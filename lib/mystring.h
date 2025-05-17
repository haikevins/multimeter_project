/*
  ******************************************************************************
  * @file    mystring.h                                                         *
  * @author  Nguyen Ngoc Hai                                                   *
  * @date    25/04/2025                                                        *
  ******************************************************************************
*/

#ifndef __MYSTRING_H__
#define __MYSTRING_H__

#include "stm32f10x.h"                  // Device header

/*functions*/
void Reverse_String(char *input_string);
int Length_String(const char *input_string);
void Copy_String(char *destination, const char *source);
void Concat_String(char *destination, const char *source);
char* Find_Char(const char *input_string, char target_char);
char* Find_String(const char *full_string, const char *sub_string);
int Same_String(const char *first_string, const char *second_string);
int Compare_String(const char *first_string, const char *second_string);

#endif

/********************************* END OF FILE ********************************/
