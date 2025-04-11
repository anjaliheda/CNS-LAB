#include <stdio.h>
#include <string.h>

#define POLYNOMIAL "10001000000100001"  // CRC-CCITT (X.25) polynomial

void xorOperation(char *data, const char *poly, int poly_len) {
    // Perform bitwise XOR operation between data and polynomial
    for (int i = 0; i < poly_len; i++) {
        data[i] = (data[i] == poly[i]) ? '0' : '1';
    }
}

void crcCheck(const char *original_data, const char *poly, int poly_len, char *final_codeword) {
    int data_len = strlen(original_data);
    char temp[200];
    
    // Step 1: Copy original data and pad with zeros
    strcpy(temp, original_data);
    for (int i = 0; i < poly_len - 1; i++) {
        temp[data_len + i] = '0';
    }
    temp[data_len + poly_len - 1] = '\0';

    printf("\nModified data is : %s\n", temp);

    // Step 2: Perform XOR division
    for (int i = 0; i <= strlen(temp) - poly_len; i++) {
        if (temp[i] == '1') {
            xorOperation(&temp[i], poly, poly_len);
        }
    }

    // Extract checksum (remainder after XOR)
    char checksum[50];
    strncpy(checksum, &temp[data_len], poly_len - 1);
    checksum[poly_len - 1] = '\0';

    printf("Checksum is : %s\n", checksum);

    // Step 3: Final codeword = original data + checksum
    strcpy(final_codeword, original_data);
    strcat(final_codeword, checksum);

    printf("Final code word is : %s\n", final_codeword);
}

void detectError(char *data, const char *poly, int poly_len) {
    int len = strlen(data);
    char temp[200];
    strcpy(temp, data);

    // Step 1: Perform XOR division on the received data
    for (int i = 0; i <= len - poly_len; i++) {
        if (temp[i] == '1') {
            xorOperation(&temp[i], poly, poly_len);
        }
    }

    // Step 2: Check if remainder (checksum) is non-zero
    int error = 0;
    for (int i = len - poly_len + 1; i < len; i++) {
        if (temp[i] == '1') {
            error = 1;
            break;
        }
    }

    if (error)
        printf("Error detected\n");
    else
        printf("No error detected\n");
}

int main() {
    char data[100], final_codeword[200], err_data[200];
    int choice, pos;

    // Step 1: Enter the data/message
    printf("Enter data : ");
    scanf("%s", data);

    // Step 2: Generate the polynomial and display it
    printf("Generating polynomial : %s\n", POLYNOMIAL);

    // Step 3: Perform CRC check to get final codeword
    crcCheck(data, POLYNOMIAL, strlen(POLYNOMIAL), final_codeword);

    // Step 4: Ask if error detection should be tested
    printf("\nTest error detection 0 (yes) 1(no)? : ");
    scanf("%d", &choice);

    if (choice == 0) {
        // Step 5: Simulate error insertion
        printf("Enter the position where error is to be inserted: ");
        scanf("%d", &pos);

        strcpy(err_data, final_codeword);

        // Step 6: Flip the bit at the specified position
        err_data[pos] = (err_data[pos] == '0') ? '1' : '0';

        printf("Erroneous data: %s\n", err_data);

        // Step 7: Detect error in the erroneous data
        detectError(err_data, POLYNOMIAL, strlen(POLYNOMIAL));
    }

    return 0;
}

