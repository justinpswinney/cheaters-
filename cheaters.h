//
// Created by Owner on 12/2/2019.
//

#ifndef CHEATERS_CHEATERS_H
#define CHEATERS_CHEATERS_H

using namespace std;



class HashTable{
private:
    vector<int> *table;
public:
    HashTable(){
        table= new vector<int>[1000]();
    }
    void add(int index, int key){
        bool notFound=true;
        for(std::vector<int>::iterator i= table[key].begin();i!=table[key].end();i++){
            if(*i==index){
                notFound=false;
            }
        }
        if(notFound==true){
            table[key].push_back(index);
        }
    }
};

#endif //CHEATERS_CHEATERS_H
