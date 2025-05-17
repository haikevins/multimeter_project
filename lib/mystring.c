#include "mystring.h"

/*
    Tra ve do dai cua chuoi
    Tham so:
    - input_string: chuoi can tinh do dai
    Tra ve:
    - Do dai cua chuoi (so ky tu truoc ky tu '\0')
*/
int Length_String(const char *input_string)
{
    int length = 0;
    while (input_string[length] != '\0') length++;
    return length;
}

/*
    So sanh 2 chuoi
    Tham so:
    - first_string: chuoi thu nhat
    - second_string: chuoi thu hai
    Tra ve:
    - 0 neu 2 chuoi bang nhau
    - <0 neu first_string < second_string
    - >0 neu first_string > second_string
*/
int Compare_String(const char *first_string, const char *second_string)
{
    int index = 0;
    while (first_string[index] != '\0' && second_string[index] != '\0') {
        if (first_string[index] < second_string[index]) return -1;
        if (first_string[index] > second_string[index]) return 1;
        index++;
    }
    if (first_string[index] == '\0' && second_string[index] == '\0') return 0;
    if (first_string[index] == '\0') return -1;
    return 1;
}

/*
    Sao chep chuoi
    Tham so:
    - destination: chuoi dich de sao chep vao
    - source: chuoi nguon can sao chep
*/
void Copy_String(char *destination, const char *source)
{
    int index = 0;
    while (source[index] != '\0') {
        destination[index] = source[index];
        index++;
    }
    destination[index] = '\0';
}

/*
    Noi chuoi
    Tham so:
    - destination: chuoi dich, chuoi se duoc noi them
    - source: chuoi nguon, chuoi duoc noi vao cuoi destination
*/
void Concat_String(char *destination, const char *source)
{
    int dest_index = 0;
    while (destination[dest_index] != '\0') dest_index++;
    int src_index = 0;
    while (source[src_index] != '\0') {
        destination[dest_index++] = source[src_index++];
    }
    destination[dest_index] = '\0';
}

/*
    Tim chuoi con trong chuoi
    Tham so:
    - full_string: chuoi lon de tim kiem
    - sub_string: chuoi con can tim
    Tra ve:
    - Con tro toi vi tri bat dau tim thay sub_string trong full_string, hoac NULL neu khong tim thay
*/
char* Find_String(const char *full_string, const char *sub_string)
{
    int i, j;
    for (i = 0; full_string[i] != '\0'; i++) {
        for (j = 0; sub_string[j] != '\0' && full_string[i + j] == sub_string[j]; j++);
        if (sub_string[j] == '\0') return (char*)&full_string[i];
    }
    return 0;
}

/*
    Tim ky tu trong chuoi
    Tham so:
    - input_string: chuoi can tim
    - target_char: ky tu can tim
    Tra ve:
    - Con tro toi vi tri dau tien tim thay ky tu, hoac NULL neu khong tim thay
*/
char* Find_Char(const char *input_string, char target_char)
{
    int index = 0;
    while (input_string[index] != '\0') {
        if (input_string[index] == target_char) return (char*)&input_string[index];
        index++;
    }
    return 0;
}

/*
    Dao nguoc chuoi
    Tham so:
    - input_string: chuoi can dao nguoc
*/
void Reverse_String(char *input_string)
{
    int length = Length_String(input_string);
    for (int i = 0; i < length / 2; i++) {
        char temp = input_string[i];
        input_string[i] = input_string[length - 1 - i];
        input_string[length - 1 - i] = temp;
    }
}

/*
    Kiem tra 2 chuoi co giong nhau khong
    Tham so:
    - first_string: chuoi thu nhat
    - second_string: chuoi thu hai
    Tra ve:
    - 1 neu 2 chuoi giong nhau hoan toan
    - 0 neu khac nhau
*/
int Same_String(const char *first_string, const char *second_string) {
    int index = 0;
    while (first_string[index] != '\0' && second_string[index] != '\0') {
        if (first_string[index] != second_string[index]) return 0;
        index++;
    }
    return (first_string[index] == '\0' && second_string[index] == '\0');
}
