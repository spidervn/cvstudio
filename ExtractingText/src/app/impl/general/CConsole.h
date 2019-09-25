#ifndef EXTRACTTEXT_APP_IMPL_GENERAL_CCONSOLE_H_
#define EXTRACTTEXT_APP_IMPL_GENERAL_CCONSOLE_H_

#include <vector>
#include <iostream>

class CConsole
{
private:
    /* data */
public:
    CConsole(/* args */);
    virtual ~CConsole();

    template<typename T>
    static void print(const std::vector<T>& v)
    {
        if (v.size() > 0)
        {
            std::cout << v[0];
            for (int i=1; i<v.size(); ++i)
            {
                std::cout << "; " << v[i];
            }
        }

        std::cout << std::endl;
    }
};


#endif