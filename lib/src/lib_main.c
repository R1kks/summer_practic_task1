/*lib_main.c - файл, который хранит все функции проекта
Дозоров Владимир Евгеньевич
МК - 101*/

#include <stdio.h>


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