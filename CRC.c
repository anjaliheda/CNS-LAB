#include <stdio.h>
#include <string.h>

#define POLYNOMIAL "10001000000100001" // CRC-CCITT (X.25)

void xorOperation(char *data, const char *poly, int poly_len) {
    for (int i = 0; i < poly_len; i++)
        data[i] = (data[i] == poly[i]) ? '0' : '1';
}

void crcCheck(const char *data, const char *poly, char *codeword) {
    int data_len = strlen(data), poly_len = strlen(poly);
    char temp[200];
    strcpy(temp, data);
    memset(temp + data_len, '0', poly_len - 1);
    temp[data_len + poly_len - 1] = '\0';

    for (int i = 0; i <= strlen(temp) - poly_len; i++)
        if (temp[i] == '1') xorOperation(&temp[i], poly, poly_len);

    snprintf(codeword, 200, "%s%.*s", data, poly_len - 1, &temp[data_len]);
}

void detectError(const char *codeword, const char *poly) {
    int len = strlen(codeword), poly_len = strlen(poly);
    char temp[200];
    strcpy(temp, codeword);

    for (int i = 0; i <= len - poly_len; i++)
        if (temp[i] == '1') xorOperation(&temp[i], poly, poly_len);

    for (int i = len - poly_len + 1; i < len; i++)
        if (temp[i] == '1') {
            printf("Error detected\n");
            return;
        }

    printf("No error detected\n");
}

int main() {
    char data[100], codeword[200];
    printf("Enter data: ");
    scanf("%s", data);

    printf("Using polynomial: %s\n", POLYNOMIAL);
    crcCheck(data, POLYNOMIAL, codeword);

    printf("Final codeword: %s\n", codeword);

    int test;
    printf("Test error detection? (0 = yes, 1 = no): ");
    scanf("%d", &test);

    if (test == 0) {
        int pos;
        printf("Enter error position: ");
        scanf("%d", &pos);

        if (pos < 0 || pos >= strlen(codeword)) {
            printf("Invalid position.\n");
            return 1;
        }

        codeword[pos] = (codeword[pos] == '0') ? '1' : '0';
        printf("Erroneous codeword: %s\n", codeword);

        detectError(codeword, POLYNOMIAL);
    }

    return 0;
}
