#include <stdio.h>
#include <string.h>
#define SIZE 30

void toLower(char *s, int n) {
    for (int i = 0; i < n; i++)
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
}

int removeSpaces(char *s, int n) {
    int k = 0;
    for (int i = 0; i < n; i++)
        if (s[i] != ' ') s[k++] = s[i];
    s[k] = '\0';
    return k;
}

int mod5(int x) { return (x + 5) % 5; }

void genKey(char *key, int n, char tab[5][5]) {
    int used[26] = {0}, i = 0, j = 0;
    used['j' - 'a'] = 1;
    for (int k = 0; k < n; k++) {
        int ch = key[k] - 'a';
        if (!used[ch]) {
            tab[i][j++] = key[k];
            used[ch] = 1;
            if (j == 5) i++, j = 0;
        }
    }
    for (int ch = 0; ch < 26; ch++) {
        if (!used[ch]) {
            tab[i][j++] = ch + 'a';
            if (j == 5) i++, j = 0;
        }
    }
}

void find(char tab[5][5], char a, char b, int pos[]) {
    if (a == 'j') a = 'i';
    if (b == 'j') b = 'i';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            if (tab[i][j] == a) pos[0] = i, pos[1] = j;
            if (tab[i][j] == b) pos[2] = i, pos[3] = j;
        }
}

int prepareText(char *s, int n) {
    if (n % 2 != 0) s[n++] = 'z', s[n] = '\0';
    return n;
}

void playfair(char *s, char tab[5][5], int n, int enc) {
    int p[4];
    for (int i = 0; i < n; i += 2) {
        find(tab, s[i], s[i+1], p);
        if (p[0] == p[2]) {
            s[i] = tab[p[0]][mod5(p[1] + enc)];
            s[i+1] = tab[p[0]][mod5(p[3] + enc)];
        } else if (p[1] == p[3]) {
            s[i] = tab[mod5(p[0] + enc)][p[1]];
            s[i+1] = tab[mod5(p[2] + enc)][p[1]];
        } else {
            s[i] = tab[p[0]][p[3]];
            s[i+1] = tab[p[2]][p[1]];
        }
    }
}

int main() {
    char text[SIZE], key[SIZE], tab[5][5];
    int choice;

    printf("Enter key: ");
    fgets(key, SIZE, stdin);
    key[strcspn(key, "\n")] = '\0';

    printf("Enter text: ");
    fgets(text, SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("1. Encrypt\n2. Decrypt\nChoice: ");
    scanf("%d", &choice);

    int kt = strlen(key), pt = strlen(text);
    kt = removeSpaces(key, kt);
    pt = removeSpaces(text, pt);
    toLower(key, kt);
    toLower(text, pt);
    pt = prepareText(text, pt);
    genKey(key, kt, tab);

    if (choice == 1) {
        playfair(text, tab, pt, +1);
        printf("Cipher: %s\n", text);
    } else if (choice == 2) {
        playfair(text, tab, pt, -1);
        printf("Plain: %s\n", text);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
