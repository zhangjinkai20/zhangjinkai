#include <stdio.h>
int maxSubArray(int* nums, int numsSize) {
    int maxSoFar = 0, maxEndingHere = 0;
    for (int i = 0; i < numsSize; i++) {
        maxEndingHere = maxEndingHere + nums[i];
        if (maxEndingHere < 0) {
            maxEndingHere = 0;
        }
        if (maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
        }
    }
    return maxSoFar;
}

int main() {
    int a[] = { -2, 11, -4, 13, -5, -2 };
    int n = sizeof(a) / sizeof(a[0]);
    int max_sum = maxSubArray(a, n);
    printf("最大子段和为: %d\n", max_sum);
    return 0;
}
