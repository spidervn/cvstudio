#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_ISET_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_PROBABILITY_ISET_H_

#include <string>
#include "IAnything.h"

class ISet
{
public:
    virtual bool subsetOf(ISet* p)  = 0;
    virtual IAnythingPtr getAnElement() = 0;

    /* Notation for a Set */
    virtual ISet* complement() = 0;
    virtual ISet* unionWith(ISet* B) = 0;
    virtual ISet* intersectWith(ISet* B) = 0;

    virtual bool isEmpty() = 0;
    virtual bool disJoinWith(ISet* B) = 0;
    virtual ISet* differenceTo(ISet* B) = 0;

    /* Operations */
    virtual ISet* product(ISet* B) = 0;
    virtual int count() = 0;

};

#endif