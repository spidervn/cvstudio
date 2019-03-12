#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IVARIABLE_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IVARIABLE_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "IValueSpace.h"

class IVariable
{
public:
    virtual ~IVariable() {}
    virtual int define(const char* name, IValueSpace* p_Space) = 0;
    
    virtual bool equals(IVariable* pCompare) = 0;
    virtual IValueSpace* _Gettype() = 0;
    virtual double currentMappedValue() = 0;
};

#endif