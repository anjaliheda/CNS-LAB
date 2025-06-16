#include <stdio.h>
#include <ctype.h>

int main() {
    char text[500], ch;
    int key, choice;

    printf("1. Encrypt\n2. Decrypt\nEnter your choice: ");
    scanf("%d", &choice);
    printf("Enter a message (no special characters): ");
    scanf(" %s", text);  
    printf("Enter the key: ");
    scanf("%d", &key);

    for (int i = 0; text[i] != '\0'; i++) {
        ch = text[i];

        if (islower(ch)) {
            ch = (choice == 1)
                ? (ch - 'a' + key) % 26 + 'a'
                : (ch - 'a' - key + 26) % 26 + 'a';
        }
        else if (isupper(ch)) {
            ch = (choice == 1)
                ? (ch - 'A' + key) % 26 + 'A'
                : (ch - 'A' - key + 26) % 26 + 'A';
        }
        else if (isdigit(ch)) {
            ch = (choice == 1)
                ? (ch - '0' + key) % 10 + '0'
                : (ch - '0' - key + 10) % 10 + '0';
        }
        else if (ch != ' ') {
            printf("Error: Special characters not allowed.\n");
            return 1;
        }

        text[i] = ch;  
    }

    if (choice == 1)
        printf("Encrypted message: %s\n", text);
    else if (choice == 2)
        printf("Decrypted message: %s\n", text);
    else
        printf("Invalid choice.\n");

    return 0;
}
