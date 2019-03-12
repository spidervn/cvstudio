#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_ISUMMATION_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_ISUMMATION_H_

#include "app/interface/background/modeling/IVariable.h"
#include "app/interface/background/modeling/IRange.h"
#include "app/interface/background/modeling/IFormula.h"

class ISummation
{
public:
    virtual ~ISummation() {}
    virtual int define(IVariable* p, IRange* pRange, IFormula* pFormula) = 0;
};

#endif