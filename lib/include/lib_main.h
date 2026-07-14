/*lib_main.h - файл, который определяет все функции проекта
Дозоров Владимир Евгеньевич
МК - 101*/

#pragma once

#include <stdio.h>

int hexToInt(char c);
int hexStringToBytes(const char* hex_str, unsigned char* out_buffer, int max_len);
int findFirstPattern(const unsigned char* data, int data_len, const unsigned char* pattern, int pattern_len);
int count_ocurrences(const unsigned char* data, int data_len, const unsigned char* pattern, int pattern_len);
int replaceInBlock(const unsigned char* data, int data_len, const unsigned char* search, int search_len, const unsigned char* replace, int replace_len, FILE* out, unsigned char* tail, int* tail_len);
void readFile(const char* input_file, const char* output_file);
