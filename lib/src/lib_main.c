/*lib_main.c - файл, который хранит все функции проекта
Дозоров Владимир Евгеньевич
МК - 101*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef N
#error "N err"
#endif

int hexToInt(char c){
    if (c >= '0' && c <= '9'){
        return c - '0';
    }
    if (c >= 'a' && c <= 'f'){
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F'){
        return c - 'A' + 10;
    }
    return -1;
}

int hexStringToBytes(const char* hex_str, unsigned char* out_buffer, int max_len){
    if (hex_str == NULL && out_buffer == NULL){
        return -1;
    }

    int len = strlen(hex_str);
    if (len % 2 != 0){
        return -1;
    }

    int count = len/2;
    if (count > max_len){
        return -1;
    }

    for (int i = 0; i < count; i++){
        int frst = hexToInt(hex_str[i*2]);
        int lst = hexToInt(hex_str[i*2+1]);

        if (frst == -1 && lst == -1){
            return -1;
        }

        out_buffer[i] = (unsigned char)(frst * 16 + lst);
    }
    return count;
}

int findFirstPattern(const unsigned char* data, int data_len, 
                        const unsigned char* pattern, int pattern_len){
    if (pattern_len <= 0 || pattern_len >= data_len){
        return -1;
    }

    for (int i = 0; i <= data_len - pattern_len; i++){
        int match = 1;
        for (int j = 0; j < pattern_len; j++){
            if (data[i + j] != pattern[j]){
                match = 0;
                break;
            }
        }
        if (match == 1){
            return i;
        }
    }
    return -1;
}

int count_ocurrences(const unsigned char* data, int data_len, const unsigned char* pattern, int pattern_len){
    int count = 0;
    int pos = 0;

    while (pos <= data_len - pattern_len){
        int found = findFirstPattern(data + pos, data_len - pos, pattern, pattern_len);
        if (found == -1){
            break;
        }
        count++;
        pos += found + pattern_len;
    }
    return count;
}

int replaceInBlock(const unsigned char* data, int data_len,
                     const unsigned char* search, int search_len,
                     const unsigned char* replace, int replace_len,
                     FILE* out,
                     unsigned char* tail_buf, int* tail_buf_len) {
    int replacements = 0;
    int pos = 0;

    while (pos < data_len) {
        int found = find_first_pattern(data + pos, data_len - pos, search, search_len);
        if (found == -1) {
            break; 
        }

        if (found > 0) {
            fwrite(data + pos, 1, found, out);
        }
        
        fwrite(replace, 1, replace_len, out);
        replacements++;
        
        pos = pos + found + search_len;
    }

    int remaining = data_len - pos;
    *tail_buf_len = 0;
    
    if (remaining > 0) {
        int safe_tail = 0;
        if (search_len > 1) {
            safe_tail = search_len - 1;
        }
        int to_write = remaining - safe_tail;
        if (to_write < 0) to_write = 0;

        if (to_write > 0) {
            fwrite(data + pos, 1, to_write, out);
        }

        *tail_buf_len = remaining - to_write;
        for (int i = 0; i < *tail_buf_len; i++) {
            tail_buf[i] = data[pos + to_write + i];
        }
    }
    
    return replacements;
}

void replaceInFile(const char* input_file, const char* output_file,
                   const unsigned char* search, int search_len,
                   const unsigned char* replace, int replace_len){
    FILE* input;
    input = fopen(input_file, "rb");
    if (input == NULL){
        printf("%s file open err", input_file);
        return;
    }

    FILE* output;
    output = fopen(output_file, "wb");
    if (output == NULL){
        printf("%s file open err", output_file);
        fclose(input);
        return;
    }

    unsigned char buffer[N];
    unsigned char tail[2*N];
    int tail_len = 0;

    unsigned char combined[3 * N];

    long total_read = 0;
    int total_replacement = 0;



    while (1){
        size_t bytes_read = fread(buffer, 1, N, input);
        if (bytes_read == 0){
            break;
        }
        total_read += (long)bytes_read;

        const unsigned char* ptr_to_process = buffer;
        int len_to_process = (int)bytes_read;

        if(tail_len > 0){
            for (int i = 0; i < tail_len; i++){
                combined[i] = tail[i];
            }
            for (int i = 0; i < bytes_read; i++){
                combined[tail_len + i] = buffer[i];
            }
            ptr_to_process = combined;
            len_to_process = tail_len + (int)bytes_read;
        }

        int block_replace = replaceInBlock(
            ptr_to_process, len_to_process,
            search, search_len,
            replace, replace_len,
            output,
            tail, &tail_len
        );

        total_replacement += block_replace;

        
    }
    
    if (tail_len > 0){
            fwrite(tail, 1, tail_len, output);
        }

        fclose(input);
        fclose(output);

    return;
}