#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

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
void dividenconquer_sort(int n,int arr[n]){
    //this is just a test function to understand how to implement divide and conquer algorithms(thanks copilot)
    //so ill use as many notes as i want
    int mid,left,right,mid2;
    bool sorted=false;
    int *TARR1;
    int *TARR2;
    //this suction is just for deviding the array into two halves
    if (n % 2 == 0){
        mid=n/2;
        mid2=mid;
        TARR1=(int *)malloc(mid*sizeof(int));
        TARR2=(int *)malloc(mid2*sizeof(int));
        printf("%d",mid);
    }else{
        mid=(n/2)+1;
        mid2=mid-1;
        TARR1=(int *)malloc(mid*sizeof(int));
        TARR2=(int *)malloc(mid2*sizeof(int));
        printf("%d",mid);
    }
    //------------------------------------------
    //this one for filling the two temporary arrays and sorting them
    for(int i = 0;i<mid;i++){
        TARR1[i]=arr[i];
    }
    for (int j=0;j<mid2;j++){
        TARR2[j]=arr[mid2+j];
    }
    //wished to use qucik sort, didnt make a function for it, too bad!
    sort_insertion(mid,TARR1);
    sort_insertion(mid2,TARR2);
    while(sorted==false){
        left=0;
        right=0;
        for(int k=0;k<n;k++){
            if (left<mid && right<mid2){
                if (TARR1[left]<TARR2[right]){
                    arr[k]=TARR1[left];
                    left++;
                }else{
                    arr[k]=TARR2[right];
                    right++;
                }
            }else if (left<mid){
                arr[k]=TARR1[left];
                left++;
            }else if (right<mid2){
                arr[k]=TARR2[right];
                right++;
            }
        }
        sorted=true;
    }

}
void display(int n,int arr[n]){
    for (int i=0;i<n;i++){
        printf("[%d]",arr[i]);
    }
    
}

int main(){
    int n,check,a,b;
    FILE *pFILE=fopen("output.txt","w");
    printf(RED"this is a sorting library, it fills and sorts!\n"WHITE);
    printf("choose the sorting algorithm you desire: \n");
    printf("1: bubble sort\n2: selection sort\n3: insertion sort\n4: divide and conquer sort\n");
    scanf("%d",&check);
    while (check<=0 || check>4){
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
            clock_t start=clock();
            sort_bubble(n,arr);
            clock_t end=clock();
            double time_taken=((double)(end-start))/CLOCKS_PER_SEC;
            printf("bubble sort took %f seconds\n",time_taken);
            }
        break;
        case 2: {
            clock_t start=clock();
            sort_selection(n,arr);        
            clock_t end=clock();
            double time_taken=((double)(end-start))/CLOCKS_PER_SEC;
            printf("selection sort took %f seconds\n",time_taken);
            }
        break;
        case 3:{
            clock_t start=clock();
            sort_insertion(n,arr);
            clock_t end=clock();
            double time_taken=((double)(end-start))/CLOCKS_PER_SEC;
            printf("insertion sort took %f seconds\n",time_taken);
            }
        break;
        case 4:{
            clock_t start=clock();
            dividenconquer_sort(n,arr);
            clock_t end=clock();
            double time_taken=((double)(end-start))/CLOCKS_PER_SEC;
            printf("divide and conquer sort took %f seconds\n",time_taken);
        }
        break;
    }
    display(n,arr);
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