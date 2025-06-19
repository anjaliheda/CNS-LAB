#include <stdio.h>
#include <string.h>
#define POLYNOMIAL "10001000000100001" // CRC-CCITT (X.25)

void xor(char *data, const char *poly, int poly_len) {
    for (int i = 0; i < poly_len; i++)
        data[i] = (data[i] == poly[i]) ? '0' : '1';
}

void crcCheck(const char *data, const char *poly, char *codeword) {
    int dataLen = strlen(data);
    int polyLen = strlen(poly);
    int totalLen = dataLen + polyLen - 1;
    char temp[200];
    // Step 1: Copy data and append (polyLen - 1) zeros
    strcpy(temp, data);
    for (int i = dataLen; i < totalLen; i++)
        temp[i] = '0';
    temp[totalLen] = '\0';  // Null-terminate
    // Step 2: Perform bitwise division (XOR where needed)
    for (int i = 0; i <= totalLen - polyLen; i++) {
        if (temp[i] == '1') {
            xor(&temp[i], poly, polyLen);
        }
    }
    // Step 3: Build final codeword = original data + remainder
    strncpy(codeword, data, dataLen);
    strncpy(codeword + dataLen, temp + dataLen, polyLen - 1);
    codeword[totalLen] = '\0';
}

void detectError(const char *codeword, const char *poly) {
    int len = strlen(codeword);
    int poly_len = strlen(poly);
    char temp[200];
    strcpy(temp, codeword);

    for (int i = 0; i <= len - poly_len; i++)
        if (temp[i] == '1') xor(&temp[i], poly, poly_len);
    
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
