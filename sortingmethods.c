#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>

#define GREY "\033[90m"
#define RED "\033[0;31m"
#define WHITE "\033[97m"
void swap(int *a,int *b){
    int temp =*a;
    *a=*b;
    *b=temp;
}
void random_fill(int n, int arr[n],int b){
    srand(time(NULL));
    for(int i=0;i<n;i++){
        int num=rand()%(b+1);
        printf(GREY"number generated!:(%d) \n" WHITE,num);
        arr[i]=num;
    }
}
int partition(int n,int arr[n],int low,int high){
 int p=arr[low];
 int i=low;
 int j=high;
    while (i<j){
        while (arr[i]<=p && i<high){
            i++;
        }
        while (arr[j]>p){
            j--;
        }
        if (i<j){
            swap(&arr[i],&arr[j]);
        }
    }   
    swap(&arr[low],&arr[j]);
    return j;
}
void merge(int arr[],int l,int m, int r){
    int i,j,k;
    int n1=m-l+1;
    int n2=r-m;
    int L[n1],R[n2];
    for (i=0;i<n1;i++){
        L[i]=arr[l+i];
    }
    for (j=0;j<n2;j++){
        R[j]=arr[m+1+j];
    }
    i=0;
    j=0;
    k=l;
    while (i<n1 && j<n2){
        if (L[i]<=R[j]){
            arr[k]=L[i];
            i++;
        }else{
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while (i<n1){
        arr[k]=L[i];
        i++;
        k++;
    }
    while (j<n2){
        arr[k]=R[j];
        j++;
        k++;
    }
}
void sort_bubble(int n, int arr[n]){
    for (int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if (arr[j]>arr[j+1]){
                //printf(GREY"SWAPING...\n"WHITE);
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}
void sort_selection(int n,int arr[n]){
    int min=0;
    for (int i=0;i<n-1;i++){
        min=i;
        for(int j=i;j<n;j++){
            if (arr [min]>arr [j]){
                min=j;
                //printf(GREY"@%d value%d \n"WHITE,min,arr[min]);
            }
        }
        //printf(GREY"SWAPING...\n"WHITE);
        swap(&arr[min],&arr[i]);
    }
}
void sort_insertion(int n, int arr[n]){
    for (int i=1;i<n;i++){
        int key =arr[i];
        int j=i-1;
        while( j>=0 && key < arr[j] ){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}
void merge_sort(int n,int arr[n],int l,int r){
    if (l<r){
        int m=l+(r-l)/2;
        merge_sort(n,arr,l,m);
        merge_sort(n,arr,m+1,r);
        merge(arr,l,m,r);
    }
}
void quicksort(int n,int arr[n]){
    int low=0;
    int high=n-1;
    if (low<high){
        int pi=partition(n,arr,low,high);
        quicksort(pi,arr);
        quicksort(n-pi-1,&arr[pi+1]);
    }
}
void display(int n,int arr[n]){
    for (int i=0;i<n;i++){
        printf("[%d]",arr[i]);
    }
    
}

int main(){
    LARGE_INTEGER start, end, freq;
    int n,check,a,b;
    FILE *pFILE=fopen("output.txt","w");
    printf(RED"this is a sorting library, it fills and sorts!\n"WHITE);
    printf("choose the sorting algorithm you desire: \n");
    printf("1: bubble sort\n2: selection sort\n3: insertion sort\n4: merge sort\n5: quicksort\n");
    scanf("%d",&check);
    while (check<=0 || check>5){
        printf(RED"please sellect a valid input"WHITE);
        scanf("%d",&check);
    }
    printf("enter the size of the array n=");
    scanf("%d",&n);
    int arr[n];
    printf("chose the range of the random numbers from zero to:\n");
    scanf("%d",&b);
    random_fill(n,arr,b);
    switch (check){
        case 1:{
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);
            sort_bubble(n,arr);
            QueryPerformanceCounter(&end);
            double time_taken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
            display(n,arr);
            printf(RED"\nTime: %.9f seconds\n"WHITE, time_taken);
            }
        break;
        case 2: {
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);
            sort_selection(n,arr);        
            QueryPerformanceCounter(&end);
            double time_taken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
            display(n,arr);
            printf(RED"\nTime: %.9f seconds\n"WHITE, time_taken);
            }
        break;
        case 3:{
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);
            sort_insertion(n,arr);
            QueryPerformanceCounter(&end);
            double time_taken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
            display(n,arr);
            printf(RED"\nTime: %.9f seconds\n"WHITE, time_taken);
            }
        break;
        case 4:{
            printf("mergesort started...\n");
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);
            merge_sort(n,arr,0,n-1);

            QueryPerformanceCounter(&end);
            double time_taken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
            display(n,arr);
            printf(RED"\nTime: %.9f seconds\n"WHITE, time_taken);
        }
        break;
        case 5:{
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);
            quicksort(n,arr);
            QueryPerformanceCounter(&end);
            double time_taken = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
            display(n,arr);
            printf(RED"\nTime: %.9f seconds\n"WHITE, time_taken);
        }
        break;

    }



    if (pFILE==NULL){
        printf(RED"error opening file,too bad!\n"WHITE);
        fclose(pFILE);
        return 1;
    }else{
    fprintf(pFILE,"%d",n);
    fprintf(pFILE,"\n");
    for (int i;i<n;i++){
        fprintf(pFILE,"%d",arr[i]);
        fprintf(pFILE,"\n");
    }
    }
    fclose(pFILE);
    return 1;
}