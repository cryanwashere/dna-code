#include <stdio.h>
#include <stdlib.h>

// this is the protocol that is used to encode the bits into 
// DNA
#define prot {'A','T','C','G'}

// take a byte, and encode it into four bases
char * encode_char(unsigned char c) {
    char * result = (char*)malloc(sizeof(char) * 5);
    if (result == NULL) {
        fprintf(stderr, "Error: could not allocate memory for byte encoding string");
        exit(1);
    }
    // string termination character
    result[4] = '\0';

    // iterate through the bits of the byte 2 at a time, and 
    // encode each pair of bits into a corresponding
    // nucleotide
    int i;
    for (i = 0; i < 4; i++) {
        unsigned char bits = (c >> (2 * i)) & 0x03;
        switch (bits) {
            case 0:
                result[i] = 'A';
                break;
            case 1:
                result[i] = 'T';
                break;
            case 2: 
                result[i] = 'C';
                break;
            case 3:
                result[i] = 'G';
                break;
            default:
                fprintf(stderr, "Error: invalid bits in byte encoding");
                exit(1);
        }
    }
    return result;
}

// open and encode a file, using the given file path
char * encode_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error, could not open file %s\n", filename);
        return NULL;
    }

    // determine the size of the file
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // Allocate memory for the encoded string
    char* encoded_str = (char*)malloc(size * 4 +1);
    if (encoded_str == NULL) {
        fprintf(stderr, "Error: could not allocate memory for byte encoding string");
        fclose(file);
        return NULL;
    }


    // read the file contents, and encode each character
    int i = 0;
    unsigned char c;
    while(fread(&c, sizeof(unsigned char), 1, file) == 1) {
        char * encoded_char = encode_char(c);
        for (int j = 0; j < 4; j++) {
            encoded_str[i++] = encoded_char[j];
        }
        free(encoded_char);
    }

    // Null-terminate the string
    encoded_str[i] = '\0';

    fclose(file);
    return encoded_str;
}

int main(int argc, char *argv[]) {
    
    const char* filename = argv[1];

    printf("encoding file: %s\n", filename);
    char * encoded_str = encode_file(filename);
    if (encoded_str == NULL) {
        fprintf(stderr, "Error: failed to encode file %s\n", filename);
        return 1;
    }

    printf("DNA Encoded string: \n%s\n", encoded_str);
    free(encoded_str);
   
    
    
    return 0;
}