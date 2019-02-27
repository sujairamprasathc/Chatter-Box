#ifndef NETWORK_H
#define NETWORK_H

#include "chatserver.h"
#include <QSsl>

extern ChatServer *chat_server;
extern QWebSocket *client_socket;

#endif // NETWORK_H
