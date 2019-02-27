#ifndef USER_H
#define USER_H

#include <iostream>
#include <list>


class User
{
private:
    std::string nickname;
    std::string user_id;

public:
    User();
    User(const User&);
    User(const std::string&, const std::string&);
    std::string getNickname() const;
    std::string getUserId() const;

    User& operator=(const User&);

    friend std::istream& operator>>(std::istream&, User&);
};

std::ostream& operator<<(std::ostream&, const User&);

bool operator==(const User&, const User&);
bool operator!=(const User&, const User&);

#endif // USER_H
