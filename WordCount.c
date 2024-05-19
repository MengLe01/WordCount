#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_BUFFER_SIZE 1024

int countCharacters(FILE* file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

int countWords(FILE* file) {
    int count = 0;
    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        char* token = strtok(buffer, " ,\t\n");
        while (token != NULL) {
            count++;
            token = strtok(NULL, " ,\t\n");
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("使用方法：%s [-c | -w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char* option = argv[1];
    char* filename = argv[2];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 1;
    }

    int count;
    if (strcmp(option, "-c") == 0) {
        count = countCharacters(file);
        printf("字符数：%d\n", count);
    }
    else if (strcmp(option, "-w") == 0) {
        count = countWords(file);
        printf("单词数：%d\n", count);
    }
    else {
        printf("没有 %s 这个操作，请输入 -c 或 -w\n", option);
        return 1;
    }

    fclose(file);
    return 0;
}
