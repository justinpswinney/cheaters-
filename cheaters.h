//
// Created by Owner on 12/2/2019.
//

#ifndef CHEATERS_CHEATERS_H
#define CHEATERS_CHEATERS_H

using namespace std;

class HashNode{
private:
    int index;
    HashNode * next;
public:
    HashNode(){
        next=NULL;
        index=-1;
    }
    HashNode(int index){
        this->index=index;
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
        table= new HashNode*[1000]();
    }
    void add(int index, int key){
        HashNode *last=NULL;
        HashNode *current=table[key];
        while(current!=NULL) {
            last = current;
            current = current->getNext();
        }
        if(current==NULL){
            current= new HashNode(index);
            if(last==NULL){
                table[key]=current;
            }else{
                last->setNext(current);
            }
        }
    }
};

#endif //CHEATERS_CHEATERS_H
