#include "chatserverexception.h"

ChatServerException::ChatServerException()
{}



const char* ChatServerException::what() const noexcept
{
    return "Chat Server failed to initialize";
}
