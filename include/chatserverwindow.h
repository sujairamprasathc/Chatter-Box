#ifndef CHATSERVERWINDOW_H
#define CHATSERVERWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <iostream>

#include "gui.h"
#include "User.h"
#include "network.h"
#include "englishtextlabels.h"


class ChatServerWindow : public QMainWindow
{
private:
    QIntValidator port_validator;
    QPushButton start_server_button;
    QLineEdit port_input_box;
    QLabel port_label, ip_address_label, ip_address_display_label;

    QListWidget *client_list;

    void setUpClientList();
    void setUpStartScreen();

private slots:
    void onStartServerButtonClicked();
    void onNewConnectionAdded(const User&);

public:
    ChatServerWindow();
};

#endif // CHATSERVERWINDOW_H
