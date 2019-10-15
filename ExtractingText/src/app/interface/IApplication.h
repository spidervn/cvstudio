#ifndef EXTRACTTEXT_APP_INTERFACE_IAPPLICATION_H_
#define EXTRACTTEXT_APP_INTERFACE_IAPPLICATION_H_
#include <memory>

class IApplication
{
public:
    virtual ~IApplication() {}
    virtual int run(int argc, char const *argv[]) = 0;
};

typedef std::shared_ptr<IApplication> IApplicationPtr;

#endif // 