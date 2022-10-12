#include <stdio.h>

int min(int, int);
void show(int*, int);
void sort(int[], int, int, int);

int main(int argc, char const *argv[]) {
    if(argc != 1) {
        int size = argc - 1;
        int array[size];
        for(int i = 1; i < argc; i++) {
            sscanf(argv[i], "%d", &array[i - 1]);
        }
        
        printf("source array:\n");
        show(array, size);

        for (int curr_size = 1; curr_size <= size - 1; curr_size = 2 * curr_size) { 
	        for (int left_start = 0; left_start < size - 1; left_start += 2 * curr_size) { 
	        	int mid = left_start + curr_size - 1; 
	        	int right_end = min(left_start + 2 * curr_size - 1, size - 1); 
	        	sort(array, left_start, mid, right_end); 
	        } 
        } 

        printf("sort array:\n");
        show(array, size);

    }else printf("array empty!!!\n");
    return 0;
}

int min(int a, int b) {
    if(a < b)
        return a;
    else return b;
}

void show(int* arr, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d\n", arr[i]);
    }
}

void sort(int array[], int left, int mid, int right) {
    int L_size = mid - left + 1;
    int R_size = right - mid;
    int L[L_size], R[R_size];

    for(int i = 0; i < L_size; i++) 
        L[i] = array[left + i];
    for(int j = 0; j < R_size; j++)
        R[j] = array[mid + 1 + j];    

    int main_index_array = left, L_index = 0, R_index = 0;
    while (L_index < L_size && R_index < R_size) {
        if(L[L_index] <= R[R_index]) 
            array[main_index_array++] = L[L_index++];
        else array[main_index_array++] = R[R_index++];
    }
    while (L_index < L_size) 
		array[main_index_array++] = L[L_index++]; 

	while (R_index < R_size) 
		array[main_index_array++] = R[R_index++]; 
}
