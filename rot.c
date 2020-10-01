/*
 * Made by: fspinola85
 * 
 * v0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define USAGE "\nUsage:\n./rot -m \"please encrypt this message\" -r 5 -e\n./rot -d -m \"cxqmfq qaoelcg gtuf iqel nqmhgurhx yqffmsq, 274.\" -r 12\n"

void help () {
    printf("----- HELP PAGE -----\n");
    printf("\nCommands:\n");
    printf("\n\t-r, --rotate [NUMBER]\t\tDefine the rotation number.\n");
    printf("\n\t-h, --help\t\t\tShow this help page.\n");
    printf("\n\t-m, --message [MESSAGE]\t\tSpecify the message you want to encrypt or decrypt.\n");
    printf("\n\t-e, --encrypt\t\t\tUse encrypt mode.\n");
    printf("\n\t-d, --decrypt\t\t\tUse decrypt mode.\n");
    printf("\n\t-v, --version\t\t\tShow the version.\n");
    printf("\n\nExamples:\n");
    printf("\n\t./rot -m \"please encrypt this message\" -r 5 -e\n");
    printf("\n\t./rot -d -m \"cxqmfq qaoelcg gtuf iqel nqmhgurhx yqffmsq, 274.\" -r 12\n\n");
}

void version () {
    printf("----- VERSION -----\n");
    printf("0.1");
    printf("\n\n");
}
// Encryption
void encryptMessage (int rotation, char *message, int length) {
    printf("Encrypted Message: \n");
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
    printf("\033[1;32mSUCCESS!\033[0m\n");
}
// Decryption
void decryptMessage (int rotation, char *message, int length) {
    printf("Decrypted Message: \n");
    printf("--------------------------------------------\n");
    for (int i = 0; i < length; i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            printf("%c", (((message[i] - 65) + 25 - rotation) % 25) + 65);
        }
        else if (message[i] >= 'a' && message[i] <= 'z') {
            printf("%c", (((message[i] - 97) + 25 - rotation) % 25) + 97);
        }
        else if (message[i] >= '0' && message[i] <= '9') {
            printf("%c", (((message[i] - 48) + 25 - rotation) % 10) + 48);
        }
        else {
            printf("%c", message[i]);
        }
    }
    printf("\n");
    printf("--------------------------------------------\n");
    printf("\033[1;32mSUCCESS!\033[0m\n");
}

int rot(int argc, char **argv) {
    unsigned int rotation = 0;
    /* Mode
     * 0: Null
     * 1: Encryption
     * 2: Decryption
     */
    short mode = 0;
    char *message;

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

    i = 0;
    while (i < argc && (strcmp(argv[i], "-m") != 0 && strcmp(argv[i], "--message") != 0)) { i++; }
    if (i == argc) {
        printf("\033[1;31m--> Error: No message was specified.\033[0m\n");
        return -1;
    } 
    //Verify if the user wrote the message
    else if ((argv[i + 1][0] == NULL || argv[i + 1][0] == '-') && argv[i + 1][2] == NULL) {
        printf("\033[1;31m--> Error: No message was specified.\033[0m\n");
        return -1;
    }
    message = argv[i + 1];
    printf("Length: %ld\n", strlen(message));

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
        encryptMessage(rotation, message, strlen(message));
    } else {
        printf("Mode: Decryption\n");
        decryptMessage(rotation, message, strlen(message));
    }

    return 0;
}

int main (int argc, char **argv) {
    if (rot(argc, argv) == -1) {
        printf(USAGE);
        return -1;
    }
    return 0;
}
