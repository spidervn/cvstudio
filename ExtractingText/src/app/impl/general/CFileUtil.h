#ifndef EXTRACTTEXT_APP_IMPL_GENERAL_CFILEUTIL_H_
#define EXTRACTTEXT_APP_IMPL_GENERAL_CFILEUTIL_H_

#include "app/interface/general/IFileUtil.h"
#include <vector>

class CFileUtil: public IFileUtil
{
private:
    /* data */
public:
    CFileUtil(/* args */);
    ~CFileUtil();

    int getAllFileInFolder(std::string folder, std::vector<std::string>& v);
};


#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_