#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "cheaters.h"
#include <functional>
#include <math.h>



using namespace std;

int getFileNames(vector<string> &files);

int key(vector<string> chunk, double tableSize);
// Expected parameters in argv
// [0] - program name
// [1] - path to folder containing txt files including folder name.
// [2] - number of words per chunk
// [3] - number of matched chunks to raise cheater flag
int main(int argc, char* argv[]){
    vector<string> files;
    getFileNames(files);
    HashTable table;                    // hash table to store matching phrases of words
    const double tableSize=1000000;     // maximum number of.....-the table size is the size of the hash table memory
    int numWords=atoi(argv[2]);         // size of number of words per chunk
    string path=argv[1];                // path of files to scan
    int threshold=atoi(argv[3]);        // number of matches to count as cheating
    string place;                       // ??? -place holds the full path from the current directory to the directory of files
    for(std::vector<string>::iterator i=files.begin();i!=files.end();i++){ // cycles through all the text files in vector
        cout << "Running.." <<endl;
        //cout << *i << endl;
        place=path+"/"+*i;
        //cout << place << endl;
        if((*i!=".")&&(*i!="..")) {         // if input file is valid, open the file
            ifstream myfile(place.c_str());
            vector<string> queue;           // vector of words collected from active file
            if (myfile.is_open()) {
                char ch;                    // var to hold character from active file
                string word;                // compiles characters from active file into a word string
                while (!myfile.eof()) {
                    word.clear();           // empties word string for new word in file
                    myfile.get(ch);         // obtain char from active file and place into ch
                    while ((ch < 123) && (ch > 64) && (ch != ' ' ) ) {  // while char is valid ASCII letter (plus extras) and not ' ',
                        word += ch;
                        myfile.get(ch);
                    }

                    if (queue.size() < numWords) {
                        queue.push_back(word);
                    } else if(word!="") {               // if chunk is full with additional words left in file
                        int k=key(queue, tableSize);    // makes key id for hash table(?)-yep its the hash function
                        string chunk;
                        // prints out contents of chunk. idk how const_iterator works-think of it like iterating through an array
                        for (std::vector<string>::const_iterator j = queue.begin(); j != queue.end(); ++j) {
                            //cout << *j ;
                            chunk+=*j;
                        }
                        //cout << "   " << k;
                        int index=distance(files.begin(),i);
                        table.add(index,k);
                        //cout << endl;
                        // Currently reads before push, last queue of file isn't outputted til outside brackets
                        // erases first word so chunk can be shift for complete coverage. Requires next word to already be loaded in.
                        queue.erase(queue.begin());
                        queue.push_back(word);
                    }
                }
                for (std::vector<string>::const_iterator j = queue.begin(); j != queue.end(); ++j) {
                    //cout << *j ;
                }
                //cout << endl << "-----------------------------------------------------------------------------------------" << endl;
                myfile.close();
            }else {
                //cout << "UNABLE TO OPEN FILE" << endl;
            }

        }else{
            //cout << "INVALID FILE NAME" << endl;
        }

    }
    table.tally(files, threshold);
    return 0;
}



/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        //cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

int getFileNames(vector<string> &files)
{
    string dir = string("sm_doc_set");
    files = vector<string>();

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        //cout << i << files[i] << endl;
    }
    return 0;
}

int key(vector<string> chunk, double tableSize){
    string characters;
    for(std::vector<string>:: iterator i=chunk.begin();i!=chunk.end();i++){
        characters+=*i;
    }

    double key=0;
    for(int i=0;i<characters.size();i++){
       key+=((characters[characters.size()-i-1])*(11^i));
    }

    return fmod(key,tableSize);
}
