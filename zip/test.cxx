#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <iostream>
#include "zip.h"

using namespace std;

static void add_zip_file(HZIP hzip, string file)
{
    struct stat file_st;
    if(0 == stat(file.c_str(), &file_st)) {
        if(S_ISDIR(file_st.st_mode)) {
            DIR *p_dir = opendir(file.c_str());
            if(p_dir) {
                cout << "[" << file << "] is a dir, enter it." << endl;
                struct dirent *p_dirent;
                while(NULL != (p_dirent = readdir(p_dir))) {
                    if('.' == p_dirent->d_name[0]) {
                        continue;
                    }
                    string sub_file = file + '/' + p_dirent->d_name;
                    add_zip_file(hzip, sub_file);
                }
                closedir(p_dir);
            } else {
                    cout << "[" << file << "] zip failed, continue.." << endl;
            }
        } else {
                cout << "[" << file << "] zipped." << endl;
                ZipAdd(hzip, file.c_str(), file.c_str());	// arg0: the file name [after unzip], arg1: src file
        }
    } else {
            cout << "[" << file << "] zip failed, continue.." << endl;
    }
}

int main(int argc, char **argv)
{
        if(argc == 1) {
                printf("please input file\n");
                return 0;
        }
        HZIP hzip = CreateZip("./tmp/total.zip", NULL);	// the final zip name 
        for(int i=1; i<argc; i++) {
                add_zip_file(hzip, argv[i]);
        }
        CloseZip(hzip);

        return 0;
}
