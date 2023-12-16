#include <stdio.h>

#define ARRAY_COUNT(x) sizeof(x)/sizeof(*x)


void insertAtIndex(int arr[], int size, int value, int index){
    if (index > -1 && index < size){
        for (int i = size -1; i > index; i--){
            arr[i] = arr[i-1];
        }
        arr[index] = value;
    }
}

void deleteAtIndex(int arr[], int size, int index){
    if (index > -1 && index < size){
        for (int i = index; i < size; i++){
            arr[i] = arr[i+1];
        }
        arr[size - 1] = 0;
    }
}


void arrayDump(int arr[], int count){
    printf("[ ");
    for (int i=0; i< count; i++){
        printf("%d, ",arr[i]);
    }
    printf("]\n");
}   


int main(){
    // pls dont do this lmao   
    int arr[10] = {1,2,3,4,5};
    printf("0[arr]:  %d\n", 0[arr]);

    arrayDump(arr, ARRAY_COUNT(arr));

    insertAtIndex(arr, ARRAY_COUNT(arr), 0, 0);
    arrayDump(arr, ARRAY_COUNT(arr));
    
    insertAtIndex(arr, ARRAY_COUNT(arr), 6, 8);
    arrayDump(arr, ARRAY_COUNT(arr));

    deleteAtIndex(arr, ARRAY_COUNT(arr), 3);
    arrayDump(arr, ARRAY_COUNT(arr));


    return 0;
}