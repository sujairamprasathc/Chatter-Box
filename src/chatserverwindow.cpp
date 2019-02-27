#include "chatserverwindow.h"
using namespace chat_server_window;

ChatServerWindow::ChatServerWindow() : port_validator(0, 65563, this), start_server_button(this),
    port_input_box(this), port_label(this), ip_address_label(this), ip_address_display_label(this)
{
    setUpStartScreen();
    connect(&start_server_button, &QPushButton::clicked, this, &ChatServerWindow::onStartServerButtonClicked);
}



void ChatServerWindow::onStartServerButtonClicked()
{
    std::clog << "Chat : StartServerDialog - Start Server Button clicked" << std::endl;

    unsigned int port = port_input_box.text().toUInt();

    try {
        chat_server = new ChatServer(port);
        setUpClientList();
        connect(chat_server, &ChatServer::newConnectionRequest, this, &ChatServerWindow::onNewConnectionAdded);
    }
    catch (ChatServerException &e)
    {
        std::clog << e.what() << std::endl;
    }
}



void ChatServerWindow::setUpStartScreen()
{
    start_server_button.setGeometry(280, 400, 80, 30);
    start_server_button.setText(START_SERVER_BUTTON_TEXT);

    port_input_box.setGeometry(350, 200, 150, 30);
    port_input_box.setValidator(&port_validator);

    ip_address_label.setText(IP_ADDRESS_LABEL_TEXT);
    ip_address_label.setGeometry(150, 150, 150, 30);

    port_label.setText(PORT_LABEL_TEXT);
    port_label.setGeometry(150, 200, 150, 30);

    // Fetch current ip address
    QString ip_address;

    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int i=0; i<list.count(); i++)
    {
        if(!list[i].isLoopback()) {
            if (list[i].protocol() == QAbstractSocket::IPv4Protocol ) {
                ip_address = list[i].toString();
            }
        }

    }

    ip_address_display_label.setText(ip_address);
    ip_address_display_label.setGeometry(350, 150, 150, 30);

    start_server_button.show();
    port_input_box.show();
    port_label.show();
    ip_address_label.show();
    ip_address_display_label.show();
}



void ChatServerWindow::setUpClientList()
{
    start_server_button.hide();
    port_input_box.hide();
    port_label.hide();
    ip_address_label.hide();
    ip_address_display_label.hide();

    client_list = new QListWidget(this);
    client_list->setGeometry(0, 0, 640, 480);
    client_list->show();
}



void ChatServerWindow::onNewConnectionAdded(const User& new_user)
{
    client_list->addItem(QString(new_user.getUserId().c_str()) + ":" + QString(new_user.getNickname().c_str()));
}
