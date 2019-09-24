#ifndef EXTRACTTEXT_APP_INTERFACE_IFILEUTIL_H_
#define EXTRACTTEXT_APP_INTERFACE_IFILEUTIL_H_

#include <vector>
#include <string>
#include <memory>

class IFileUtil
{
private:
    /* data */
public:
    virtual ~IFileUtil() {};
    virtual int getAllFileInFolder(std::string folder, std::vector<std::string>& v) = 0;
};

typedef std::shared_ptr<IFileUtil> IFileUtilPtr;

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_