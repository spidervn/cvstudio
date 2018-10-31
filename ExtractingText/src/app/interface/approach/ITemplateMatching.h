#ifndef EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_
#define EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_

class ITemplateMatching
{
public:
    virtual ~ITemplateMatching() {}
    virtual int run(int argc, char* argv[]) = 0;
};

#endif // !EXTRACTTEXT_APP_INTERFACE_APPROACH_ITEMPLATEMATCHING_H_