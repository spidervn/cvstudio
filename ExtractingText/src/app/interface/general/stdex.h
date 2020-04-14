#ifndef EXTRACTTEXT_APP_INTERFACE_STDEX_H_
#define EXTRACTTEXT_APP_INTERFACE_STDEX_H_

class stdex
{
private:
    /* data */
public:
    stdex(/* args */);
    ~stdex();

    template<class InputIt, class T>
    static T accumulate(InputIt first, InputIt last, T init, int jump=1)
    {
        for (; first != last;) {
            init = init + *first;

            // Jump
            for (int i=0;i<jump && first !=last;++i)
            {
                first++;
            }
        }
        return init;
    }
};



#endif