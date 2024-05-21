#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include "shell.h"

using namespace std;
//using namespace GFile;

int main(){
    GFile::Shell myshell;

    myshell.main_shell();
    return 0;
}