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
        *bucket += packetSize;  
        printf("\nPacket of size %d bytes added to the bucket.\n", packetSize);
    }

    // Output data at the constant rate (leaky rate)
    while (*bucket > 0) {
        sleep(1);  /
        time++;

        if (*bucket >= outputRate) {
            *bucket -= outputRate;  
            printf("\nTime %d Sec: %d bytes Outputted from bucket.\n", time, outputRate);
        } else {
            printf("\nTime %d Sec: %d bytes Outputted (last packet).\n", time, *bucket);
            *bucket = 0;  
        }
    }
    printf("\nBucket Output Successful.\n");
}

int main() {
    int bucket = 0;  
    int bucketSize, outputRate, numPackets, packetSize, delay, time = 0;

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

        packetSize = rand() % 1000;  
        printf("\n---------------------------\n");
        printf("Time %d Sec\n", time);
        printf("Packet Number %d\n", i);
        printf("Packet Size %d bytes\n", packetSize);

        leakyBucket(&bucket, packetSize, bucketSize, outputRate);
    }

    return 0;
}

