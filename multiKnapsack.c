
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
        if (arr[j] > pivot) //if the values are in reverse place according to the pivot 
        { 
            i++;    //swap the values ith and jth
            swap(&arr[i], &arr[j]);
			swap_int(&val[i], &val[j]);
			swap_int(&wt[i], &wt[j]); 
			swap_int(&order[i], &order[j]); 
        } 
    } //
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

void knapSack(int val[], int wt[], int n, int m, int W[]) 
{ 
		int i,j,k,cap=0,value=0,used=0;
		float ratio[n];//to keep value/weight ratio
		int zero_one[n][m];//to keep include or not situation 0 not included 1 included, n values for m knapsack
		int remain,max_index=0;
		int max=0;
		int order[n];//after sorting remembering their first position to write output in first order
		int msec2=0;
		clock_t timer2 = clock(); //start second timer
		
		for(i=0;i<n;i++){
			ratio[i]=(float)(val[i])/(float)(wt[i]); //get the ratio for all inputs
		}
		
		for(j=0;j<n;j++){
			order[j]=j;			//to keep sorted values first order
		}
	
		quickSort(ratio,val,wt,order, 0, n-1); //sort arrays acc to ratio values
		
		for(k=0;k<m;k++){
			for(j=0;j<n;j++){
				zero_one[j][k]=0;			//make all not included for start
			}
		}
		
		i=0;
	for(k=0;k<m;k++){//loop for all the existing knapsacks
		//continue until knapsack capacity is full or there is no left item for the corresponding knapsack
		while((cap!=W[k])&&(i<n)){
			for(j=0;j<k;j++){//loop for all knapsacks before current knapsack 
			if(zero_one[i][j]==1){//look if the ith item is used before or not?
				used=2;//keep used=2 as an info for it is used
			}
			}
			//if corresponding item is not used and knapsack can take in that item
			if((wt[i]<W[k]-cap)&&(used==0)){
				zero_one[order[i]][k]=1;//include that item
				cap+=wt[i];//increase capacity with that items capacity
				value+=val[i];//increase value with that items value
			}
		i++;
		used=0;	//make used  value 0 for next item
		}
		cap=0;i=0,used=0;//make all of them 0 for next knapsack
	}
	
	clock_t end_timer2 = clock()-timer2;//end second timer
	msec2 = end_timer2 * 1000 / CLOCKS_PER_SEC;//turn timer to sec
	printf("Time taken to compute greedy algorithm %d seconds %d milliseconds\n",msec2/1000,msec2%1000);
	//prompt user
		
		
		FILE *file2;//output file
		file2 = fopen("output-test2e.dat","w");//open new file to write
		fprintf(file2,"%d\n",value);//in the first line write total value
		for(i=0;i<n;i++){//for all items
			for(k=0;k<m;k++){//for all knapsacks
				fprintf(file2,"%d",zero_one[i][k]);//write situation for that item on that knapsack
			}
			fprintf(file2,"\n");
		}
		fclose(file2);//close output file
} 

int main()  
{ 
		FILE *file;//for input file
		file = fopen("test2e.dat", "r+");//open file to read
		int n,m;
		int msec1 = 0;
		clock_t timer1 = clock();//start first timer
		fscanf(file,"%d",&n);//read first value for item number n
		fscanf(file,"%d",&m);//read second value for number of knapsacks
		int val[n];//to keeps items values
		int wt[n];//to keep items weight values
		int W[m];//to keep knapsacks total weight
		int i;
		for(i=0;i<m;i++){//loop as much as thee knapsack number
			fscanf(file,"%d",&W[i]);//read total weight for each knapsack
		}
		i=0;
		while (i<n) {//read items
			fscanf(file,"%d",&val[i]);//first is value
			fscanf(file,"%d",&wt[i]);//second is weight
			i++;
		}

		knapSack(val,wt,n,m,W);//call knapsack function
		 
		clock_t end_timer1 = clock()-timer1;//end first timer
		msec1 = end_timer1 * 1000 / CLOCKS_PER_SEC;//turn timer value into sec
		printf("Time taken to execute whole program %d seconds %d milliseconds\n",msec1/1000, msec1%1000);
		//prompt the user
		fclose(file);//close input file
		
	return 61;
} 

