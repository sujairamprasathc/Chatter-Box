#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QtWebSockets/QtWebSockets>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <QUuid>

#include "User.h"
#include "chatserverexception.h"


class ChatServer : public QObject
{
    Q_OBJECT

private:
    QWebSocketServer web_socket_server;
    std::vector<User> user_list;

    std::vector<bool> client_authentication_status;
    std::vector<QWebSocket *> client_list;
    std::map<unsigned int, unsigned int> client_list_to_user_list_map;

private slots:
    void onBinaryMessageReceived(const QByteArray&);
    void onTextMessageReceived(const QString&);
    void onNewConnectionRequest();
    void onSocketDisconnected();

signals:
    void newConnectionRequest(const User&);

public:
    ChatServer(qint16 port);
    ~ChatServer();
};

#endif // CHATSERVER_H
