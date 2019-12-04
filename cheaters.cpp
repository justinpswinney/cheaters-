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

int key(vector<string> chunk, int threshold);

int main(int argc, char* argv[]){
    vector<string> files;
    getFileNames(files);
    HashTable table;
    table.add("Justin",0);
    table.add("Justan",0);

    int numWords=atoi(argv[2]);
    string path=argv[1];
    int threshold=atoi(argv[3]);
    string place;
    for(std::vector<string>::iterator i=files.begin();i!=files.end();i++){
        cout << *i << endl;
        place=path+"/"+*i;
        cout << place << endl;
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
                        key(queue, threshold);
                        for (std::vector<string>::const_iterator j = queue.begin(); j != queue.end(); ++j) {
                            cout << *j ;
                        }
                        cout << endl;
                        // Currently reads before push, last queue of file isn't outputted til outside brackets
                        queue.erase(queue.begin());
                        queue.push_back(word);
                    }
                }
                for (std::vector<string>::const_iterator j = queue.begin(); j != queue.end(); ++j) {
                    cout << *j ;
                }
                cout << endl << "-----------------------------------------------------------------------------------------" << endl;
                myfile.close();
            }else {
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

int key(vector<string> chunk, int threshold){

    return 0;
}