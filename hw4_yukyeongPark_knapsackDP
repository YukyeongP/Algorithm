#include <iostream>
#include <istream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <tuple>
#include <chrono>

#define MAX_NUM_OF_ITEMS 12000
#define MAX_WEIGHT 12000*3 //maximum size

//Knapsack Problem with Dynamic Programming solution

using namespace std;

typedef struct items{
    int value;
    int weight;
} Items;

Items items[MAX_NUM_OF_ITEMS];
int B[MAX_NUM_OF_ITEMS][MAX_WEIGHT];

int knapsack_DP(int n){
    int W = n*40;
    int w,i;

    //generate random number for each items' value and weight
    for(i=1; i<=n; i++){
        items[i].value=rand()%300+1;
        items[i].weight=rand()%100+1;
    }

    for(w=0; w<=W; w++)
        B[0][w]=0; //initialize    
    for(i=1; i<=n; i++){
        B[i][0]=0; //initialize    
        for(w=1; w<=W; w++){
            if(items[i].weight <= w){ //if maxweight is bigger than current weight,
                B[i][w] = max(B[i-1][w], B[i-1][w-items[i].weight] + items[i].value); //take maximum into table
            }else B[i][w] = B[i-1][w]; // else if current weight is smaller than maxweight 
        }
    }

    return B[n][W];
}


int main(){
    clock_t DP_start, DP_finish;
    double DP_duration;
    int numOfItems[8] = {100,1000,2000,4000,6000,8000,10000,12000};

    cout << "-----------------------------------------------\n" 
    << "  Num  | (Processing time/Maximum benefit value)\n" 
    << "   of  |---------------------------------------\n"
    << " Items |\tD.P.\t\tGreedy\n" 
    << "-----------------------------------------------\n";

    //Write file
    ofstream output("output.txt");
    output << "-----------------------------------------------\n" 
    << "  Num  | (Processing time/Maximum benefit value)\n" 
    << "   of  |---------------------------------------\n"
    << " Items |\t\t\t\tD.P.\t\t\t\t\tGreedy\n" 
    << "-----------------------------------------------\n"; 
    
    for (int i = 0; i < sizeof(numOfItems) / sizeof(int); i++){
        //Dynamic Programming
        DP_start = clock();   
        int DP_result = knapsack_DP(numOfItems[i]); 
        DP_finish = clock();
        DP_duration = (double)(DP_finish-DP_start)/CLOCKS_PER_SEC;

        cout << numOfItems[i] << "\t" << DP_duration << "ms / " << DP_result << "\n";   
        output << numOfItems[i] << "   \t\t" << DP_duration << "ms / " << DP_result << "\n";    //write file
 
    }
    
    output.close();

    return 0;

}
