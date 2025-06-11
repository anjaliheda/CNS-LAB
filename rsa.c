#include <stdio.h>
#include <string.h>

// Modular exponentiation
int mod_exp(int base, int exp, int mod) {
    int res = 1;
    base %= mod;
    while (exp) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// GCD
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

// Modular inverse (brute force)
int mod_inv(int e, int phi) {
    for (int d = 1; d < phi; d++)
        if ((e * d) % phi == 1) return d;
    return -1;
}

int main() {
    int p = 17, q = 23, n = p * q, phi = (p - 1) * (q - 1);
    int e = 3;
    while (gcd(e, phi) != 1) e++;
    int d = mod_inv(e, phi);

    printf("Public Key: (%d, %d)\nPrivate Key: (%d, %d)\n", e, n, d, n);

    char msg[100]; int enc[100];
    printf("Enter message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;

    int len = strlen(msg);
    printf("Encrypted: ");
    for (int i = 0; i < len; i++) {
        enc[i] = mod_exp(msg[i], e, n);
        printf("%d ", enc[i]);
    }

    printf("\nDecrypted: ");
    for (int i = 0; i < len; i++)
        printf("%c", mod_exp(enc[i], d, n));
    printf("\n");

    return 0;
}
