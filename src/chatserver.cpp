#include "chatserver.h"




ChatServer::ChatServer(qint16 port) : web_socket_server(QString("Chat Server"), QWebSocketServer::NonSecureMode, this)
{
    if (web_socket_server.listen(QHostAddress::Any, port))
    {
        std::clog << "Chat : ChatServer - Server listening for incoming connections at port " << port << std::endl;
        connect(&web_socket_server, &QWebSocketServer::newConnection, this, &ChatServer::onNewConnectionRequest);

        std::ifstream users_file("users");
        if (users_file.is_open())
        {
            User user;
            while (!(users_file >> user).eof()) {
                user_list.push_back(user);
            }
        }
    }
    else
    {
        throw ChatServerException();
    }
}



ChatServer::~ChatServer()
{
    web_socket_server.close();
}



void ChatServer::onNewConnectionRequest()
{
    std::clog << "Chat : ChatServer - New connection request received" << std::endl;

    QWebSocket *socket = web_socket_server.nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &ChatServer::onTextMessageReceived);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &ChatServer::onBinaryMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &ChatServer::onSocketDisconnected);

    client_list_to_user_list_map.insert(std::make_pair<unsigned, unsigned>(client_list.size(), 0));
    client_list.push_back(socket);
    client_authentication_status.push_back(false);

    socket->sendTextMessage(QString("Ehlo"));
}



void ChatServer::onBinaryMessageReceived(const QByteArray &byte_stream)
{   // onBinaryMessageReceived
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());

    unsigned int index = 0;

    for (auto iterator : client_list) {
        if (iterator == client) {
            break;
        }
        else {
            index++;
        }
    }

    std::stringstream data_stream(byte_stream.toStdString());
    std::string type;

    data_stream >> type;

    if (type == "Credentials")
    {
        std::clog << "Chat : ChatServer - Authentication requested" << std::endl;

        std::string username, password;
        data_stream >> username >> password;

        for (unsigned int i=0; i<user_list.size(); i++)
        {
            if (username == user_list[i].getNickname())
            {
                std::ifstream password_file("passwords");
                if (password_file.is_open())
                {
                    std::string stored_password;

                    for (unsigned int j = 0; j <= i; ++j) {
                        password_file >> password;
                    }
                    password_file.close();

                    if (stored_password == password) {
                        client_list_to_user_list_map[index] = i;
                        client_authentication_status[index] = true;
                        client->sendTextMessage(QByteArray("Login authenticated"));

                        std::stringstream user_data_stream;
                        user_data_stream << "userdata " << user_list[i];
                        std::string user_data;
                        std::getline(user_data_stream, user_data);
                        client->sendBinaryMessage(user_data.c_str());

                        for (auto client : client_list) {
                            // Send the available userlist
                            std::stringstream reply_stream;
                            reply_stream << "userlist ";

                            for (auto user : user_list) {
                                reply_stream << user << " ";
                            }

                            std::string reply;
                            std::getline(reply_stream, reply);

                            client->sendBinaryMessage(QByteArray(reply.c_str()));
                        }

                        emit newConnectionRequest(user_list[i]);
                        return;
                    }
                    else {
                        client->sendTextMessage("Invalid login");
                        return;
                    }
                }
            }
        }

        // Username not exist, create one
        User new_user(username, QUuid::createUuid().toString().toStdString());
        user_list.push_back(new_user);

        std::ofstream password_file("passwords", std::ios::app);
        if (!password_file.is_open()) {
            std::cerr << "Chat : ChatServer - Unable to open password file" << std::endl;
            return;
        }
        else {
            password_file << password << std::endl;
            password_file.close();
        }

        std::ofstream users_file("users", std::ios::app);
        if (!users_file.is_open()) {
            std::cerr << "Chat : ChatServer - Unable to open users file" << std::endl;
            return;
        }
        else {
            users_file << user_list[user_list.size() - 1] << std::endl;
            users_file.close();
        }

        client_list_to_user_list_map[index] = user_list.size() - 1;
        client_authentication_status[index] = true;
        client->sendTextMessage("Login authenticated");

        std::stringstream user_data_stream;
        user_data_stream << "userdata " << user_list[user_list.size() - 1];
        std::string user_data;
        std::getline(user_data_stream, user_data);
        client->sendBinaryMessage(user_data.c_str());

        for (auto client : client_list) {
            // Send the available userlist
            std::stringstream reply_stream;
            reply_stream << "userlist ";

            for (auto user : user_list) {
                reply_stream << user << " ";
            }

            std::string reply;
            std::getline(reply_stream, reply);

            client->sendBinaryMessage(QByteArray(reply.c_str()));
        }

        emit newConnectionRequest(new_user);
    }


    std::clog << "Chat : ChatServer - Binary messaage received" << std::endl;
}



void ChatServer::onTextMessageReceived(const QString &data)
{
    User from, to;
    std::string message;
    std::stringstream data_stream(data.toStdString());

    std::getline(data_stream >> from >> to, message);

    for (unsigned int i=0; i<user_list.size(); ++i) {
        if (user_list[i] == to && client_list[i]->state() == QAbstractSocket::SocketState::ConnectedState) {
            client_list[i]->sendTextMessage(data);
            break;
        }/**
        else {
            // Store the message to be sent later
        }*/
    }

    std::clog << "Chat : ChatServer - Text messaage received" << std::endl;
}



void ChatServer::onSocketDisconnected()
{
    std::clog << "Chat : ChatServer - Client disconnected" << std::endl;

    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    for (unsigned int i=0; i<client_list.size(); ++i) {
        if (client_list[i] == client) {
            client_list.erase(client_list.begin() + i);
            client_authentication_status.erase(client_authentication_status.begin() + i);
            client_list_to_user_list_map.erase(i);
            break;
        }
    }
    client->deleteLater();
}
