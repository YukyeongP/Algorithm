#include <iostream>
#include <istream>

#include <cstring> // strcpy
#define NAME_SIZE 10 
#define HEAP_SIZE 30

using namespace std;


//declaration each element in heap
typedef struct element{
    char name[NAME_SIZE+1];
    float score;
} Element;

//declaration heap structure
typedef struct heap{
    Element data[HEAP_SIZE+1];
    int data_num; //the number of datas in heap
} Heap;

//initialize heap
void init_heap(Heap* heap){
    heap->data_num = 0;
    //(*heap).data_num =0;
}

//parent index
int parent_idx(int index) {
    return index / 2;
}

//left child index
int left_child_idx(int index) {
    return index * 2;
}

//right child index
int right_child_idx(int index) {
    return index * 2 + 1;
}

//heap swap
void swap(Heap* heap, int idx1, int idx2){
    Element tmp;
    strcpy(tmp.name, heap->data[idx1].name);
    tmp.score = heap->data[idx1].score;

    strcpy(heap->data[idx1].name, heap->data[idx2].name);
    heap->data[idx1].score = heap->data[idx2].score;

    strcpy(heap->data[idx2].name, tmp.name);
    heap->data[idx2].score = tmp.score;
}

//going up and comparing and swapping values in heap
void up(Heap* heap, int index){
    // not root and parent > child, then swap the heap
    while (index!=1 && heap->data[parent_idx(index)].score > heap->data[index].score){
        swap(heap, parent_idx(index), index);
        index=parent_idx(index); //index위치가 parent idx로
    }
}

//insert the name and the score into heap
void insert_heap(Heap* heap, const char* name, float score){
    Element elem;

    strcpy(elem.name, name);
    elem.score = score;

    heap->data_num++;
    heap->data[heap->data_num] = elem; 

    up(heap, heap->data_num); // compare and swap the value by upwarding
    
}

//decrease key of element in queue
void decrease_key_heap(Heap* heap, int index, float score){
    //change value according to input index
    heap->data[index].score = score;
           
    //going up and comparing values
    up(heap, index);
}

//return lower priority child index
int lower_score_childidx(Heap* heap, int idx){
    //no child node
    if(left_child_idx(idx) > heap->data_num)
        return 0;
    else if(left_child_idx(idx) == heap->data_num)
        return left_child_idx(idx);
    else{
        //left child's score is higher than right
        if(heap->data[left_child_idx(idx)].score > heap->data[right_child_idx(idx)].score)
            return right_child_idx(idx); //return right
        else
            return left_child_idx(idx); //return left
    }
}

//delete the smallest element from the heap
Element delete_heap(Heap* heap){
    Element last_elem = heap->data[heap->data_num];

    int parent_idx = 1;
    int child_idx;

    printf("[%s,%.1f] is deleted.", heap->data[1].name, heap->data[1].score);
    
    //compare the score (priority) between left and right child
    //if left is smaller than right, left will be root element
    while(child_idx = lower_score_childidx(heap, parent_idx)){
        if(last_elem.score <= heap->data[child_idx].score)
            break;
        heap->data[parent_idx] = heap->data[child_idx]; 
        parent_idx = child_idx; //last node index
    }
    heap->data[parent_idx] = last_elem;
    heap->data_num -= 1;
    
    return last_elem;
    
}

//print menu
void print_menu(){
    cout << "\n\n********* MENU *********\n";
    cout << "I : Insert new element into queue\n";
    cout << "D : Delete element with smallest key from queue\n";
    cout << "C : Decrease key of element in queue\n";
    cout << "P : Print out all elements in queue\n";
    cout << "Q : Quit";
    cout << "\nChoose menu:";
}

int main(){
    Heap heap;
    char menu; 
    init_heap(&heap); 

    while(1){
        print_menu();
        cin >> menu;

        //insert the elements into heap
        if(menu=='I'){
            char input_name[NAME_SIZE+1];
            float input_score;
            cout << "Enter name of element: ";
            cin >> input_name;
            cout << "Enter key value of element: ";
            cin >> input_score;

            insert_heap(&heap, input_name, input_score);

            printf("[%s,%.1f]", input_name, input_score);
        
        //delete element with smallest key from queue
        }else if(menu=='D'){
           delete_heap(&heap);

        //decrease key of element in queue
        }else if(menu=='C'){
            int input_idx;
            float input_newscore;

            cout << "Enter index of element: ";
            cin >> input_idx;
            cout << "Enter new key value: ";
            cin >> input_newscore;

            decrease_key_heap(&heap, input_idx, input_newscore);

        //print out all elements in queue
        }else if(menu=='P'){
            for (int i = 1; i <= heap.data_num; i++)
                printf("[%s,%.1f]", heap.data[i].name, heap.data[i].score);

        //terminate program
        }else if(menu=='Q'){
            cout << "Thank you, Bye!\n";
            break;
        }else{
            cout << "Try again!\n";
            continue;
        }
        
    }
    return 0;
}