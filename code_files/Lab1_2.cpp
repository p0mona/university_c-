
//Task 2
#include <iostream>

void quicksort(int* low, int* high) {
    if (low < high) {
        int pivot = *high; 
        int* i = low - 1;  

        for (int* j = low; j < high; j++) {
            if (*j < pivot) {
                i++; 
                int temp = *i;
                *i = *j;
                *j = temp;
            }
        }
        
        int temp = *(i + 1);
        *(i + 1) = *high;
        *high = temp;

        
        int pi = i + 1 - low;

        
        quicksort(low, low + pi - 1);
        quicksort(low + pi + 1, high);
    }
}

//Tests
int main() {
    
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    quicksort(&arr[0], &arr[n - 1]);
    
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}
