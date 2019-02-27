#include "User.h"
#include <iostream>


User::User()
{}



User::User(const std::string& nickname, const std::string& user_id)
{
    this->nickname = nickname;
    this->user_id = user_id;
}



User::User(const User &user)
{
    this->nickname = user.getNickname();
    this->user_id = user.getUserId();
}



User& User::operator=(const User &user)
{
    this->nickname = user.getNickname();
    this->user_id = user.getUserId();

    return *this;
}



std::string User::getNickname() const
{
    return this->nickname;
}



std::string User::getUserId() const
{
    return this->user_id;
}



bool operator==(const User& user1, const User& user2)
{
    if( user1.getUserId() == user2.getUserId() ) {
        return true;
    }
    else {
        return false;
    }
}

bool operator!=(const User& user1, const User& user2)
{
    if( user1.getUserId() != user2.getUserId() ) {
        return true;
    }
    else {
        return false;
    }
}


std::ostream& operator << (std::ostream& out,const User& output_user)
{
    out << output_user.getNickname() << " " << output_user.getUserId() << " ";
    return out;
}



std::istream& operator >> (std::istream& in, User& user)
{
    in >> user.nickname;
    in >> user.user_id;
    return in;
}
