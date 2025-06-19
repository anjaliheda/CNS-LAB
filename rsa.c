#include <stdio.h>
#include <string.h>

// Modular exponentiation using exponentiation by squaring
int modX(int base, int exp, int mod) {
    int res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return res;
}

// GCD using Euclidean algorithm
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

// Modular inverse using brute-force search
int mod_inv(int e, int phi) {
    for (int d = 1; d < phi; d++)
        if ((e * d) % phi == 1)
            return d;
    return -1; // no inverse found
}

int main() {
    // Step 1: Key generation
    int p = 17, q = 23;
    int n = p * q;              // n = 391
    int phi = (p - 1) * (q - 1); // phi = 352

    // Step 2: Choose public exponent e
    int e = 3;
    while (gcd(e, phi) != 1)
        e++;

    // Step 3: Compute private exponent d
    int d = mod_inv(e, phi);

    // Display keys
    printf("Public Key: (%d, %d)\n", e, n);
    printf("Private Key: (%d, %d)\n", d, n);

    // Step 4: Input plaintext message
    char msg[100];
    int enc[100];

    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0; // Remove newline

    int len = strlen(msg);

    // Step 5: Encrypt message
    printf("Encrypted: ");
    for (int i = 0; i < len; i++) {
        enc[i] = modX(msg[i], e, n);  // Encryption: C = M^e mod n
        printf("%d ", enc[i]);
    }

    // Step 6: Decrypt message
    printf("\nDecrypted: ");
    for (int i = 0; i < len; i++) {
        printf("%c", modX(enc[i], d, n)); // Decryption: M = C^d mod n
    }

    printf("\n");
    return 0;
}
