#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_IANYTHING_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_IANYTHING_H_

#include <memory>

class IAnything
{
public:
    virtual ~IAnything() {};
};

typedef std::shared_ptr<IAnything> IAnythingPtr;

#endif