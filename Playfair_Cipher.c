#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

// Converts characters of the string to lowercase
void toLowerCase(char plain[], int ps) {
    for (int i = 0; i < ps; i++) {
        if (plain[i] >= 'A' && plain[i] <= 'Z') {
            plain[i] += 32;
        }
    }
}

// Removes spaces from the string
int removeSpaces(char* plain, int ps) {
    int count = 0;
    for (int i = 0; i < ps; i++) {
        if (plain[i] != ' ') {
            plain[count++] = plain[i];
        }
    }
    plain[count] = '\0';
    return count;
}

// Generates the 5x5 key table
void generateKeyTable(char key[], int ks, char keyT[5][5]) {
    int dicty[26] = {0};  // Map for 26 letters of alphabet
    int i = 0, j = 0;

    // Fill dictionary with key characters
    for (int k = 0; k < ks; k++) {
        if (key[k] != 'j') {
            dicty[key[k] - 'a'] = 2;
        }
    }
    dicty['j' - 'a'] = 1;  // 'j' is treated as 'i'

    // Place key characters in the grid
    for (int k = 0; k < ks; k++) {
        if (dicty[key[k] - 'a'] == 2) {
            dicty[key[k] - 'a'] -= 1;
            keyT[i][j++] = key[k];
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }

    // Fill remaining grid with unused letters
    for (int k = 0; k < 26; k++) {
        if (dicty[k] == 0) {
            keyT[i][j++] = (char)(k + 'a');
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}

// Finds the positions of two characters in the key table
void search(char keyT[5][5], char a, char b, int arr[]) {
    if (a == 'j') a = 'i';  // Treat 'j' as 'i'
    if (b == 'j') b = 'i';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyT[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            if (keyT[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

// Modulo 5 operation
int mod5(int a) {
    if (a < 0) a += 5;
    return a % 5;
}

// Prepares the plaintext by ensuring its length is even
int prepare(char str[], int ptrs) {
    if (ptrs % 2 != 0) {
        str[ptrs++] = 'z';
        str[ptrs] = '\0';
    }
    return ptrs;
}

// Encryption using Playfair Cipher
void encrypt(char str[], char keyT[5][5], int ps) {
    int a[4];
    for (int i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] + 1)];
            str[i + 1] = keyT[a[0]][mod5(a[3] + 1)];
        } else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] + 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];
        } else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

// Decryption using Playfair Cipher
void decrypt(char str[], char keyT[5][5], int ps) {
    int a[4];
    for (int i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] - 1)];
            str[i + 1] = keyT[a[0]][mod5(a[3] - 1)];
        } else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] - 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] - 1)][a[1]];
        } else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

// Main function for encryption or decryption
void processText(char str[], char key[], int isEncrypt) {
    char ps = strlen(str), ks = strlen(key), keyT[5][5];

    ks = removeSpaces(key, ks);
    toLowerCase(key, ks);

    ps = removeSpaces(str, ps);
    toLowerCase(str, ps);
    ps = prepare(str, ps);

    generateKeyTable(key, ks, keyT);

    if (isEncrypt) {
        encrypt(str, keyT, ps);
        printf("Ciphertext: %s\n", str);
    } else {
        decrypt(str, keyT, ps);
        printf("Decrypted text: %s\n", str);
    }
}

// Main code
int main() {
    char str[SIZE], key[SIZE];
    int choice;

    // Input key text
    printf("Enter key text: ");
    fgets(key, SIZE, stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline

    // Input plaintext or ciphertext
    printf("Enter text: ");
    fgets(str, SIZE, stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove trailing newline

    // Ask user for encryption or decryption
    printf("Choose operation:\n1. Encrypt\n2. Decrypt\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Encrypting...\n");
        processText(str, key, 1); // Encrypt
    } else if (choice == 2) {
        printf("Decrypting...\n");
        processText(str, key, 0); // Decrypt
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
