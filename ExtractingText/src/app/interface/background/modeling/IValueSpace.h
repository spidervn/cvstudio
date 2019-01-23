#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IVALUESPACE_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IVALUESPACE_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>

class IValueSpace
{
public:
    virtual ~IValueSpace() {}
    virtual int construct(const char* name) = 0;
};

#endif