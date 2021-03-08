#include <stdio.h>

int div(int a,int b);
int prime(int a,int b);
int find(int a[],int n,int z);
int choice1();
int choice2();
int choice3();

int main(){
    int choice;

    // printf("Enter valid input: ");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            printf("%d\n",choice1());
            break;
        case 2:
            printf("%d\n",choice2());
            break;       
        case 3:                
            printf("%d\n",choice3());
            break;
        default:
            break;
    }    

    return 0;
}

int div(int a,int b){
    int x = 0;

    if(a<b)
        return x;  
    return x+=1+div(a-b,b);
}
int prime(int a,int b){
    if(b>0)
        return prime(b,a%b);
    else
        return a;
}
int find(int a[],int n,int z){
    if(n<0)
        return 0;
    if(a[n]==z)
        return 1;
    return find(a,--n,z);
}
int choice1(){    
    int a,b;
    scanf("%d %d",&a,&b);

    return div(a,b);
}
int choice2(){ 
    int a,b;
    scanf("%d %d",&a,&b);     

    if(prime(a,b)==1)
        return 1;
    else
        return 0;
}
int choice3(){
    int n;
    scanf("%d",&n); 
    int arr[n];

    for(int i = 0;i<n+1;i++)
        scanf("%d",&arr[i]);   

    return find(arr,n-1,arr[n]);
}

