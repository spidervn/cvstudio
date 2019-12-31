#ifndef VISIONFUND_VISIONLAB_INTERFACE_IAPPLICATION_H_
#define VISIONFUND_VISIONLAB_INTERFACE_IAPPLICATION_H_

class IApplication
{
private:
    /* data */
public:
    virtual ~IApplication() {}
    virtual int run(int argc, char const* argv[]) = 0;
};

#endif