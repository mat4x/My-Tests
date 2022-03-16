//Page Replacement Algorithms               14/03/2022
#include <iostream>
#include <vector>
using namespace std;

int n_frames, n_pages;              //number of frames and pages
vector<int> page_ref;               //page reference string

void print_frame_state(int frames[]){
    cout << "| ";
    for( int i=0; i<n_frames; i++ ){
        if( frames[i] == -1 )
            cout << '-';
        else
            cout << frames[i];
        cout << "  ";
        }
    cout << '|';
}

bool page_hit(int frame[], int page){
    for( int i=0; i<n_frames; i++ ){
        if( frame[i] == page )
            return true;
    }
    return false;
}

void fifo_algorithm(){
    int frames[n_frames], pointer = 0, page_fault = 0;

    for( int i=0; i<n_frames; i++ )
        frames[i] = -1;

    for( int i=0; i<n_pages; i++ ){
        if( !page_hit(frames, page_ref[i]) ){
            frames[pointer] = page_ref[i];
            page_fault++;
            pointer = (pointer+1)%n_frames;
        }
        cout << ' ' << page_ref[i] << ' '; print_frame_state(frames); cout << '\n';
    }
    cout << " Page Faults: " << page_fault << '\n';
}

void lru_algorithm(){
    int frames[n_frames], pointer = 0, page_fault = 0;


}


int main(){

    cout << " Page Replacement Algorithms\n";
    cout << "   Enter number of page frames\t\t:";      cin >> n_frames;
    cout << "   Enter number of pages to reference\t:"; cin >> n_pages;
    cout << " Enter page reference string\n   : ";

    int page;
    for( int i=0; i<n_pages; i++ ){
        cin >> page;
        page_ref.push_back(page);
    }

    /*for( int i=0; i<n_pages; i++ )
        cout << page_ref[i] << ' ';*/

    cout << string(50, '-') << '\n';
    fifo_algorithm();
    cout << string(50, '-') << '\n';


    return 0;
}


/*
    TESTING
3
10
4 7 6 1 7 6 1 2 7 2

https://www.gatevidyalay.com/page-replacement-algorithms-page-fault/


4
14
7 0 1 2 0 3 0 4 2 3 0 3 2 3

3
20
7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
*/
