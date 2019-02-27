#include "Message.h"



Message::Message()
{}

Message::Message(const User& sender,const User& receiver,const std::string& message) : sender(sender), receiver(receiver)
{
    this->text = message;
}

Message::Message(const Message &message)
{
    this->receiver = message.getReceiver();
    this->sender = message.getSender();
    this->text = message.getTextMessage();
}

Message& Message::operator=(const Message &message)
{
    this->receiver = message.getReceiver();
    this->sender = message.getSender();
    this->text = message.getTextMessage();
}

unsigned int Message::getMessageSize() const
{
    return this->text.length();
}

std::string Message::getTextMessage() const
{
    return this->text;
}

User Message::getReceiver() const
{
    return this->receiver;
}

User Message::getSender() const
{
    return this->sender;
}



std::istream& operator>>(std::istream& in, Message& input_message)
{
    in >> input_message.sender >> input_message.receiver >> input_message.text;
    return in;
}



std::ostream& operator<<(std::ostream& out, const Message& output_message)
{
    out << output_message.getSender() << " ";
    out << output_message.getReceiver() << " ";
    out << output_message.getTextMessage() << " ";
    return out;
}

