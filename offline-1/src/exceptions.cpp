#include <exceptions.hpp>

const char *null_collider_exception::what()
{
    return "Rigidbody must have a valid collider";
}