#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b) 
{ return (a > b) ? a : b; } //to find and return maximum of given inputs
 
void swap(float* a, float* b) //to swap two float inputs 
{ 
    float t = *a; 
    *a = *b; 
    *b = t; 
} 
void swap_int(int* a, int* b) //to swap two int inputs
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
}  
int partition (float arr[],int val[],int wt[],int order[], int low, int high) 
{ 
    float pivot = arr[high];   
    int i = (low - 1);
	int j;   
  
    for (j = low; j <= high- 1; j++) 
    { 
        if (arr[j] > pivot) 
        { 
            i++;    
            swap(&arr[i], &arr[j]);
			swap_int(&val[i], &val[j]);
			swap_int(&wt[i], &wt[j]); 
			swap_int(&order[i], &order[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]);
    swap_int(&val[i+1], &val[high]);
	swap_int(&wt[i+1], &wt[high]); 
	swap_int(&order[i+1], &order[high]); 
    return (i + 1); 
} 
  

void quickSort(float arr[],int val[],int wt[],int order[], int low, int high) 
{ //quick sort algorithm,sort according to the ratio but sort all of the values with it
    if (low < high) 
    { 
        int pi = partition(arr,val,wt,order, low, high); 
        quickSort(arr,val,wt,order, low, pi - 1); 
        quickSort(arr,val,wt,order, pi + 1, high); 
    } 
} 

void knapSack(int val[], int wt[], int n, int W) 
{ 
		int i,j,cap=0,value=0;
		float ratio[n];//to keep value/weight ratio
		int zero_one[n];//to keep include or not situation 0 not included 1 included
		int remain,max_index=0;
		int max=0;
		int order[n];//after sorting remembering their first position to write output in first order
		int msec2=0;
		
		clock_t timer2 = clock();//start second timer
		
		for(i=0;i<n;i++){
			ratio[i]=(float)(val[i])/(float)(wt[i]);//get the ratio for all inputs
		}
		
		for(j=0;j<n;j++){
			order[j]=j;	}		//to keep sorted values first order
			
		quickSort(ratio,val,wt,order, 0, n-1); //sort arrays acc to ratio values
		
		for(j=0;j<n;j++){
			zero_one[j]=0;	}		//make all not included for start
		i=0;
		
		while((cap!=W)&&(i<n)){ //continue until knapsack capacity is full or there is no left item
			//if corresponding item is not used and knapsack can take in that item
			if(wt[i]<W-cap){
				zero_one[order[i]]=1;//include that item
				cap+=wt[i];//increase capacity with that items capacity
				value+=val[i];//increase value with that items value
			}
		i++;	
		}
		
		
	clock_t end_timer2 = clock()-timer2;//end timer 2
	msec2 = end_timer2 * 1000 / CLOCKS_PER_SEC;//calculate time in sec
	printf("Time taken to compute greedy algorithm %d seconds %d milliseconds\n",msec2/10000,msec2%10000);

		FILE *file2;//to write output
		file2 = fopen("output-test1d.dat","w"); //open output file to write
		fprintf(file2,"%d\n",value);//write total value in the first line
		for(i=0;i<n;i++){
			fprintf(file2,"%d\n",zero_one[i]);//write each items includeness
		}
		fclose(file2);//close file
} 

main()  
{ 
		FILE *file;
		file = fopen("test1d.dat", "r+");//open input file to read
		int n,W;
		
		int msec1 = 0;
		clock_t timer1 = clock();//start first timer
		
		fscanf(file,"%d",&n);//read first value for item number n
		fscanf(file,"%d",&W);//read second value for total capacity W
		int val[n];//to keeps items values
		int wt[n];//to keep items weight values
		int i=0;
		while (i<n) {//read items
			fscanf(file,"%d",&val[i]);//first is value
			fscanf(file,"%d",&wt[i]);//second is weight
			i++;
		}

		knapSack(val,wt, n,W); //call knapsack function

		clock_t end_timer1 = clock()-timer1;//end first timer
		msec1 = end_timer1 * 1000 / CLOCKS_PER_SEC;//turn timer value into sec
		printf("Time taken to execute whole program %d seconds %d milliseconds\n",msec1/1000, msec1%1000);
		//prompt the user
		fclose(file);//close input file
		
} 


