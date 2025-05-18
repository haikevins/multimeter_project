#include "lcd_i2c2.h"
#include "stdio.h"
#include "uart1.h"
#include "tim2.h"

#define I2C_TIMEOUT 10000
uint8_t lcd_address; // Global variable for LCD address

uint8_t I2C2_Scan_Address(void) {
    uint8_t address;
    uint8_t found = 0;
    Uart1_Send_String("Scanning I2C2 LCD addresses...\r\n");
    
    for(address = 0x20; address <= 0x3F; address++) {
        if(address == 0x28) address = 0x38;

        uint32_t timeout = I2C_TIMEOUT;
        I2C2_Send_Start();
        I2C2->DR = address << 1;

        while(!(I2C2->SR1 & (I2C_SR1_ADDR | I2C_SR1_AF))) {
            if(--timeout == 0) break;
        }

        if(I2C2->SR1 & I2C_SR1_ADDR) {
            (void)I2C2->SR2;
            Uart1_Send_String("LCD found at address: 0x");
            Uart1_Send_Hex(address);
            Uart1_Send_String("\r\n");
            found = address;
            break;
        }

        I2C2_Send_Stop();
        I2C2->SR1 &= ~I2C_SR1_AF;
        Tim2_Delay_Ms(5);
    }

    if(!found) {
        Uart1_Send_String("LCD not found, using default address: 0x");
        Uart1_Send_Hex(0x27);
        Uart1_Send_String("\r\n");
        return 0x27;
    }
    return found;
}

void I2C2_LCD_Init(void)
{
    RCC->APB1ENR |= (1 << 22); // Enable I2C2
    RCC->APB2ENR |= (1 << 3);  // Enable GPIOB

    GPIOB->CRH &= ~((0xF << 8) | (0xF << 12));
    GPIOB->CRH |= ((0xB << 8) | (0xB << 12));

    I2C2->CR1 |= (1 << 15);
    I2C2->CR1 &= ~(1 << 15);

    I2C2->CR2 = (36 & 0x3F);
    I2C2->CCR = 180;
    I2C2->TRISE = 37;

    I2C2->OAR1 = (1 << 14);
    I2C2->CR1 = (1 << 0);

    lcd_address = I2C2_Scan_Address();
    if(!lcd_address) {
        Uart1_Send_String("LCD not found!\r\n");
        lcd_address = 0x27;
    }
    lcd_address <<= 1;

    I2C2_LCD_Control_Write(0x33);		 
    Tim2_Delay_Ms(10);
    I2C2_LCD_Control_Write(0x32);
    Tim2_Delay_Ms(50);
    I2C2_LCD_Control_Write(0x28);
    Tim2_Delay_Ms(50);
    I2C2_LCD_Control_Write(0x01);
    Tim2_Delay_Ms(50);
    I2C2_LCD_Control_Write(0x06);
    Tim2_Delay_Ms(50);
    I2C2_LCD_Control_Write(0x0C);
    Tim2_Delay_Ms(50);
    I2C2_LCD_Control_Write(0x02);
    Tim2_Delay_Ms(50);
}

void I2C2_Send_Data(uint8_t data)
{
    I2C2->DR = data;
    while(!(I2C2->SR1 & I2C_SR1_TXE));
}

void I2C2_Send_Address(uint8_t addr)
{
    I2C2->DR = addr;
    while(!(I2C2->SR1 & I2C_SR1_ADDR));
    volatile uint32_t temp = I2C2->SR2;
}

void I2C2_Send_Start(void)
{
    I2C2->CR1 |= I2C_CR1_START;
    while(!(I2C2->SR1 & I2C_SR1_SB));
}

void I2C2_Send_Stop(void)
{
    I2C2->CR1 |= I2C_CR1_STOP;
}

void I2C2_LCD_Write_byte(char data)
{
    I2C2_Send_Start();
    I2C2_Send_Address(lcd_address);
    I2C2_Send_Data(data);
    I2C2_Send_Stop();
}

void I2C2_LCD_Data_Write(char data)
{
    char data_u = data & 0xf0;
    char data_l = (data << 4) & 0xf0;
    uint8_t data_t[4] = {
        data_u | 0x0D,
        data_u | 0x09,
        data_l | 0x0D,
        data_l | 0x09
    };
    for(uint8_t i = 0; i < 4; i++) {
        I2C2_LCD_Write_byte(data_t[i]);
    }
}

void I2C2_LCD_Control_Write(char data)
{
    char data_u = data & 0xf0;
    char data_l = (data << 4) & 0xf0;
    uint8_t data_t[4] = {
        data_u | 0x04,
        data_u,
        data_l | 0x04,
        data_l | 0x08
    };
    for(uint8_t i = 0; i < 4; i++) {
        I2C2_LCD_Write_byte(data_t[i]);
    }
}

void I2C2_LCD_Send_String(char *str)
{
    while(*str) {
        I2C2_LCD_Data_Write(*str++);
    }
}

void I2C2_LCD_Clear(void)
{
    I2C2_LCD_Control_Write(0x01);
    Tim2_Delay_Ms(10);
}

void I2C2_LCD_Set_Cursor(char col, char row)
{
    char address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    I2C2_LCD_Control_Write(address);
}

void I2C2_LCD_Send_Number(uint16_t num)
{
    char buffer[16];
    uint8_t length = 0;
    if(num == 0) {
        I2C2_LCD_Data_Write('0');
        return;
    }
    while(num > 0) {
        buffer[length++] = (num % 10) + '0';
        num /= 10;
    }
    for(int i = length - 1; i >= 0; i--) {
        I2C2_LCD_Data_Write(buffer[i]);
    }
}

void I2C2_LCD_Send_Float(float number)
{
    if(number < 0) {
        I2C2_LCD_Send_String("-");
        number = -number;
    }
    uint16_t integer = (uint16_t)number;
    float decimal = number - (uint16_t)number;
    I2C2_LCD_Send_Number(integer);
    I2C2_LCD_Send_String(".");
    decimal *= 1000;
    I2C2_LCD_Send_Number((uint16_t)decimal);
}
