#ifndef _LEANR_EXCEPTION_H_
#define _LEANR_EXCEPTION_H_

#include <exception>
#include <iostream>

class ZqhErr : public std::exception {
private:
    const char* m_str;

public:
    ZqhErr() = default;
    ZqhErr(char* str)
        : m_str(str)
    {
    }

    const char* what()
    {
        return "你错了，隔这搞笑了吧";
    }
};

#endif