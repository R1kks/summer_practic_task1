/*main.c - главный файл всего проекта
Дозоров Владимир Евгеньевич
МК - 101*/

int main(int argc, char* argv[], char* envp[]) {
    const char* input_file = argv[1];
    const char* output_file = argv[2];
    
    readFile(input_file, output_file);
    return 0;
}