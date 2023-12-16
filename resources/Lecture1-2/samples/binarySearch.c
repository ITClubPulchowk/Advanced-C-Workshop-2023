#include <stdint.h>


int binarySearch(int arr[], int low, int high, int target) {
    while (low < high) {
        int mid = low + (high - low) / 2;

        // Check if the target is present at the middle
        if (arr[mid] == target)
            return mid;

        // If the target is greater, ignore the left half
        else if (arr[mid] < target)
            low = mid + 1;

        // If the target is smaller, ignore the right half
        else
            high = mid;
    }
    return -1;
}

int main() {
    int arr[] = {2, 4, 7, 10, 14, 18, 23, 29, 31};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 19;

    int result = binarySearch(arr, 0, n - 1, target);

    if (result == -1)
        printf("Element %d is not present in the array\n", target);
    else
        printf("Element %d is present at index %d\n", target, result);

    return 0;
}

