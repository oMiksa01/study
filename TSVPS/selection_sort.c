#include <stdio.h>

void swap(int*, int*);
void show(int*, int);

int main(int argc, char const *argv[]) {
    if(argc != 1) {
        int size = argc - 1;
        int array[size];
        for(int i = 1; i < argc; i++) {
            sscanf(argv[i], "%d", &array[i - 1]);
        }
        
        printf("source array:\n");
        show(array, size);

        int min, index;
        for(int i = 0; i < size - 1; i++) {
            min = array[i];
            index = i;
            for(int j = i + 1; j < size; j++)
                if(min > array[j]) {
                    min = array[j]; 
                    index = j;
                }
            swap(&array[i], &array[index]);      
        }

        printf("sort array:\n");
        show(array, size);

    }else printf("array empty!!!\n");
    return 0;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void show(int* arr, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d\n", arr[i]);
    }
}