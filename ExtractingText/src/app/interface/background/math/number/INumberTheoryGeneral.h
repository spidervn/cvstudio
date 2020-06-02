#ifndef EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MATH_NUMBER_INUMBERTHEORYGENERAL_H_
#define EXTRACTTEXT_APP_INTERFACE_BACKGROUND_MATH_NUMBER_INUMBERTHEORYGENERAL_H_

class I

class IProof
{
public:
    virtual ~IProof() {}
    virtual bool proof() = 0;
};

class INumberTheoryGeneral
{
public:
    virtual ~INumberTheoryGeneral() {}    
};



#endif