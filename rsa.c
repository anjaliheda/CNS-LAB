#include <stdio.h>
#include <string.h>

// Modular exponentiation
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp /= 2;
        base = (base * base) % mod;
    }
    return result;
}

// GCD
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Modular inverse
int mod_inverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

int main() {
    // Bigger primes to support ASCII
    int p = 17, q = 23;
    int n = p * q;           // n = 391
    int phi = (p - 1) * (q - 1); // phi = 352

    int e = 3;
    while (gcd(e, phi) != 1) e++;

    int d = mod_inverse(e, phi);

    printf("Public Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n", d, n);

    char msg[100];
    int encrypted[100];

    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;

    int len = strlen(msg);

    // Encrypt
    printf("Encrypted: ");
    for (int i = 0; i < len; i++) {
        encrypted[i] = mod_exp((int)msg[i], e, n);
        printf("%d ", encrypted[i]);
    }
    printf("\n");

    // Decrypt
    printf("Decrypted: ");
    for (int i = 0; i < len; i++) {
        char ch = (char)mod_exp(encrypted[i], d, n);
        printf("%c", ch);
    }
    printf("\n");

    return 0;
}

