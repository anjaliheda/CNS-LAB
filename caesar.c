#include<stdio.h>
#include<ctype.h>

int main() {

    char text[500], ch;
    int key, choice;
    printf("1. Encrypt \n2. Decrypt \nEnter your choice: ");
    scanf("%d", &choice);
    printf("Enter a message: ");
    scanf("%s", text);
    printf("Enter the key: ");
    scanf("%d", &key);

    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];

        if (isalnum(ch)) {

            if (choice == 1) {  // Encryption
              
                if (islower(ch)) {
                    ch = (ch - 'a' + key) % 26 + 'a';
                }
                
                else if (isupper(ch)) {
                    ch = (ch - 'A' + key) % 26 + 'A';
                }
                
                else if (isdigit(ch)) {
                    ch = (ch - '0' + key) % 10 + '0';
                }
            }
            else if (choice == 2) {  // Decryption
                
                if (islower(ch)) {
                    ch = (ch - 'a' - key + 26) % 26 + 'a';
                }
               
                else if (isupper(ch)) {
                    ch = (ch - 'A' - key + 26) % 26 + 'A';
                }
                
                else if (isdigit(ch)) {
                    ch = (ch - '0' - key + 10) % 10 + '0';
                }
            } else {
                printf("Invalid choice! Please enter 1 or 2.");
                return 1;
            }

        } else {
            printf("Invalid character in the message.\n");
            return 1;
        }

        
        text[i] = ch;
    }

   
    if (choice == 1) {
        printf("Encrypted message: %s\n", text);
    } else if (choice == 2) {
        printf("Decrypted message: %s\n", text);
    }

    return 0;
}

