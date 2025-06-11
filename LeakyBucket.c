#include <stdio.h>
#include <unistd.h>

void leakyBucket(int *bucket, int packetSize, int bucketSize, int outputRate, int time) {
    printf("\nTime %d sec:\n", time);
    printf("Incoming Packet Size: %d bytes\n", packetSize);

    // Check for overflow
    if (*bucket + packetSize > bucketSize) {
        printf("Bucket Overflow! Dropped %d bytes\n", packetSize);
        return;
    }

    // Accept the packet
    *bucket += packetSize;
    printf("Added %d bytes to bucket. Current bucket level: %d bytes\n", packetSize, *bucket);

    // Leak/output data at fixed rate
    while (*bucket > 0) {
        sleep(1);
        if (*bucket >= outputRate) {
            *bucket -= outputRate;
            printf("Leaked %d bytes. Remaining in bucket: %d bytes\n", outputRate, *bucket);
        } else {
            printf("Leaked %d bytes. Bucket now empty.\n", *bucket);
            *bucket = 0;
        }
    }
}

int main() {
    int bucket = 0;
    int bucketSize, outputRate, numPackets, packetSize;

    printf("Enter Bucket Size (in bytes): ");
    scanf("%d", &bucketSize);

    printf("Enter Output Rate (bytes/sec): ");
    scanf("%d", &outputRate);

    printf("Enter Number of Packets: ");
    scanf("%d", &numPackets);

    for (int i = 0; i < numPackets; i++) {
        printf("\nEnter Packet %d Size (1–5 bytes recommended): ", i + 1);
        scanf("%d", &packetSize);

        leakyBucket(&bucket, packetSize, bucketSize, outputRate, i + 1);
    }

    return 0;
}
