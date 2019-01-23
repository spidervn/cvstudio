#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IFORMULABUILDER_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IFORMULABUILDER_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "../IVariable.h"
#include "../IFormula.h"

class IFormulaBuilder
{
public:
    virtual ~IFormulaBuilder() {}
    virtual IVariable* multiply(IVariable* p1, IVariable* p2) = 0;
    virtual IVariable* divide(IVariable* p1, IVariable* p2) = 0;
    virtual IVariable* sum(IVariable* pi, 
                                IValueSpace* p_range_I,
                                IFormula* pFormular) = 0;
    virtual IVariable* product(IVariable* pi, 
                                IValueSpace* p_range_I,
                                IFormula* pFormula) = 0;
    virtual IVariable* product() = 0;
};

#endif