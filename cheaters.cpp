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

int getFileNames(vector<string> &files, string directory);

int key(vector<string> chunk, double tableSize);

int main(int argc, char* argv[]){
    vector<string> files;
    string directory=argv[1];
    getFileNames(files,directory);
    HashTable table;
    const double tableSize=1000000;
    int numWords=atoi(argv[2]);
    string path=argv[1];
    int threshold=atoi(argv[3]);
    string place;
    for(std::vector<string>::iterator i=files.begin();i!=files.end();i++){
        cout << "Running..." <<endl;
        place=path+"/"+*i;
        if((*i!=".")&&(*i!="..")) {
            ifstream myfile(place.c_str());
            vector<string> queue;
            if (myfile.is_open()) {
                char ch;
                string word;
                while (!myfile.eof()) {
                    word.clear();
                    myfile.get(ch);
                    while ((ch < 123) && (ch > 64) && (ch != ' ' ) ) {
                        word += ch;
                        myfile.get(ch);
                    }

                    if (queue.size() < numWords) {
                        queue.push_back(word);
                    } else if(word!="") {
                        int k=key(queue, tableSize);
                        string chunk;
                        for (std::vector<string>::const_iterator j = queue.begin(); j != queue.end(); ++j) {
                            chunk+=*j;
                        }
                        int index=distance(files.begin(),i);
                        table.add(index,k);
                        queue.erase(queue.begin());
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
    for(std::vector<string>:: iterator i=chunk.begin();i!=chunk.end();i++){
        characters+=*i;
    }

    double key=0;
    for(double i=0;i<characters.size();i++){
        key+=((characters[characters.size()-i-1])*pow(3,i));
    }

    return fmod(key,tableSize);
}