#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "cheaters.h"


using namespace std;

int getFileNames(vector<string> &files);

int key(vector<char> chunk, int threshold);

int main(int argc, char* argv[]){
    vector<string> files;
    getFileNames(files);
    HashTable table;
    table.add("Justin",0);
    table.add("Justan",0);
    
    int numChars=atoi(argv[2]);
    string path=argv[1];
    int threshold=atoi(argv[3]);
    string place;
    for(std::vector<string>::iterator i=files.begin();i!=files.end();i++){
        cout << *i << endl;
        place=path+"/"+*i;
        cout << place << endl;
        if((*i!=".")&&(*i!="..")) {
            ifstream myfile(place.c_str());
            vector<char> queue;
            if (myfile.is_open()) {
                char ch;
                while (!myfile.eof()) {
                    myfile.get(ch);
                    if (ch < 123 && ch > 64) {
                        if (queue.size() < numChars) {
                            queue.push_back(ch);
                        } else {
                            key(queue,threshold);
                            for (std::vector<char>::const_iterator j = queue.begin(); j != queue.end(); ++j) {
                                std::cout << *j << ' ';
                            }
                            cout << endl;
                            // Currently reads before push, last queue of file isn't outputted
                            queue.erase(queue.begin());
                            queue.push_back(ch);

                        }
                    }
                }
                cout << "--------------------------------------------------------" << endl;
                myfile.close();
            } else {
                cout << "UNABLE TO OPEN FILE" << endl;
            }
        }else{
            cout << "INVALID FILE NAME" << endl;
        }

    }
    return 0;
}



/*function... might want it in some class?*/
int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
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
        cout << i << files[i] << endl;
    }
    return 0;
}

int key(vector<char> chunk, int threshold){
    int result=0;
    for(std::vector<char>::iterator k=chunk.begin();k!=chunk.end();k++){
        result+=*k;
    }
    return result;
}