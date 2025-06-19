#include <stdio.h>
#include <unistd.h>

void leakyBucket(int *bucket, int packetSize, int bucketSize, int outputRate) {
    printf("\nIncoming Packet Size: %d bytes\n", packetSize);

    // Check for overflow
    if (*bucket + packetSize > bucketSize) {
        printf("Bucket Overflow! Dropped %d bytes\n", packetSize);
        return;
    }

    // Accept the packet
    *bucket += packetSize;
    printf("Accepted %d bytes. Bucket Level: %d bytes\n", packetSize, *bucket);

    // Leak/output data at fixed rate
    while (*bucket > 0) {
        sleep(1);
        int leak = (*bucket >= outputRate) ? outputRate : *bucket;
        *bucket -= leak;
        printf("Leaked %d bytes. Remaining: %d bytes\n", leak, *bucket);
    }
}

int main() {
    int bucket = 0, bucketSize, outputRate, numPackets, packetSize;

    printf("Enter Bucket Size (bytes): ");
    scanf("%d", &bucketSize);

    printf("Enter Output Rate (bytes/sec): ");
    scanf("%d", &outputRate);

    printf("Enter Number of Packets: ");
    scanf("%d", &numPackets);

    for (int i = 0; i < numPackets; i++) {
        printf("\nEnter Packet %d Size: ", i + 1);
        scanf("%d", &packetSize);
        leakyBucket(&bucket, packetSize, bucketSize, outputRate);
    }

    return 0;
}
