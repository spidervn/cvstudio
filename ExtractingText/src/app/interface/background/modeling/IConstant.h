#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_ICONSTANT_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_ICONSTANT_H_

#include "IValueSpace.h"

class IConstant
{
public:
    virtual ~IConstant() {}
    virtual  int define(const char* name, IValueSpace* pVS, double mappedValue) = 0;
    virtual double currentMappedValue() = 0;
};

#endif