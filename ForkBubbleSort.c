#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main() {
    int* pointer; //To hold address of block created
    int sizeArr, temp;
    int sum = 0;

    scanf("%d", &sizeArr); //takes user input for array size
    pointer = (int*)malloc(sizeArr * sizeof(int));
    if (pointer == NULL){
        printf("Memory Allocation Error");
        exit(0);
    }
    for(int i = 0; i < sizeArr; i++){
        scanf("%d", pointer + i);
        sum += *(pointer + i);
    }
    if(fork() == 0){
            printf("Child process executing:\n");
            for(int i = 0; i < sizeArr; i++){
                for(int j = 0; j < sizeArr - i - 1; j++){
                    if(pointer[j] > pointer[j + 1]){
                        temp = pointer[j];
                        pointer[j] = pointer[j + 1];
                        pointer[j + 1] = temp;
                    }
                }
            }
            printf("The sorted array is:\n");
            for(int i = 0; i < sizeArr; i++){
                printf("%d ", pointer[i]);
            }
            printf("\n");
    }
    else{
        wait(NULL);
        printf("Parent process executing:\n");
        for(int i = 0; i < sizeArr; i++){
                for(int j = i + 1; j < sizeArr; j++){
                    if(pointer[i] < pointer[j]){
                        temp = pointer[i];
                        pointer[i] = pointer[j];
                        pointer[j] = temp;
                    }
                }
            }
            printf("The sorted array is:\n");
            for(int i = 0; i < sizeArr; i++){
                printf("%d ", pointer[i]);
            }
    }
    return 0;
}