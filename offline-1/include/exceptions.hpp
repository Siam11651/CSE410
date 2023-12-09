#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class null_collider_exception : public std::exception
{
public:
    const char *what();
};

#endif