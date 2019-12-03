//
// Created by Owner on 12/2/2019.
//

#ifndef CHEATERS_CHEATERS_H
#define CHEATERS_CHEATERS_H

using namespace std;

class HashNode{
private:
    string name;
    HashNode * next;
public:
    HashNode(){
        next=NULL;
        name="0";
    }
    HashNode(string writer){
        name=writer;
        next=NULL;
    }

    HashNode *getNext() const{
        return this->next;
    }
    void setNext(HashNode * nextNode){
        HashNode *trail=NULL;
        HashNode *current=this;
        while(current!=NULL){
            trail=current;
            current=current->next;
        }
        trail->next=nextNode;
    }
};

class HashTable{
private:
    HashNode **table;
public:
    HashTable(){
        table= new HashNode*[100]();
    }
    void add(string name, int key){
        HashNode *last=NULL;
        HashNode *current=table[key];
        while(current!=NULL) {
            last = current;
            current = current->getNext();
        }
        if(current==NULL){
            current= new HashNode(name);
            if(last==NULL){
                table[key]=current;
            }else{
                last->setNext(current);
            }
        }
    }
};

#endif //CHEATERS_CHEATERS_H
