/**
 * @file rot.c
 * @author fspinola85 (fssecur3@outlook.com)
 * @brief A simple program to enrypt and decrypt messages or text files, using Ceaser Cipher.
 * @version 1.0
 * 
 * @copyright Copyright (c) 2020 fspinola85
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define USAGE "\nUsage:\n./rot -f tester.txt -r 5 -e\n./rot -d -m \"cxqmfq qaoelcg gtuf iqel nqmhgurhx yqffmsq, 274.\" -r 12\n"
#define MAXCHAR 1024

struct File {
    FILE *file;
    char *filename;
    int length;
    char *text;
};

/**
 * @brief Help Page
 */
void help () {
    printf("----- HELP PAGE -----\n");
    printf("\nCommands:\n");
    printf("\n\t-r, --rotate [NUMBER]\t\tDefine the rotation number.\n");
    printf("\n\t-h, --help\t\t\tShow this help page.\n");
    printf("\n\t-m, --message [MESSAGE]\t\tSpecify the message you want to encrypt or decrypt.\n");
    printf("\n\t-e, --encrypt\t\t\tUse encrypt mode.\n");
    printf("\n\t-d, --decrypt\t\t\tUse decrypt mode.\n");
    printf("\n\t-v, --version\t\t\tShow the version.\n");
    printf("\n\t-f, --file [FILENAME]\t\tSpecify the input file you want to encrypt or decrypt\n");
    printf("\n\nExamples:\n");
    printf("\n\t./rot -m \"please encrypt this message\" -r 5 -e\n");
    printf("\n\t./rot -d -m \"cxqmfq qaoelcg gtuf iqel nqmhgurhx yqffmsq, 274.\" -r 12\n\n");
}

/**
 * @brief Version Page
 */
void version () {
    printf("----- VERSION -----\n");
    printf("1.0");
    printf("\n\n");
}

/**
 * @brief Get a file's properties
 * 
 * @param filename Name of the input file
 * @return struct File* Pointer to the input file structure
 */
struct File *getFile (const char *filename) {
    struct File *f = (struct File*) malloc(sizeof(struct File));
    f->filename = filename;
    f->file = fopen(f->filename, "r");
    if (f->file == NULL) { 
        printf("\033[1;31m--> Error: Could not locate/open %s\033[0m\n", f->filename); 
    }
    f->length = 0;
    printf("File: %s\n", f->filename);

    //Allocating memory and retrieving the text from the file
    f->text = (char *) malloc(sizeof(char));
    if (f->text == NULL) {
        printf("\033[1;31m--> Error: Could not allocate memory\033[0m\n");
    }
    for (char c = getc(f->file); c != EOF; c = getc(f->file)) {
        f->text[f->length] = c;
        f->length++;
        f->text = realloc(f->text, sizeof(f->text) + (f->length * sizeof(char)));
        if (f->text == NULL) {
            printf("\033[1;31m--> Error: Could not reallocate memory\033[0m\n");
        }
    }

    return f;
}

/**
 * @brief Function which encrypts a message
 * 
 * @param rotation Rotation value
 * @param message Message to encrypt
 * @param length Message length
 * @return int 0 if the encryption succeeded
 */
int encryptMessage (const int rotation, const char *message, const int length) {
    printf("\033[01;33mEncrypting...\033[0m\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < length; i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            printf("%c", (((message[i] - 65) + rotation) % 25) + 65);
        }
        else if (message[i] >= 'a' && message[i] <= 'z') {
            printf("%c", (((message[i] - 97) + rotation) % 25) + 97);
        }
        else if (message[i] >= '0' && message[i] <= '9') {
            printf("%c", (((message[i] - 48) + rotation) % 10) + 48);
        } else {
            printf("%c", message[i]);
        }
    }
    printf("\n");
    printf("--------------------------------------------\n");
    printf("\033[1;32mDone\033[0m\n");
    printf("\033[1;32mSUCCESS!\033[0m\n");
    return 0;
}

/**
 * @brief Function which decrypts a message
 * 
 * @param rotation Rotation value
 * @param message Message to decrypt
 * @param length Message length
 * @return int if the decryption succeeded
 */
int decryptMessage (const int rotation, const char *message, const int length) {
    printf("\033[01;33mDecrypting...\033[0m\n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < length; i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            printf("%c", (((message[i] - 65) + 25 - rotation) % 25) + 65);
        }
        else if (message[i] >= 'a' && message[i] <= 'z') {
            printf("%c", (((message[i] - 97) + 25 - rotation) % 25) + 97);
        }
        else if (message[i] >= '0' && message[i] <= '9') {
            printf("%c", (((message[i] - 48) + 10 - rotation) % 10) + 48);
        }
        else {
            printf("%c", message[i]);
        }
    }
    printf("\n");
    printf("--------------------------------------------\n");
    printf("\033[1;32mDone\033[0m\n");
    printf("\033[1;32mSUCCESS!\033[0m\n");
    return 0;
}

/**
 * @brief Function which encrypts the text from a file
 * 
 * @param rotation Rotation value
 * @param filename File name
 * @return int 0 if the encryption succeeded
 */
int encryptFile (const int rotation, const char *filename) {
    struct File *input = getFile(filename);
    struct File *output = (struct File*) malloc(sizeof(struct File));
    
    //Creating the output file
    const short size = strlen(input->filename) + 10;
    char newfilename[size];
    strcpy(newfilename, "encrypted_");
    strcat(newfilename, input->filename);
    output->filename = newfilename;
    output->file = fopen(output->filename, "w");
    if (output->file == NULL) { 
        printf("\033[1;31m--> Error: Could not create %s\033[0m\n", output->filename); 
        return -1; 
    }

    printf("Output: %s\n", output->filename);
    printf("Length: %d\n", input->length);

    //Encrypting
    printf("\033[01;33mEncrypting...\033[0m\n");
    for (int i = 0; i < input->length; i++) {
        if (input->text[i] >= 'A' && input->text[i] <= 'Z') {
            fputc((((input->text[i] - 65) + rotation) % 25) + 65, output->file);
        }
        else if (input->text[i] >= 'a' && input->text[i] <= 'z') {
            fputc((((input->text[i] - 97) + rotation) % 25) + 97, output->file);
        }
        else if (input->text[i] >= '0' && input->text[i] <= '9') {
            fputc((((input->text[i] - 48) + rotation) % 10) + 48, output->file);
        } else {
            fputc(input->text[i], output->file);
        }
    }

    printf("\033[1;32mDone\033[0m\n");

    //Closing files and freeing memory
    printf("\033[01;33mCleaning up...\033[0m\n");
    fclose(input->file);
    fclose(output->file);
    free(input->text);
    free(output->text);

    printf("--------------------------------------------\n");
    printf("\033[1;32mSUCCESS!\033[0m\n");

    return 0;
}

/**
 * @brief Function which decrypts the text from a file
 * 
 * @param rotation Rotation value
 * @param filename File name
 * @return int 0 if the decryption succeeded
 */
int decryptFile (int rotation, char *filename) {
    struct File *input = getFile(filename);
    struct File *output = (struct File*) malloc(sizeof(struct File));
    
    //Creating the output file
    const short size = strlen(input->filename) + 10;
    char newfilename[size];
    strcpy(newfilename, "decrypted_");
    strcat(newfilename, input->filename);
    output->filename = newfilename;
    output->file = fopen(output->filename, "w");
    if (output->file == NULL) { 
        printf("\033[1;31m--> Error: Could not create %s\033[0m\n", output->filename); 
        return -1; 
    }

    printf("Output: %s\n", output->filename);
    printf("Length: %d\n", input->length);

    //Decrypting
    printf("\033[01;33mDecrypting...\033[0m\n");
    for (int i = 0; i < input->length; i++) {
        if (input->text[i] >= 'A' && input->text[i] <= 'Z') {
            fputc((((input->text[i] - 65) + 25 - rotation) % 25) + 65, output->file);
        }
        else if (input->text[i] >= 'a' && input->text[i] <= 'z') {
            fputc((((input->text[i] - 97) + 25 - rotation) % 25) + 97, output->file);
        }
        else if (input->text[i] >= '0' && input->text[i] <= '9') {
            fputc((((input->text[i] - 48) + 10 - rotation) % 10) + 48, output->file);
        } else {
            fputc(input->text[i], output->file);
        }
    }

    printf("\033[1;32mDone\033[0m\n");

    //Closing files and freeing memory
    printf("\033[01;33mCleaning up...\033[0m\n");
    fclose(input->file);
    fclose(output->file);
    free(input->text);
    free(output->text);

    printf("--------------------------------------------\n");
    printf("\033[1;32mSUCCESS!\033[0m\n");

    return 0;
}

/**
 * @brief Get run options from user
 * 
 * @param argc Argument counter
 * @param argv Argument vector
 * @return int 0 if there are no errors
 */
int rot(int argc, char **argv) {
    unsigned int rotation = 0;
    /* Mode
     * 0: Null
     * 1: Encryption
     * 2: Decryption
     */
    short mode = 0;
    char *message;
    bool file = false;

    //Verifying if the user wants the help screen
    int i = 0;
    while (i < argc && (strcmp(argv[i], "-h") != 0 && strcmp(argv[i], "--help") != 0)) { i++; }
    if (i != argc) {
        help();
        return 0;
    }

    //Verifying if the user wants the version
    i = 0;
    while (i < argc && (strcmp(argv[i], "-v") != 0 && strcmp(argv[i], "--version") != 0)) { i++; }
    if (i != argc) {
        version();
        return 0;
    }
    printf("--------------------------------------------\n");

    //Verifying if there are repetitive argument types
    i = 0;
    while (i < argc) {
        for (int j = i + 1; j < argc; ++j) {
            if (strcmp(argv[i], argv[j]) == 0) {
                printf("\033[1;31m--> Error: Invalid arguments.\033[0m\n");
                return -1;
            }
        }
        ++i;
    }

    printf("\033[01;33mInitializing...\033[0m\n");

    //Getting the rotation value
    i = 0;
    while (i < argc && (strcmp(argv[i], "-r") != 0 && strcmp(argv[i], "--rotation") != 0)) { i++; }
    if (i != argc && argv[i + 1] != NULL) {
        int j = 0;
        while (j < strlen(argv[i + 1]) && argv[i + 1][j] >= '0' && argv[i + 1][j] <= '9') { j++; }
        if (j == strlen(argv[i + 1])) {
            rotation = atoi(argv[i + 1]);
            printf("Rotation: %d\n", rotation);
        } else {
            printf("\033[1;31m--> Error: Invalid rotation.\033[0m\n");
            return -1;
        }
    } else {
        printf("\033[1;31m--> Error: No rotation specified.\033[0m\n");
        return -1;
    }

    //Verify if the user wrote the message or choosed a file
    i = 0;
    int k = 0;
    while (i < argc && (strcmp(argv[i], "-m") != 0 && strcmp(argv[i], "--message") != 0)) { i++; }
    if (i == argc) {
        while (k < argc && (strcmp(argv[k], "-f") != 0 && strcmp(argv[k], "--file") != 0)) { k++; }
        if (k == argc) {
            printf("\033[1;31m--> Error: No message/file was specified.\033[0m\n");
            return -1;
        }
        file = true;
    }
    if (argv[i + 1] == NULL|| argv[k + 1] == NULL) {
        printf("\033[1;31m--> Error: No message/file was specified.\033[0m\n");
        return -1;
    }
    if (!file) {
        if ((argv[i + 1][0] == NULL || argv[i + 1][0] == '-')) {
            printf("\033[1;31m--> Error: No message was specified.\033[0m\n");
            return -1;
        }
    } else {
        if ((argv[k + 1][0] == NULL || argv[k + 1][0] == '-')) {
            printf("\033[1;31m--> Error: No filename was specified.\033[0m\n");
            return -1;
        }
    }
    
    if (!file) {
        message = argv[i + 1];
        printf("Length: %ld\n", strlen(message));
    } else {
        message = argv[k + 1];
    }

    //Verify the cryptography mode
    i = 0;
    while (i < argc && (strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "--encrypt") != 0)) { i++; }
    if (i != argc) {
        mode = 1;
    }
    i = 0;
    while (i < argc && (strcmp(argv[i], "-d") != 0 && strcmp(argv[i], "--decrypt") != 0)) { i++; }
    if (i != argc) {
        if (mode != 0) {
            printf("\033[1;31m--> Error: Cryptography type conflict.\033[0m\n");
            return -1;
        }
        mode = 2;
    }
    if (mode == 0) {
        printf("\033[1;31m--> Error: No cryptography mode specified.\033[0m\n");
        return -1;
    } else if (mode == 1) {
        printf("Mode: Encryption\n");
        if (file) {
            return encryptFile(rotation, message);
        } else {
            return encryptMessage(rotation, message, strlen(message));
        }
    } else {
        printf("Mode: Decryption\n");
        if (file) {
            return decryptFile(rotation, message);
        } else {
            return decryptMessage(rotation, message, strlen(message));
        }
    }

    return 0;
}

/**
 * @brief Main function
 * 
 * @param argc Argument counter
 * @param argv Argument vector
 * @return int 0 if success, -1 if failure
 */
int main (int argc, char **argv) {
    if (rot(argc, argv) == -1) {
        printf(USAGE);
        printf("--------------------------------------------\n");
        printf("\033[1;31mFAILED!\033[0m\n");
        return -1;
    }
    return 0;
}
