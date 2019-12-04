//
// Created by Owner on 12/2/2019.
//
#include <algorithm>

#ifndef CHEATERS_CHEATERS_H
#define CHEATERS_CHEATERS_H



using namespace std;

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
    int getInstances() const{
        return instances;
    }
    string getNames() const{
        return name1+" "+name2;
    }
    string getName1() const{
        return name1;
    }
    string getName2() const{
        return name2;
    }
    void setName1(string name1){
        this->name1=name1;
    }
    void setName2(string name2){
        this->name2=name2;
    }
    void setInstances(int instances){
        this->instances=instances;
    }
};

class HashTable{
private:
    vector<int> *table;
public:
    HashTable(){
        table= new vector<int>[1000000];
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
    void tally(vector<string> files, int threshold){
        int collisions[files.size()][files.size()];
        for(int i=0;i<files.size();i++){
            for(int j=0;j<files.size();j++){
                collisions[i][j]=0;
            }
        }
        for(int i=0;i<1000000;i++){
            for(std::vector<int>::iterator j=table[i].begin();j!=table[i].end();j++){
                for(std::vector<int>::iterator h=j+1;h!=table[i].end();h++){
                    collisions[*j][*h]++;
                }
            }
        }
        vector<Caught> cheaters;
        for(int i=0;i<files.size();i++){
            for(int j=i;j<files.size();j++){
                if((collisions[i][j]+collisions[j][i]>threshold)&&(i!=j)){
                    //cout << files[i] << " " << files[j] << " " << collisions[i][j]+collisions[j][i] << endl;
                    Caught writers(collisions[i][j]+collisions[j][i], files[i], files[j]);
                    cheaters.push_back(writers);
                }
            }
        }
        vector<Caught> cheatersSorted;
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


        for(std::vector<Caught>::iterator i=cheaters.begin();i!=cheaters.end();i++){
            cout << (*i).getNames() << " " << (*i).getInstances() << endl;
        }

    }
};



#endif //CHEATERS_CHEATERS_H
