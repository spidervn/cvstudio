#ifndef EXTRACTTEXT_APP_INTERFACE_IAPPLICATION_H_
#define EXTRACTTEXT_APP_INTERFACE_IAPPLICATION_H_

class IApplication
{
public:
    virtual ~IApplication() {}
    virtual int run(int argc, char const *argv[]) = 0;
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_