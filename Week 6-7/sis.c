#include <stdio.h>
#include <stdlib.h>

struct Data{
    int sNumA,sNumB,yearLevel, age, grade, index;
    char firstN[15], lastN[15], course[15],sex[15];
};
typedef struct Data Data;

struct myNode{
    struct Data data;
    struct myNode* next;
};
typedef struct myNode myNode;

typedef struct{
    myNode* head;
    myNode* tail;
    int size;
}SLList;

myNode *getItem(SLList* list, int index);
myNode *createNode();
myNode *getNode(SLList* list, int index);
void initList(SLList* list);
void setItem(SLList* list, int index);
void insertItem(SLList* list, int index);
void selection(int n, SLList *list);
void subSelection(int n,SLList *list, myNode *node);
void displayAll(SLList *list);
void intSort(SLList *list);
void stringSort(SLList *list);
void menu();
void subMenu(myNode *node);
int removeItem(SLList* list, int index);
int stringCompare(char s1[], char s2[]);
int stringCheck(myNode *node, char *str,int n);
char toLower(char ch);
char toUpper(char ch);

int main(){
    int n;
    myNode *node = NULL;
    myNode *new;
    SLList list;
    
    initList(&list);
    do{
        menu();
        scanf("%d",&n);
        printf("\n");
        selection(n,&list);
        
    }while(n != 14);
    
    return 0;
}

myNode* createNode() {
    myNode* a = (myNode*) malloc(sizeof(myNode));

    printf("Student number: ");
    scanf("%d-%d",&a->data.sNumA,&a->data.sNumB);
    printf("Last name: ");
    scanf("%s",&a->data.lastN);
    printf("First name: ");
    scanf("%s",&a->data.firstN);
    printf("Course: ");
    scanf("%s",&a->data.course);
    printf("Year level: ");
    scanf("%d",&a->data.yearLevel);
    printf("Age: ");
    scanf("%d",&a->data.age);
    printf("Sex: ");
    scanf("%s",&a->data.sex);
    printf("Final grade: ");
    scanf("%d",&a->data.grade);

    a->next = 0;

    return a;
}

myNode* getNode(SLList* list, int index) {
    myNode* current = list->head;
    
    for (int i = 0; i < index; i++) 
        current = current->next;

    return current;
}

void initList(SLList* list) {
    list->head = 0;
    list->tail = 0;
    list->size = 0;
}

void setItem(SLList* list, int index){
    int n;
    if (index >= 0 && index <= list->size - 1) {
        myNode* node = getNode(list, index);

        do{
            subMenu(node);
            scanf("%d",&n);
            printf("\n");
            subSelection(n,list,node);
        }while(n != 9);        
    }
}

void insertItem(SLList* list, int index) {
    if (index >= 0 && index <= list->size) {
        myNode* toInsert = createNode();

        if (index == 0) {
            toInsert->next = list->head;
            list->head = toInsert;
        }
        if (index == list->size) {
            if (list->tail != 0) {
                list->tail->next = toInsert;
            }        
            list->tail = toInsert;
        }
        list->size++;
    }
}

myNode *getItem(SLList* list, int index) {
    if (index >= 0 && index <= list->size - 1) {
        myNode* node = getNode(list, index);
        return node;
    }
}

int getIndex(SLList *list){
    myNode *node = list->head;
    int index = 0, numA, numB;
    printf("Student number: ");
    scanf("%d-%d",&numA,&numB);

    while(node != NULL){
        if(node->data.sNumA == numA && node->data.sNumB == numB){
            return index;
        }
        index++;
        node = node->next;
    }
    return -1;
}
int removeItem(SLList* list, int index) {
    if (index >= 0 && index <= list->size - 1) {
        myNode* toRemove;

        if (index == 0) {
            toRemove = list->head;
            list->head = toRemove->next;
        } else {
            myNode* previous = getNode(list, index -1);
            toRemove = previous->next;
            previous->next = toRemove->next;

            if (index == list->size - 1) {
                list->tail = previous;
            }
        }
        free(toRemove);
        list->size--;
    }
}
void displayAll(SLList *list){    
    myNode *node = list->head;

    while(node != NULL){
        printf("Student number: %d-%d\n",node->data.sNumA,node->data.sNumB);
        printf("Last name: %s\n",node->data.lastN);
        printf("First name: %s\n",node->data.firstN);
        printf("Course: %s\n",node->data.course);
        printf("Year level: %d\n",node->data.yearLevel);      
        printf("Age: %d\n",node->data.age);      
        printf("Sex: %s\n",node->data.sex);  
        printf("Final grade: %d\n",node->data.grade);        

        printf("\n");
        node = node->next;
    }

    printf("Displaying %d of %d student(s)\n",list->size,list->size);
}
int stringCheck(myNode *node, char *str,int n){
    switch (n){
        case 1:        
            for(int i = 0; node->data.lastN[i] != '\0';i++)
                if(toLower(node->data.lastN[i]) != toLower(str[i]))
                    return 0;                
            
            str[0] = toUpper(str[0]);
            break;
        case 2:
            for(int i = 0; node->data.course[i] != '\0';i++){           
                str[i] = toUpper(str[i]);                   
                if(toUpper(node->data.course[i]) != str[i])
                    return 0;  
            }
            break;
        case 3:
            for(int i = 0; node->data.sex[i] != '\0';i++){         
                if(toLower(node->data.sex[i]) != toLower(str[i]))
                    return 0;  
            }
            str[0] = toUpper(str[0]);
            break;
        default:
            break;
    }
    return 1;
}

int intCheck(myNode *node, int numA, int numB, int n){
    switch (n){
        case 0:        
            if(node->data.sNumA == numA && node->data.sNumB == numB)
                return 1;
            break;
        case 1:
            if(node->data.yearLevel == numA)
                return 1;
            break;
        case 2:
            if(node->data.grade >= 60)
                return 1;
            break;
        case 3:
            if(node->data.grade < 60)
                return 1;
            break;
        default:
            break;
    }
    return 0;
}

void strFilter(SLList *list,int n){
    myNode *node = list->head;
    int count = 0;
    char str[15];

    scanf("%s",str);

    printf("\n");

    while(node != NULL){
        if(stringCheck(node,str,n)){             
            printf("Student number: %d-%d\n",node->data.sNumA,node->data.sNumB);
            printf("Last name: %s\n",node->data.lastN);
            printf("First name: %s\n",node->data.firstN);
            printf("Course: %s\n",node->data.course);
            printf("Year level: %d\n",node->data.yearLevel);      
            printf("Age: %d\n",node->data.age);      
            printf("Sex: %s\n",node->data.sex);  
            printf("Final grade: %d\n",node->data.grade);       
            printf("\n");
            count++;
        }
        node = node->next;
    }
    if(count)
        printf("Displaying %d of %d student(s)\n",count,list->size);
    else
        printf("No student(s) found.\n");
}
void intFilter(SLList *list, int n){
    myNode *node = list->head;
    int numA = 0, numB = 0, count = 0;
    switch(n){
        case 0:
            scanf("%d-%d",&numA,&numB);
            break;
        case 1:            
            scanf("%d",&numA);
            break;
        default:
            break;
    }

    while(node != NULL){
        if(intCheck(node,numA,numB,n)){    
            printf("Student number: %d-%d\n",node->data.sNumA,node->data.sNumB);
            printf("Last name: %s\n",node->data.lastN);
            printf("First name: %s\n",node->data.firstN);
            printf("Course: %s\n",node->data.course);
            printf("Year level: %d\n",node->data.yearLevel);      
            printf("Age: %d\n",node->data.age);      
            printf("Sex: %s\n",node->data.sex);  
            printf("Final grade: %d\n",node->data.grade);                
            printf("\n");
            count++;
        }
        node = node->next;
    }
    if(count)
        printf("Displaying %d of %d student(s)\n",count,list->size);
    else
        printf("\nNo student(s) found.\n");
}

int stringCompare(char s1[], char s2[]){    
    for(int i=0;i<15;i++){
        if(toLower(s1[i])>toLower(s2[i]))
            return 1;        
        else if(toLower(s1[i])<toLower(s2[i]))            
            return 0;
        else
            continue;
    }
}

void menu(){
    printf("\n");
    printf("1. Enrol a student\n");
    printf("2. Drop a student\n");
    printf("3. Edit a student\n");
    printf("4. Display all students\n");
    printf("5. Filter students by last name\n");
    printf("6. Filter students by student number\n");
    printf("7. Filter students by year level\n");
    printf("8. Filter students by course\n");
    printf("9. Filter students by sex\n");
    printf("10. Filter students by passing\n");
    printf("11. Filter students by failing\n");
    printf("12. Sort students by last name\n");
    printf("13. Sort students by student number\n");
    printf("14. Exit\n");
    printf("\n");
    printf("? ");
}
void subMenu(myNode *node){
    printf("\nEdit %d-%d\n",node->data.sNumA,node->data.sNumB);
    printf("1. Student number\n");
    printf("2. Last name\n");
    printf("3. First name\n");
    printf("4. Course\n");
    printf("5. Year level\n");
    printf("6. Age\n");
    printf("7. Sex\n");
    printf("8. Final grade\n");
    printf("9. Back\n");
    printf("\n");
    printf("? ");
}
void subSelection(int n,SLList *list, myNode *node){
    switch(n){
        case 1:            
            printf("Student number: ");
            scanf("%d-%d",&node->data.sNumA,&node->data.sNumB);
            printf("\nStudent number updated!\n");
            break;
        case 2:
            printf("Last name: ");
            scanf("%s",&node->data.lastN);
            printf("\nLast name updated!\n");
            break;
        case 3:
            printf("First name: ");
            scanf("%s",&node->data.firstN);
            printf("\nFirst name updated!\n");
            break;
        case 4:
            printf("Course: ");
            scanf("%s",&node->data.course);
            printf("\nCourse updated!\n");
            break;
        case 5:           
            printf("Year level: ");
            scanf("%d",&node->data.yearLevel);
            printf("\nYear level updated!\n");
            break;
        case 6:
            printf("Age: ");
            scanf("%d",&node->data.age);
            printf("\nAge updated!\n");
            break;
        case 7:
            printf("Sex: ");
            scanf("%s",&node->data.sex);
            printf("\nSex updated!\n");
            break;
        case 8:
            printf("Final grade (%d): ",node->data.grade);
            scanf("%d",&node->data.grade);
            printf("\nFinal grade updated!\n");
            break;
        case 9:
            break;
        default:
            printf("Please enter a valid selection!\n");
            break;
    }
}
void selection(int n, SLList *list){
    myNode *node;
    int index;

    if(list->size==0 && (n!=1 && n!=14)){
        printf("Record is currently empty! Please enroll a student first.\n");
        return;
    }
    switch(n){
        case 1:
            printf("Enrol\n");
            insertItem(list,list->size);

            node = getItem(list,list->size-1);

            printf("\n");
            printf("%d-%d added!\n",node->data.sNumA,node->data.sNumB);
            break;
        case 2:
            printf("Drop a student\n");
            index = getIndex(list);

            if(index>=0){
                removeItem(list,index);
                printf("Student Dropped.\n");
            }
            else               
                printf("\nThis student is not enrolled.\n");
            
            break;
        case 3:
            index = getIndex(list);

            if(index>=0)
                setItem(list,index);
            else               
                printf("\nThis student is not enrolled.\n");

            break;
        case 4:
            displayAll(list);
            break;
        case 5:
            printf("Filter students by last name: ");
            strFilter(list,1);
            break;
        case 6:
            printf("Filter students by student number: ");
            intFilter(list,0);
            break;
        case 7:
            printf("Filter students by year level: ");
            intFilter(list,1);
            break;
        case 8:
            printf("Filter students by course: ");
            strFilter(list,2);
            break;
        case 9:
            printf("Filter students by sex: ");
            strFilter(list,3);
            break;
        case 10:
            printf("Filter students by passing:\n");
            intFilter(list,2);
            break;
        case 11:
            printf("Filter students by failing:\n");
            intFilter(list,3);
            break;
        case 12:
            printf("Sort students by last name:\n");
            stringSort(list);
            displayAll(list);
            break;
        case 13:
            printf("Sort students by student number:\n");
            intSort(list);
            displayAll(list);
            break;
        case 14:
            break;    
        default:
            printf("Please enter a valid selection!\n");
            break;
    }
}

char toLower(char ch){
    if(ch>=65 && ch<=90)
        return (int)ch+32;
    return ch;
}

char toUpper(char ch){
    if(ch>=97 && ch<=122)
        return (int)ch-32;
    return ch;
}

void intSort(SLList *list){
    myNode *node;
    myNode *nextNode;
    Data temp;
    int numA, numB;

    for(int i=0;i<list->size;i++){
        node = list->head;
        nextNode = node->next;
        
        for(int j = 0; j<list->size-1;j++){
            if(node->data.sNumA >= nextNode->data.sNumA){
                temp = node->data;
                node->data = nextNode->data;
                nextNode->data = temp;      
            } // Primary Checking

            if(node->data.sNumA >= nextNode->data.sNumA && node->data.sNumB >= nextNode->data.sNumB){
                temp = node->data;
                node->data = nextNode->data;
                nextNode->data = temp;                
            } // Secondary Checking

            node = nextNode;
            nextNode = nextNode->next;
        }
    }
}
void stringSort(SLList *list){
    myNode *node;
    myNode *nextNode;
    Data temp;
    int numA, numB;

    for(int i=0;i<list->size;i++){
        node = list->head;
        nextNode = node->next;
        
        for(int j = 0; j<list->size-1;j++){            
            if(stringCompare(node->data.lastN,nextNode->data.lastN)){
                temp = node->data;
                node->data = nextNode->data;
                nextNode->data = temp;                
            }

            node = nextNode;
            nextNode = nextNode->next;
        }
    }
}