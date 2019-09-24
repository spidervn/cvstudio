#include "CFileUtil.h"

#include <dirent.h>
using namespace std;
CFileUtil::CFileUtil(/* args */)
{
}

CFileUtil::~CFileUtil()
{
}

int CFileUtil::getAllFileInFolder(std::string folder, std::vector<std::string>& v)
{
    v.clear();
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (folder.c_str())) != NULL) 
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) 
        {
            //
            // printf ("%s\n", ent->d_name);
            //
            if (ent->d_type == DT_REG)   
            {
                v.push_back(folder + "/" +  ent->d_name);
            }
        }

        closedir (dir);
    } 
    else 
    {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }

    return 0;
}