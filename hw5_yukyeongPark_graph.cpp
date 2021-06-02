#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Reference : https://sarah950716.tistory.com/12#footnote_link_12_1

using namespace std;
#define ROW 9 
#define COL 9

string arr[ROW][COL]; // original graph's matrix
string transp_arr[ROW][COL]; //transpose graph's matrix

int main(){
    int row = 0;
    int col = 1;
    vector<string> adj[9]; // Array of adjacency list
    
    //Read file and store data in 2D-array
    ifstream fin("C:/Users/byk11/Downloads/hw5_.data.txt");
    while(!fin.eof()){
        fin >> arr[row][col];
        col++;
        if(col%9==0){
            row++;
            col=0;
        }
    }
    fin.close();

    //1) original graph
    cout << "\nOriginal";
    for(int i=0; i<ROW; i++){
        cout << "\n";
        for(int j=0; j<COL; j++){
            cout << arr[i][j] << " ";
            transp_arr[j][i] = arr[i][j];
        }
    }

    //Array of adjacency list of above graph
    cout << "\n\n<<Array of adjacency list of above graph>>";
    for(int i=1; i<ROW; i++){
        cout << "\nAdjacency node with " << arr[i][0] << "\n";
        for(int j=0; j<COL; j++){
            if(!arr[i][j].compare("1")){
                cout << "adj: " << arr[0][j] << endl;
                adj[i].push_back(arr[0][j]);
            }
        }
    }
	
    //2) Transpose graph
    cout << "-------------------------------------" << "\nTransp";
    for (int i = 0; i < COL; ++i){
        cout << "\n";
        for (int j = 0; j < ROW; ++j) {
            cout << transp_arr[i][j] << " ";
        }
    }
    
    // Array of adjacency list of transpose graph
    cout << "\n\n<<Array of adjacency list of transpose graph>>";
    for(int i=1; i<ROW; i++){
        cout << "\nAdjacency node with " << transp_arr[i][0] << "\n";
        for(int j=0; j<COL; j++){
            if(!transp_arr[i][j].compare("1")){
                cout << "adj: " << transp_arr[0][j] << endl;
                adj[i].push_back(transp_arr[0][j]);
            }
        }
    }
    return 0;
   
}
