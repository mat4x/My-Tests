//Reader-Writer Problem                     22/02/2022
#include <iostream>
#include <conio.h>          //for getch()
#include <unistd.h>         //for usleep
#include <thread>           //for multi-threading
#include <vector>           //for buffer
using namespace std;


int reader_count = 0,
    mutex = 1, writer_sem = 1,      //binary semaphores
    stop = 0, update = 0;           //flags

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
                //entry conditions
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
                //entry conditions
            else if( inp_flag && semWait(writer_sem) ){
                this->write();                  //critical section
                semSignal(writer_sem);

                inp_flag = false;
                update++;
            }
        usleep(200000);     //0.2 s
    }   }
};



int main(){
    cout << " This program simulates the working of the reader writer problem\
    \n Two readers R1 and R2 have been initiated as separate threads.\
    \n Two writers W1 and W2 have been initiated as separate threads.\n\
    \n The readers detect any input key presses and add the name to the bufffer\
    \n The writers read the data only when the buffer has been updated by the readers\n\
    \n If multiple inputs have been provided the readers and writers have to\
    \n managed such that resource allocation is properly done.\
    \n [Press ` key to exit program]\n\n";

    Reader r1("R1");
    Reader r2("R2");

    Writer w1("W1");
    Writer w2("W2");

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
