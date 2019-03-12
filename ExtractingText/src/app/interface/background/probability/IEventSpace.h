#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_IEVENTSPACE_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_IEVENTSPACE_H_

#include <string>
#include "app/interface/background/modeling/IVariable.h"

class IEventSpace
{
public:
    virtual ~IEventSpace() {}
    virtual std::string name() = 0;
};

#endif