/*lib_main.h - файл, который определяет все функции проекта
Дозоров Владимир Евгеньевич
МК - 101*/

#pragma once

int hexToInt(char c);
int hexStringToBytes(const char* hex_str, unsigned char* out_buffer, int max_len);
int findFirstPattern(const unsigned char* data, int data_len, const unsigned char* pattern, int pattern_len);
int count_ocurrences(const unsigned char* data, int data_len, const unsigned char* pattern, int pattern_len);
void readFile(const char* input_file, const char* output_file);
