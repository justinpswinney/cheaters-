#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int getFileNames(vector<string> &files);

int main(int argc, char* argv[]){
    vector<string> files;
    getFileNames(files);
    string line;
    int numChars=atoi(argv[2]);
    string path=argv[1];
    
    for(std::vector<string>::iterator i=files.begin();i!=files.end();i++){
        cout << *i << endl;
        ifstream myfile (*i);
        vector<char> queue;
        if(myfile.is_open()){
            /*
            while(getline(myfile,line)){
                cout << line << endl;
            }
            */
            char ch;
            while (!myfile.eof() ) {
                myfile.get(ch);
                if(ch<123&&ch>64){
                    if (queue.size() < numChars) {
                        queue.push_back(ch);
                    } else {
                        for (std::vector<char>::const_iterator i = queue.begin(); i != queue.end(); ++i) {
                            std::cout << *i << ' ';
                        }
                        cout << endl;
                        // Currently reads before push, last queue of file isnt outputted
                        queue.erase(queue.begin());
                        queue.push_back(ch);
                    }

                }


            }
            cout << "--------------------------------------------------------" << endl;
            myfile.close();
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