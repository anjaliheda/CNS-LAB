#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function to simulate the Leaky Bucket algorithm
void leakyBucket(int *bucket, int packetSize, int bucketSize, int outputRate) {
    int time = 0;

    // Check if packet can fit into the bucket
    if (*bucket + packetSize > bucketSize) {
        printf("\nBucket Overflow! Packet of size %d bytes is dropped.\n", packetSize);
    } else {
        *bucket += packetSize;  // Add packet to the bucket
        printf("\nPacket of size %d bytes added to the bucket.\n", packetSize);
    }

    // Output data at the constant rate (leaky rate)
    while (*bucket > 0) {
        sleep(1);  // Simulate 1-second delay for output
        time++;

        if (*bucket >= outputRate) {
            *bucket -= outputRate;  // Output the fixed rate of data
            printf("\nTime %d Sec: %d bytes Outputted from bucket.\n", time, outputRate);
        } else {
            printf("\nTime %d Sec: %d bytes Outputted (last packet).\n", time, *bucket);
            *bucket = 0;  // Empty the bucket after this output
        }
    }
    printf("\nBucket Output Successful.\n");
}

int main() {
    int bucket = 0;  // Initial bucket size is 0
    int bucketSize, outputRate, numPackets, packetSize, delay, time = 0;

    // User input for bucket size, output rate, and number of packets
    printf("____________________________________________\n");
    printf("C Program for Leaky Bucket Algorithm\n");
    printf("____________________________________________\n");

    printf("Enter Bucket Size (Maximum Capacity): ");
    scanf("%d", &bucketSize);

    printf("Enter Output Rate (bytes/sec): ");
    scanf("%d", &outputRate);

    printf("Enter Number of Packets: ");
    scanf("%d", &numPackets);

    // Process each packet
    for (int i = 0; i < numPackets; i++) {
        delay = rand() % 3;  // Random delay to simulate packet arrival time
        sleep(delay);
        time += delay;

        packetSize = rand() % 1000;  // Random packet size (0-999 bytes)
        printf("\n---------------------------\n");
        printf("Time %d Sec\n", time);
        printf("Packet Number %d\n", i);
        printf("Packet Size %d bytes\n", packetSize);

        // Call the leakyBucket function to process the packet
        leakyBucket(&bucket, packetSize, bucketSize, outputRate);
    }

    return 0;
}

