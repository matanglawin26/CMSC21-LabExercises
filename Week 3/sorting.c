#include <stdio.h>

void sort(int *arr,int n);
void swap(int *x,int *y);

int main(){
    int n,*ptr;
    
    scanf("%d",&n);

    int arr[n];

    ptr = arr;

    for(int i = 0;i<n;i++){
        scanf("%d",(ptr+i));
    }
    
    sort(arr,n);

    for(int i = 0;i<n;i++){
        printf("%d ",*(ptr+i));
    }
    
    return 0;
}

void sort(int *arr,int n){    
    int *a,*b;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){           
            a = arr+j;
            b = arr+j+1;
            if(*a>*b){
                swap(a,b);
            }
        }
    }
}

void swap(int *x,int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}