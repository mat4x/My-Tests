//Memory Management                         13/03/2022
#include <iostream>
#include <vector>
using namespace std;


struct Partition{
    int number, par_size, free_size;

    Partition(int number, int par_size){
        this->number    = number;
        this->par_size  = par_size;
        this->free_size = par_size;
    }

    void allocate(int process_size){
        free_size -= process_size;
    }

    void print(){
        cout << " Partition" << number << '\t' << par_size << "KB\t" << free_size << "KB\n";
    }
};


struct Process{
    int number, process_size, partition_number = 0;

    Process(int number, int process_size){
        this->number       = number;
        this->process_size = process_size;
    }

    bool allocate(Partition &par){
        //method return true if process was allocated
        if( par.free_size >= process_size ){
            par.allocate(this->process_size);
            this->partition_number = par.number;
            return true;}
        return false;
    }

    void print(){
        cout << " P" << number << '\t' << process_size << "KB" << '\t';
        if( partition_number != 0 )
            cout << "  Partition " << partition_number << '\n';
        else
            cout << "  Unallocated\n";
    }
};


vector<Partition> partitions;   //memory
vector<Process> processes;      //processes
int par_n, pr_n;                //number of partitions and processes


void print_memory( vector<Partition> memory){
    for( int i=0; i != par_n; i++ )
        memory[i].print();
}

void print_processes( vector<Process> process_list){
    for( int i=0; i!=pr_n; i++ )
        process_list[i].print();
}


//First Fit
void first_fit(){
    int int_fragmenattion = 0, ext_fragmenattion = 0, flag = 0;
    vector<Partition> t_partitions = partitions;        //temporary copy of partitions
    vector<Process>   t_processes  = processes;         //temporary copy of processes

    /*Iterate through all the processes.
      For each process check if process size <= partition size.
      If a suitable partition is found,
      assign it the partition number and reduce free_size.
      If the process was unallocated (flag=0), add it's size as external fragmentation.*/
    for( int pr=0; pr<pr_n; pr++){
        flag = 0;
        for( int pt=0; pt<par_n; pt++){
            if( t_processes[pr].allocate(t_partitions[pt]) ){
                flag = 1;
                break;}
            }
        if( !flag )
            ext_fragmenattion += t_processes[pr].process_size;
    }

    for( int pt=0; pt<par_n; pt++){
        if( t_partitions[pt].par_size != t_partitions[pt].free_size )
            int_fragmenattion += t_partitions[pt].free_size;
    }

    cout << "     [First Fit Algorithm]\n";
    print_processes( t_processes );
    cout << "\n Internal Fragmentation\t: " << int_fragmenattion << "KB\n";
    cout << " External Fragmentation\t: " << ext_fragmenattion << "KB\n";
}


//Best Fit
void best_fit(){
    int int_fragmenattion = 0,
        ext_fragmenattion = 0,
        flag, par_sel;
    vector<Partition> t_partitions = partitions;        //temporary copy of partitions
    vector<Process>   t_processes  = processes;         //temporary copy of processes

    /*Iterate through all the processes.
      For each process check which partition results to minimum internal fragmentation.
      Assign the process the partition number and reduce free_size.
      If the process was unallocated (flag=0), add it's size as external fragmentation.*/
    for( int pr=0; pr<pr_n; pr++ ){
        flag = 0, par_sel = -1;
        for( int pt=0; pt<par_n; pt++ ){
            if( t_partitions[pt].free_size >= t_processes[pr].process_size ){
                flag = 1;
                if( par_sel == -1)
                    par_sel = pt;
                else if( t_partitions[pt].free_size <= t_partitions[par_sel].free_size )
                    par_sel = pt;
            }
        }
        if( flag )
            if( !t_processes[pr].allocate(t_partitions[par_sel]) )
                ext_fragmenattion += t_processes[pr].process_size;
    }

    for( int pt=0; pt<par_n; pt++){
        if( t_partitions[pt].par_size != t_partitions[pt].free_size )
            int_fragmenattion += t_partitions[pt].free_size;
    }

    cout << "     [Best Fit Algorithm]\n";
    print_processes( t_processes );
    cout << "\n Internal Fragmentation\t: " << int_fragmenattion << "KB\n";
    cout << " External Fragmentation\t: " << ext_fragmenattion << "KB\n";
}


//Worst Fit
void worst_fit(){
    int int_fragmenattion = 0,
        ext_fragmenattion = 0,
        flag, par_sel;
    vector<Partition> t_partitions = partitions;        //temporary copy of partitions
    vector<Process>   t_processes  = processes;         //temporary copy of processes

    /*Iterate through all the processes.
      Assign the process the partition with the maximum free size.
      If the process was unallocated (flag=0), add it's size as external fragmentation.*/
    for( int pr=0; pr<pr_n; pr++ ){
        flag = 0, par_sel = -1;
        for( int pt=0; pt<par_n; pt++ ){
            if( t_partitions[pt].free_size >= t_processes[pr].process_size ){
                flag = 1;
                if( par_sel == -1)
                    par_sel = pt;
                else if( t_partitions[pt].free_size >= t_partitions[par_sel].free_size )
                    par_sel = pt;
        }   }

        if( flag )
            t_processes[pr].allocate(t_partitions[par_sel]);
        else
            ext_fragmenattion += t_processes[pr].process_size;
    }

    for( int pt=0; pt<par_n; pt++){
        if( t_partitions[pt].par_size != t_partitions[pt].free_size )
            int_fragmenattion += t_partitions[pt].free_size;
    }

    cout << "      [Worst Fit Algorithm]\n";
    print_processes( t_processes );
    cout << "\n Internal Fragmentation\t: " << int_fragmenattion << "KB\n";
    cout << " External Fragmentation\t: "   << ext_fragmenattion << "KB\n";
}


int main(){
    int par_size, pr_size;              //partition size and process size
    //partitions input
    cout << " Number of memory partitions: "; cin >> par_n;
    cout << " Input partition sizes [KB]\n";
    for( int i=0; i<par_n; i++ ){
        cout << "   Partition" << i+1 << ": "; cin >> par_size;
        Partition p_temp(i+1, par_size);
        partitions.push_back(p_temp);
    }

    //process input
    cout << " Number of processes: "; cin >> pr_n;
    cout << " Input process sizes [KB]\n";
    for( int i=0; i<pr_n; i++ ){
        cout << "   P" << i+1 << ": "; cin >> pr_size;
        Process p_temp(i+1, pr_size);
        processes.push_back(p_temp);
    }

    cout << string(35, '-') << '\n';
    first_fit();
    cout << string(35, '-') << '\n';
    best_fit();
    cout << string(35, '-') << '\n';
    worst_fit();

    return 0;
}

/*
    TESTING
6
200
400
600
500
300
250
4
357
210
468
491
*/
