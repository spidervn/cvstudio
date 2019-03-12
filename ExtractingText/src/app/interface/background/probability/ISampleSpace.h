#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_ISAMPLESPACE_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_ISAMPLESPACE_H_

#include <string>

// All out-come of a random expertiments
class ISampleSpace
{
public:
    virtual ~ISampleSpace() {}
    virtual std::string name() = 0; 
};

#endif