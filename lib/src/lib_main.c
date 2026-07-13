/*lib_main.c - файл, который хранит все функции проекта
Дозоров Владимир Евгеньевич
МК - 101*/

#include <stdio.h>
#include <string.h>


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

void readFile(const char* input_file, const char* output_file){
    FILE* input;
    input = fopen(input_file, "r");
    if (input == NULL){
        printf("%s file open err", input_file);
        return;
    }

    FILE* output;
    output = fopen(output_file, "w");
    if (output == NULL){
        printf("%s file open err", output_file);
        return;
    }

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), input) != NULL){
        fputs(buffer, output);
    }
    
    fclose(input);
    fclose(output);

    return;
}