#include <iostream>
#include <istream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <tuple>
#include <chrono>

#define MAX_NUM_OF_ITEMS 12000
#define MAX_WEIGHT 12000*3 //maximum size

using namespace std;

typedef struct items{
    int value;
    int weight;
    float vw; //for Greedy
   
} Items;

Items items[MAX_NUM_OF_ITEMS];
int B[MAX_NUM_OF_ITEMS][MAX_WEIGHT];

bool compare(const Items& a, const Items& b){
    return a.vw>b.vw;
}

//Dynamic programming solution
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

//Greedy solution
int knapsack_Greedy(int n){
    int W = n*40;
    int w,i;
    float max_benefit=0;

    //decreasing order sorting
    sort(items, items+(n+1), compare);

    for(i=0; i<=n; i++){
        if(items[i].weight < W){ //if I can put items, (current weight is smaller than maximum weight)
            W -= items[i].weight; //put items and current weight decreases.
            max_benefit = max_benefit + items[i].value; //change the current value
        }else{  //if I can't, do fraction
            float frac = items[i].weight = W/items[i].weight;
            max_benefit += (items[i].value)*frac;
            break;
        }        
    }
    return max_benefit;
}


int main(){
    clock_t DP_start, DP_finish, GD_start, GD_finish;
    double DP_duration, GD_duration;
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

        //Greedy
        GD_start = clock();   
        int GD_result = knapsack_Greedy(numOfItems[i]); 
        GD_finish = clock();
        GD_duration = (double)(GD_finish-GD_start)/CLOCKS_PER_SEC;

        cout << numOfItems[i] << "\t" << DP_duration << "ms / " << DP_result << "\t\t" << GD_duration << "ms / " << GD_result << "\n";   

        //write file
        output << numOfItems[i] << "\t" << DP_duration << "ms / " << DP_result << "\t\t" << GD_duration << "ms / " << GD_result << "\n";   

    }
    
    output.close();

    return 0;

}
