#include "stdio.h"

int main (int argc, char *argv[]) {
    char result_str[100] = "";
    int k = 0;
    for(int i = 1; i < argc; i++)
        for (int j = 0; argv[i][j] != '\0'; j++)
            result_str[k++] = argv[i][j];

    printf("%s\n", result_str);
}