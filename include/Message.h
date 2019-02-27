#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include "User.h"

class Message
{
private:
    std::string text;
    User sender;
    User receiver;

    friend std::istream& operator>>(std::istream&, Message&);

public:
    Message();
    Message(const Message&);
    Message(const User&, const User&, const std::string&);

    Message& operator=(const Message&);

    unsigned int getMessageSize() const;
    User getSender() const;
    User getReceiver() const;
    std::string getTextMessage() const;
};

std::ostream& operator<<(std::ostream&, const Message&);

#endif // MESSAGE_H
