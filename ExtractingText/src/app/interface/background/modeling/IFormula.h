#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IFORMULA_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IFORMULA_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "IVariable.h"

class IFormula
{
public:
    virtual ~IFormula() {}
    virtual int define(IVariable* p_Val) = 0;
    virtual bool equals(IFormula* pFopposite) = 0;
    
};

#endif