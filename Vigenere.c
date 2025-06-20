#include <stdio.h>
#include <string.h>
#include <ctype.h>

char shift(char m, char k, int dir) {
    int a = tolower(m) - 'a';
    int b = tolower(k) - 'a';
    return 'a' + (a + dir * b + 26) % 26;
}

int main() {
    int ch;
    char msg[100], key[100], res[100];

    printf("Vigenère Cipher\n1 - Encrypt\n2 - Decrypt\nChoice: ");
    scanf("%d", &ch);

    if (ch == 1 || ch == 2) {
        int mode = (ch == 1) ? 1 : -1;

        printf("Enter message: ");
        scanf("%s", msg);
        printf("Enter key: ");
        scanf("%s", key);

        int len = strlen(msg), klen = strlen(key);

        for (int i = 0; i < len; i++)
            res[i] = shift(msg[i], key[i % klen], mode);
        res[len] = '\0';

        printf("%s message: %s\n\n", mode == 1 ? "Encrypted" : "Decrypted", res);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}
