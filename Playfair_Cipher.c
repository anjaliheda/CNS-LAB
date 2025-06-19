#include <stdio.h>
#include <string.h>
#include <ctype.h>

void makeTable(char key[], char table[5][5]) {
    int used[26] = {0}, k = 0;
    used['j' - 'a'] = 1;  // 'j' is treated as 'i'

    for (int i = 0; key[i]; i++) {
        char c = tolower(key[i]);
        if (c < 'a' || c > 'z') continue;
        if (!used[c - 'a']) {
            table[k / 5][k % 5] = c;
            used[c - 'a'] = 1;
            k++;
        }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (!used[c - 'a']) {
            table[k / 5][k % 5] = c;
            used[c - 'a'] = 1;
            k++;
        }
    }
}

void findPos(char table[5][5], char a, char b, int pos[]) {
    if (a == 'j') a = 'i';
    if (b == 'j') b = 'i';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == a) { pos[0] = i; pos[1] = j; }
            if (table[i][j] == b) { pos[2] = i; pos[3] = j; }
        }
}

void applyPlayfair(char text[], char table[5][5], int encrypt) {
    int len = strlen(text);
    if (len % 2 != 0) text[len++] = 'z';
    text[len] = '\0';

    for (int i = 0; i < len; i += 2) {
        int p[4];
        findPos(table, text[i], text[i+1], p);

        if (p[0] == p[2]) {
            text[i]   = table[p[0]][(p[1] + encrypt + 5) % 5];
            text[i+1] = table[p[2]][(p[3] + encrypt + 5) % 5];
        } else if (p[1] == p[3]) {
            text[i]   = table[(p[0] + encrypt + 5) % 5][p[1]];
            text[i+1] = table[(p[2] + encrypt + 5) % 5][p[1]];
        } else {
            text[i]   = table[p[0]][p[3]];
            text[i+1] = table[p[2]][p[1]];
        }
    }
}

int main() {
    char key[100], text[100], table[5][5];
    int choice;

    printf("Enter key (no spaces): ");
    scanf("%s", key);

    printf("Enter text (no spaces): ");
    scanf("%s", text);

    printf("1. Encrypt\n2. Decrypt\nChoice: ");
    scanf("%d", &choice);

    // Convert key and text to lowercase
    for (int i = 0; key[i]; i++) key[i] = tolower(key[i]);
    for (int i = 0; text[i]; i++) text[i] = tolower(text[i]);

    makeTable(key, table);

    if (choice == 1) {
        applyPlayfair(text, table, 1);
        printf("Encrypted: %s\n", text);
    } else if (choice == 2) {
        applyPlayfair(text, table, -1);
        printf("Decrypted: %s\n", text);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
