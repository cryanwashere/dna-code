#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    unsigned char* buffer;
    FILE* ptr;

    ptr = fopen(argv[1],"rb");

    fread(buffer,sizeof(buffer),1,ptr);


    for (int i=0;i<sizeof(buffer);i++) {
        printf("%x ",buffer[i]);
    }
    

    return 0;
}