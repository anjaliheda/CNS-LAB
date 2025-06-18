#include <stdio.h>

// Modular exponentiation function (efficient method)
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

int main() {
    int p, g;  // Prime modulus and primitive root

    printf("Enter a prime number (p): ");
    scanf("%d", &p);

    printf("Enter a primitive root modulo p (g): ");
    scanf("%d", &g);

    int a, b;  // Private keys of Alice and Bob
    printf("Enter Alice's private key (a): ");
    scanf("%d", &a);

    printf("Enter Bob's private key (b): ");
    scanf("%d", &b);

    int A = modX(g, a, p);  // Alice's public key
    int B = modX(g, b, p);  // Bob's public key

    int secretA = modX(B, a, p);  // Alice computes secret
    int secretB = modX(A, b, p);  // Bob computes secret

    printf("\nPublic values:\n");
    printf("p = %d, g = %d\n", p, g);
    printf("Alice's Public Key (A = g^a mod p): %d\n", A);
    printf("Bob's Public Key (B = g^b mod p): %d\n", B);

    printf("\nShared Secret Keys:\n");
    printf("Alice's Secret Key: %d\n", secretA);
    printf("Bob's Secret Key: %d\n", secretB);

    if (secretA == secretB) {
        printf("\nKey exchange successful! Shared key = %d\n", secretA);
    } else {
        printf("\nKey exchange failed.\n");
    }

    return 0;
}
