// cheaters.h
// Created by: Justin Swinney (***), Victor Yip (vsy59)
// Modified on: 12/6/19

#include <algorithm>

#ifndef CHEATERS_CHEATERS_H
#define CHEATERS_CHEATERS_H



using namespace std;

// Caught is used to make objects that compare two files and shows how many similarities there are between them.
// This class is only used if there are pairs of files that cross the prog arg threshold of similarities for plagiarism
class Caught{
private:
    int instances;
    string name1;
    string name2;
public:
    Caught(){
        this->instances=0;
        this->name1="";
        this->name2="";
    };

    Caught(int instances,string name1,string name2){
        this->instances=instances;
        this->name1=name1;
        this->name2=name2;
    }

    int getInstances() const{return instances;}
    string getNames() const{return name1+" "+name2;}
    string getName1() const{return name1;}
    string getName2() const{return name2;}
    void setName1(string name1){this->name1=name1;}
    void setName2(string name2){this->name2=name2;}
    void setInstances(int instances){this->instances=instances;}
};


// HashTable creates an object that generates a set of 1 Million possible keys for chunks to be identified with.
// By giving each unique word chunk a vector, we can identify which files have similar series' of words.
class HashTable{
private:
    vector<int> *table;
public:
    HashTable(){

        table= new vector<int>[1000000];
    }

    // input: file index number and hash table key number
    // output: none
    // precond: key is within hash table memory range.
    // postcond: adds the ID of file if it is not already registered for that chunk's key.
    void add(int index, int key){
        bool notFound=true;

        // checks the file ID's in the specified key number for self-identification
        for(std::vector<int>::iterator i= table[key].begin();i!=table[key].end();i++){

            // prevents file from being added twice
            if(*i==index){
                notFound=false;
            }
        }

        // adds file ID if not already recorded in chunk key
        if(notFound==true){
            table[key].push_back(index);
        }
    }

    // input: vector containing file IDs and threshold for number of chunk matches (prog arg)
    // output: none
    // precond: all the text file chunks have been created and sorted
    // postcond: outputs to console the likely cheaters/plagiarizers
    void tally(vector<string> files, int threshold){
        int collisions[files.size()][files.size()]; // array table to tally hash table key file similarities.

        // fills table with 0's to start
        for(int i=0;i<files.size();i++){
            for(int j=0;j<files.size();j++){
                collisions[i][j]=0;
            }
        }

        // compares every combination of file IDs stored per hash key. Every combination of ID's is added to collisions.
        for(int i=0;i<1000000;i++){
            for(std::vector<int>::iterator j=table[i].begin();j!=table[i].end();j++){
                for(std::vector<int>::iterator h=j+1;h!=table[i].end();h++){
                    collisions[*j][*h]++;
                }
            }
        }

        vector<Caught> cheaters;

        // Adds together the number of similarities between files A->B and B->A.
        // If the sum is > threshold, then the pair of files are added as a "Caught" to the cheaters vector.
        // Number of collisions is also added.
        for(int i=0;i<files.size();i++){
            for(int j=i;j<files.size();j++){
                if((collisions[i][j]+collisions[j][i]>threshold)&&(i!=j)){
                    Caught writers(collisions[i][j]+collisions[j][i], files[i], files[j]);
                    cheaters.push_back(writers);
                }
            }
        }
        cout <<  endl;

        vector<Caught> cheatersSorted;

            // Cheaters are sorted so the pair of files are displayed with descending number of collisions.
            for(std::vector<Caught>::iterator i=cheaters.begin();i!=cheaters.end();i++){
                for(std::vector<Caught>::iterator j=i+1;j!=cheaters.end();j++){
                    if((*j).getInstances()>(*i).getInstances()){
                        string name1;
                        string name2;
                        int instances;
                        instances=(*j).getInstances();
                        name1=(*j).getName1();
                        name2=(*j).getName2();
                        (*j).setName1((*i).getName1());
                        (*j).setName2((*i).getName2());
                        (*j).setInstances((*i).getInstances());
                        (*i).setName1(name1);
                        (*i).setName2(name2);
                        (*i).setInstances(instances);

                    }
                }
            }

        // Displays list of cheaters to the console.
        for(std::vector<Caught>::iterator i=cheaters.begin();i!=cheaters.end();i++){
            cout << (*i).getNames() << " " << (*i).getInstances() << endl;
        }

    }
};



#endif //CHEATERS_CHEATERS_H
