#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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
    //printf("%02x %s\n", c, result);
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

unsigned char decode_char(char* encoded_byte) {
    unsigned char result = 0;

    int i;
    for(i = 0; i < 4; i++) {
        unsigned char bits;
        switch(encoded_byte[i]) {
            case 'A':
                bits = 0;
                break;
            case 'T':
                bits = 1;
                break;
            case 'C':
                bits = 2;
                break;
            case 'G':
                bits = 3;
                break;
            default:
                fprintf(stderr, "Error: invalid character in encoded byte: %c", encoded_byte[i]);
                exit(1);
        }
        result |= bits << (2 * i);
    }

    return result;
}

void decode_sequence(const char * str, const char * filename) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file %s for writing\n", filename);
        return;
    }

    // loop over the string, and write the corresponding byte to the output file
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i+=4) {
        
        char encoded_byte[5];
        strncpy(encoded_byte, str+i, 4);
        encoded_byte[4] = '\0';

        unsigned char byte = decode_char(encoded_byte);

        //printf("%s %02x\n", encoded_byte, byte);

        fwrite(&byte, sizeof(unsigned char), 1, fp);
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("invalid argument");
        return 0;
    }

    // encode a file
    if (strcmp(argv[1], "encode") == 0) {
        // the file path is the second argument
        const char* filename = argv[2];
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
    
    // decode a sequence
    if (strcmp(argv[1], "decode") == 0) {
        
        if (argc < 4) {
            printf("decode: invalid arguments");
            return 0;
        }

        const char * filename = argv[2];
        const char * sequence = argv[3];

        printf("decoding sequence to file %s:\n", filename);
        decode_sequence(sequence, filename);

        //unsigned char result = decode_char(sequence);
        //printf("Decoded byte: %02x\n", result);
        
        return 0;
    }

    return 0;
}