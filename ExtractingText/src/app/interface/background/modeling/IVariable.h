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
    virtual int construct(const char* name, IValueSpace* p_Space) = 0;
};

#endif