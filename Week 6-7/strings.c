/*
    Exercise #8: Strings
    Date completed: 04/5/2021
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int size;
    int capacity;
    char *arr;
} vector;

void initList(vector* list);
void initString(vector* str,char* chr);
void insertItem(vector* str, char item);
void resize(vector* str);
void concatenate(vector* combined, vector* a, vector* b);
void slice(vector *sliced, vector* source, int start, int end);
void choice1();
void choice2();
void input1(char* strA, char* strB);
void input2(char *str, int *a, int *b);

int main(){    
    int n;

    scanf("%d ",&n);

    switch(n){
        case 1:
            choice1();
            break;
        case 2:
            choice2();
            break;
        default:
            break;
    } 

    return 0;
}
void initList(vector* list) {
    list->size = 0;
    list->capacity = 10;
    list->arr = (char*)malloc(sizeof(char)*list->capacity);
}

void initString(vector* str,char* temp) {
    initList(str);

    for(int i = 0;temp[i]!='\0';i++)
        insertItem(str,temp[i]);    
    
    insertItem(str,'\0');
}

void insertItem(vector* str, char item) {
    if (str->size == str->capacity)
        resize(str);
    
    str->arr[str->size++] = item;
}

void resize(vector* str){
    int newCapacity = 2 * str->size;
    char* newArr = (char*) malloc(sizeof(char) * newCapacity);

    for (int i = 0; i < str->size; i++) 
        newArr[i] = str->arr[i];    

    str->capacity = newCapacity;
    free(str->arr);
    str->arr = newArr;
}

void concatenate(vector* combined, vector* a, vector* b){
    int len,i;
    len = a->size+b->size-1;

    char *temp = (char*)malloc(sizeof(char)*len);

    for(i = 0; i < len-1;i++){
        if(i < a->size-1)
            temp[i] = a->arr[i];
        else
            temp[i] = b->arr[i-a->size+1];        
    }

    temp[i] = '\0';

    initString(combined,temp);
}

void slice(vector *sliced, vector* source, int start, int end){
    int i=0;
    char temp[end-start+1];

    for(i = 0;i<end;i++)
        if(i >= start)
            temp[i-start] = source->arr[i];          
    
    temp[i-start] = '\0';

    initString(sliced,temp);
}

void input1(char* strA, char* strB){
    int currentSize, i = 0;
    char c;

    currentSize = sizeof(char)*20;

    while (c != ' '){        
        scanf("%c",&c);
        
        strA[i++]=c;

        if(i == currentSize){
            currentSize+=i;
            strA = realloc(strA, currentSize);
        }
    }
    strA[--i] = '\0';

    i = 0;

    while (c != '\n'){
        scanf("%c",&c);
        
        strB[i++]=c;

        if(i == currentSize){
            currentSize+=i;
            strB = realloc(strB, currentSize);
        }
    }
    strB[--i] = '\0';

}

void input2(char *str, int *a, int *b){
    int currentSize,i = 0;
    char c;

    currentSize = sizeof(char)*20;

    while (c != ' '){
        scanf("%c",&c);
        
        str[i++]=c;
        if(i == currentSize){
            currentSize*=2;
            str = realloc(str, currentSize);
        }
    }
    str[--i] = '\0'; 

    scanf("%d %d",a,b);

}

void choice1(){
    vector comb, a, b;
    char *strA,*strB;

    strA = (char*)malloc(sizeof(char)*20);
    strB = (char*)malloc(sizeof(char)*20);
    
    input1(strA,strB);

    initString(&a,strA);
    initString(&b,strB);    

    concatenate(&comb,&a,&b);

    printf("%s\n",comb.arr);

    free(strA);
    free(strB);
    free(a.arr);
    free(b.arr);
    free(comb.arr);
}

void choice2(){
    vector sliced, source;
    int a,b;
    char *str;

    str = (char*)malloc(sizeof(char)*20);

    input2(str,&a,&b);
    
    initString(&source,str);
    
    slice(&sliced,&source,a,b);

    printf("%s\n",sliced.arr);

    free(str);
    free(sliced.arr);
    free(source.arr);
}
