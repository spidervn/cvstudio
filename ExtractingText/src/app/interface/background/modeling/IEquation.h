#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IEQUATION_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MODELING_IEQUATION_H_

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "IFormula.h"

class IEquation
{
public:
    virtual ~IEquation() {}
    virtual int construct(IFormula* pF1, IFormula* pF2) = 0;
};

#endif