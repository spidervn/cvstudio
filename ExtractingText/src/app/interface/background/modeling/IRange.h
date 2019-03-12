#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IRANGE_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IRANGE_H_
#include <string>
#include "app/interface/background/modeling/IVariable.h"
class IRange
{
public:
    virtual ~IRange() {}
    virtual int define(IVariable* pFrom, IVariable* pTo) = 0;
};

#endif