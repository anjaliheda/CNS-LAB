#include <stdio.h>
#include <string.h>
#include <ctype.h>

char shift(char m, char k, int dir) {
    int a = tolower(m) - 'a';
    int b = tolower(k) - 'a';
    return 'a' + (a + dir * b + 26) % 26;
}

void process(int mode) {
    char msg[100], key[100], res[100];
    printf("Enter message: ");
    scanf("%s", msg);
    printf("Enter key: ");
    scanf("%s", key);

    int len = strlen(msg), klen = strlen(key);
    for (int i = 0; i < len; i++)
        res[i] = shift(msg[i], key[i % klen], mode);
    res[len] = '\0';

    printf("%s message: %s\n\n", mode == 1 ? "Encrypted" : "Decrypted", res);
}

int main() {
    int ch;
    while (1) {
        printf("Vigenère Cipher\n1 - Encrypt\n2 - Decrypt\n3 - Quit\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) process(1);
        else if (ch == 2) process(-1);
        else if (ch == 3) break;
        else printf("Invalid choice!\n");
    }
    return 0;
}
