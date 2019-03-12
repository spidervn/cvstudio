#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IRANGE_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IRANGE_H_

#include <string>

class IRange
{
public:
    virtual ~IRange() {}
    virtual int define() = 0;
};

#endif