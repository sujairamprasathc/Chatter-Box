#ifndef CHATSERVEREXCEPTION_H
#define CHATSERVEREXCEPTION_H

#include <exception>


class ChatServerException : public std::exception
{
public:
    ChatServerException();
    const char* what() const noexcept override;
};

#endif // CHATSERVEREXCEPTION_H
