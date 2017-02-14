#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string>

using namespace std;

std::string getOsName()
{
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __unix || __unix__
    return "Unix";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #else
    return "Other";
    #endif
}

int main()
{
        char dirn[50];
        DIR *dir = NULL;
        struct dirent *drnt = NULL;
        string extention = ".ssp";
        string fileName = "";

        printf("Input dir name: ");
        gets(dirn);

        dir=opendir(dirn);
        if(dir)
        {
                printf("output:\n");
                while(drnt = readdir(dir))
                {
					fileName = drnt->d_name;
					if (fileName.find(extention) != std::string::npos)
					{
						cout << fileName << endl;
                        //printf("%s\n", drnt->d_name);
					}
                }
                closedir(dir);
        }
        else
        {
                printf("Can not open directory '%s'\n", dirn);
        }

if(fileName == extention)
	cout << "SATANAS" << endl;
else
	cout << "CAPETA" << endl;

        return 0;

}


/*
int main()
{
	glob_t glob_result;
    cout << "Hello world!" << endl;
    std::string myOSName = getOsName();
    cout << myOSName << endl;
    
    return 0;
}
*/
