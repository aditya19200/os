#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SEGMENTS 100

typedef struct {
    int base_address;
    int segment_limit;
} Segment;

Segment segment_table[MAX_SEGMENTS];
int segment_count = 0;

bool add_segment(int segment_number, int base_address, int segment_limit) {
    if (segment_number < 0 || segment_number >= MAX_SEGMENTS) {
        printf("Error: Invalid segment number.\n");
        return false;
    }
    if (base_address < 0 || segment_limit <= 0) {
        printf("Error: Invalid base address or segment limit.\n");
        return false;
    }

    segment_table[segment_number].base_address = base_address;
    segment_table[segment_number].segment_limit = segment_limit;
    if (segment_number >= segment_count) {
        segment_count = segment_number + 1;
    }

    printf("Segment %d added with Base Address: %d and Limit: %d\n", segment_number, base_address, segment_limit);
    return true;
}

int compute_physical_address(int segment_number, int logical_address) {
    if (segment_number < 0 || segment_number >= segment_count) {
        printf("Error: Segment %d does not exist.\n", segment_number);
        return -1;
    }

    Segment segment = segment_table[segment_number];

    if (logical_address < 0 || logical_address >= segment.segment_limit) {
        printf("Error: Logical address %d exceeds segment limit %d.\n", logical_address, segment.segment_limit);
        return -1;
    }

    return segment.base_address + logical_address;
}

int main() {
    int segment_number, base_address, segment_limit, logical_address;

    printf("Enter Segment Number: ");
    scanf("%d", &segment_number);
    printf("Enter Base Address: ");
    scanf("%d", &base_address);
    printf("Enter Segment Limit: ");
    scanf("%d", &segment_limit);

    if (!add_segment(segment_number, base_address, segment_limit)) {
        return 1;
    }

    printf("\nEnter Logical Address: ");
    scanf("%d", &logical_address);

    int physical_address = compute_physical_address(segment_number, logical_address);
    if (physical_address != -1) {
        printf("Physical Address: %d\n", physical_address);
    }

    return 0;
}
