//Page Replacement Algorithms               14/03/2022
#include <iostream>
#include <vector>
using namespace std;

int n_frames, n_pages;              //number of frames and pages
vector<int> page_ref;               //page reference string

void print_frame_state(int &frames[n_frames]){
    cout << "| ";
    for( int i=0; i<n_frames; i++ )
        cout << frames[i] << "  ";
    cout << '|';
}

bool hit_or_miss(){
    //I guess they never miss, huh?
}

void fifo_algorithm(){
    int frames[n_frames], pointer = 0;
    for( int i=0; i<n_pages; i++ ){

    }
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

    fifo_algorithm();


    return 0;
}


/*
    TESTING
3
10
4 7 6 1 7 6 1 2 7 2

https://www.gatevidyalay.com/page-replacement-algorithms-page-fault/
*/
