#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Alphabet definition (lowercase letters only)
const char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";

// Returns the index of a character in the alphabet (0-25)
int get_char_index(char c) {
    return tolower(c) - 'a';  // Ensure lowercase handling for case insensitivity
}

// Returns the character corresponding to an index (0-25)
char get_char_from_index(int index) {
    return alphabet[index % 26];  // Ensure we stay within bounds
}

// Encrypts the message using the Vigenère cipher
void encrypt() {
    char message[100], key[100], result[100];
    int message_len, key_len;

    // Input message
    printf("\nEnter your message: ");
    scanf("%s", message);

    // Input key
    printf("Enter your key: ");
    scanf("%s", key);

    // Calculate the lengths of the message and key
    message_len = strlen(message);
    key_len = strlen(key);

    int delta_index = 0;
    for (int i = 0; i < message_len; i++) {
        // Wrap around the key if it's shorter than the message
        if (delta_index >= key_len) {
            delta_index = 0;
        }

        // Encrypt character: (message[i] + key[delta_index]) % 26
        int message_index = get_char_index(message[i]);
        int key_index = get_char_index(key[delta_index]);
        int encrypted_index = (message_index + key_index) % 26;

        // Store the encrypted character
        result[i] = get_char_from_index(encrypted_index);

        // Move to the next character in the key
        delta_index++;
    }

    // Null-terminate the result
    result[message_len] = '\0';

    printf("Encrypted message: %s\n\n", result);
}

// Decrypts the message using the Vigenère cipher
void decrypt() {
    char message[100], key[100], result[100];
    int message_len, key_len;

    // Input message
    printf("\nEnter your encrypted message: ");
    scanf("%s", message);

    // Input key
    printf("Enter your key: ");
    scanf("%s", key);

    // Calculate the lengths of the message and key
    message_len = strlen(message);
    key_len = strlen(key);

    int delta_index = 0;
    for (int i = 0; i < message_len; i++) {
        // Wrap around the key if it's shorter than the message
        if (delta_index >= key_len) {
            delta_index = 0;
        }

        // Decrypt character: (message[i] - key[delta_index] + 26) % 26
        int message_index = get_char_index(message[i]);
        int key_index = get_char_index(key[delta_index]);
        int decrypted_index = (message_index - key_index + 26) % 26;  // Handle negative values

        // Store the decrypted character
        result[i] = get_char_from_index(decrypted_index);

        // Move to the next character in the key
        delta_index++;
    }

    // Null-terminate the result
    result[message_len] = '\0';

    printf("Decrypted message: %s\n\n", result);
}

// Main function for the Vigenère cipher program
int main() {
    int choice = 0;

    // Program menu
    while (1) {
        printf("Vigenère Cipher\n");
        printf("1 - Encrypt\n");
        printf("2 - Decrypt\n");
        printf("3 - Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                encrypt();  // Call encryption function
                break;
            case 2:
                decrypt();  // Call decryption function
                break;
            case 3:
                printf("Exiting the program...\n");
                return 0;  // Exit the program
            default:
                printf("Invalid choice! Please choose again.\n");
        }
    }

    return 0;
}

