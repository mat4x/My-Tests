//Reader-Writer Problem  22/02/2022
#include <iostream>
#include <conio.h>          //for getch()
#include <unistd.h>         //for usleep
#include <thread>           //for multi-threading
#include <vector>
using namespace std;


/*
writer takes single char input from user
Reader reads if anything new

press ` to exit
*/


int reader_count = 0,
    mutex = 1, writer_sem = 1,                  //Binary semaphores
    stop = 0, update = 0;

vector<char> buffer;


bool semWait(int &n){
    if( n>0 ){
        n--;
        return true;}
    return false;
}

bool semSignal(int &n){
    n++;
}


class Reader{
public:
    string name;

    Reader(string name){
        this->name = name;}

    void read(){
        cout << name << " is reading:\t\t";
        for (auto i = buffer.begin(); i!=buffer.end(); ++i)
            cout << *i;
        cout << '\n';
    }

    void start(){
        while(!stop){
            /*Entry code*/
            if( update > 0 && semWait(mutex) ){ //reader only reads if there are new updates in the buffer
                update = 0;
                reader_count++;
                if (reader_count == 1) semWait(writer_sem);
                semSignal(mutex);

                this->read();                   //critical section

                /*Exit code*/
                semWait(mutex);
                reader_count--;
                if (reader_count == 0) semSignal(writer_sem);
                semSignal(mutex);
                }
        usleep(300000);     //0.3 s
        }
    }
};


class Writer{
public:
    string name;
    char inp;
    bool inp_flag = false;

    Writer(string name){
        this->name = name;}

    void write(){
        buffer.push_back(inp);
        cout << name << " received and updated data.\n";
    }

    void start(){
        while(!stop){
            if(!inp_flag){
                inp_flag = true;
                inp = _getch();
                if (inp == '`') stop = 1;
            }

            else if( inp_flag && semWait(writer_sem) ){
                this->write();                  //Critical section
                semSignal(writer_sem);

                inp_flag = false;
                update++;
            }
        usleep(200000);     //0.2 s
    }   }
};



int main(){
    Reader r1("R1");
    Reader r2("R2");

    Writer w1("W1");
    Writer w2("W2");

    //TESTING
    thread r1_thread( &Reader::start, r1 );
    thread r2_thread( &Reader::start, r2 );

    thread w1_thread( &Writer::start, w1 );
    thread w2_thread( &Writer::start, w2 );

    r1_thread.join();
    r2_thread.join();
    w1_thread.join();
    w2_thread.join();

    cout << "Program terminated...\n";

    return 0;
}
