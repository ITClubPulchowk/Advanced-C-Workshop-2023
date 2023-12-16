#include <stdio.h>

void merge(int arr[], int left, int mid, int right)
{
    // Find sizes of two subarrays to be merged
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int left_arr[n1];
    int right_arr[n2];

    // Copy data to temporary arrays left_arr[] and right_arr[]
    for (int i = 0; i < n1; i++)
    {
        left_arr[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++)
    {
        right_arr[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[k] = left_arr[i++];
        }
        else
        {
            arr[k] = right_arr[j++];
        }

        k++;
    }

    // Copy the remaining elements of left_arr[], if there are any
    while (i < n1)
    {
        arr[k++] = left_arr[i++];
    }

    // Copy the remaining elements of right_arr[], if there are any
    while (j < n2)
    {
        arr[k++] = right_arr[j++];
    }
}

void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Recursively divide and merge the two halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main()
{
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    merge_sort(arr, 0, size - 1);

    printf("\nSorted array: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
