// cheaters.cpp
// Created by: Justin Swinney (***), Victor Yip (vsy59)
// Modified on: 12/6/19
// Objective: Compares a set of .txt files in a directory and evaluates them for plagiarism.


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

// input: vector containing file names
// output: 0 if success. (perhaps we can make this a void function???)
// precond: file path directory matches string set
// postcond: inserts file names
int getFileNames(vector<string> &files, string directory);


// input: string vector with set of words, hash table
// output: 0 if success.
// precond: hash table is initialized.
// postcond: adds a value to the hash table
int key(vector<string> chunk, double tableSize);

// Expected parameters in argv[]
// [0] - program name
// [1] - path to folder containing .txt files including folder name.
// [2] - number of words per chunk
// [3] - number of matched chunks to raise cheater flag
int main(int argc, char* argv[]){
    vector<string> files;
    string directory=argv[1];
    getFileNames(files,directory);

    HashTable table;
    const double tableSize=1000000;         // hash table memory size

    int numWords=atoi(argv[2]);
    string path=argv[1];
    int threshold=atoi(argv[3]);
    string place;


    // parses through all identified files in the string vector
    for(std::vector<string>::iterator i=files.begin();i!=files.end();i++){
        cout << "Running..." <<endl;
        place=path+"/"+*i;

        // checks for valid filenames, explicitly excludes "." and ".."
        if((*i!=".")&&(*i!="..")) {
            ifstream myfile(place.c_str());
            vector<string> queue;

            // if there is still information in the active file, start forming a chunk
            if (myfile.is_open()) {
                char ch;        // char pulled from active file
                string word;    // concat of chars from active file

                // while not at end of file, start reading chars -> word in active file
                while (!myfile.eof()) {
                    word.clear();
                    myfile.get(ch);

                    // only obtains ASCII alphabet characters. Word is defined by encountering white space.
                    // Characters such as [, . ? ' "] are ignored
                    while ((ch < 123) && (ch > 64) && (ch != ' ' ) ) {
                        word += ch;
                        myfile.get(ch);
                    }

                    // if number of collected words in "queue" is less than defined chunk size, add new word to queue vector.
                    // otherwise, if the new word is an actual word (not end of file) generate a key for chunk and place key into hash table
                    if (queue.size() < numWords) {
                        queue.push_back(word);
                    } else if(word!="") {
                        int k=key(queue, tableSize); // generate hash key
                        string chunk;

                        // concat words from queue
                        for (std::vector<string>::const_iterator j = queue.begin(); j != queue.end(); ++j) {
                            chunk+=*j;
                        }


                        int index=distance(files.begin(),i);    // file from which chunk originates
                        table.add(index,k);                     // adds chunk file ID and key to hash table
                        queue.erase(queue.begin());             // deletes first word in queue to make space for new word.
                        queue.push_back(word);
                    }
                }
                myfile.close();
            }
        }
    }
    table.tally(files, threshold);
    return 0;
}

// input: string containing directory name, string vectors
// output: 0 for success, errno (from errno.h) if fail
// precond: dir string matches dir in program argument; files vector has valid filenames
// postcond: pushes file name
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

int getFileNames(vector<string> &files, string directory)
{
    string dir = directory;
    files = vector<string>();

    getdir(dir,files);

    for (unsigned int i = 0;i < files.size();i++) {
        //cout << i << files[i] << endl;
    }
    return 0;
}

int key(vector<string> chunk, double tableSize){
    string characters;

    // concats characters from chunk.
    for(std::vector<string>:: iterator i=chunk.begin();i!=chunk.end();i++){
        characters+=*i;
    }

    double key=0;

    // creates an identifier unique to the chunk contents, used for hash table.
    for(double i=0;i<characters.size();i++){
        key+=((characters[characters.size()-i-1])*pow(3,i));
    }

    return fmod(key,tableSize);
}
