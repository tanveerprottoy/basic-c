#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;

    int* map = (int*)malloc(numsSize * sizeof(int));
    int* result = (int*)malloc(*returnSize * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        map[i] = -1;
    }

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];

        for (int j = 0; j < i; j++) {
            if (nums[j] == complement) {
                result[0] = j;
                result[1] = i;
                free(map);
                return result;
            }
        }

        map[i] = nums[i];
    }

    *returnSize = 0;

    free(map);

    free(result);

    return NULL;
}

/*
Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same. Then return the number of unique elements in nums.

Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:

Change the array nums such that the first k elements of nums contain the unique elements in the order they were present in nums initially. The remaining elements of nums are not important as well as the size of nums.
Return k.
*/
int removeDuplicates(int* nums, int numsSize) {
    // first element is always counted unique
    int k = 1;

    for (int i = 0; i < numsSize; i++) {
        // as nums sorted in non-decreasing order
        // only need to compare previous element to the next
        // increment k when an unique element is seen
        if (nums[i] != nums[k]) {
            // unique element is seen
            // move it to k
            nums[k] = nums[i];

            // increment k
            k++;
        }

        // if elements are not unique we want the loop to continue
        // and do nothing
    }

    // return k after loop ends
    return k;
}
