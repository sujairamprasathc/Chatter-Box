#include "connecttoserverdialog.h"
using namespace connect_to_server;

ConnectToServerDialog::ConnectToServerDialog() : connect_button("Connect", this), ip_address_input_box(this),
    port_input_box(this), username_input_box(this), password_input_box(this), ip_address_label(IP_ADDRESS_LABEL_TEXT, this),
    port_label(PORT_LABEL_TEXT, this), username_label(USERNAME_LABEL_TEXT, this), password_label(PASSWORD_LABEL_TEXT, this),
    connection_status_label(this), port_input_validator(0, 65536, this)
{
    connect_button.setGeometry(280, 400, 80, 30);

    ip_address_input_box.setGeometry(350, 120, 150, 30);
    username_input_box.setGeometry(350, 220, 150, 30);

    password_input_box.setGeometry(350, 270, 150, 30);
    password_input_box.setEchoMode(QLineEdit::EchoMode::Password);

    port_input_box.setGeometry(350, 170, 150, 30);
    port_input_box.setValidator(&port_input_validator);

    ip_address_label.setGeometry(150, 120, 150, 30);
    port_label.setGeometry(150, 170, 150, 30);
    username_label.setGeometry(150, 220, 150, 30);
    password_label.setGeometry(150, 270, 150, 30);
    connection_status_label.setGeometry(150, 350, 340, 30);
    connection_status_label.setAlignment(Qt::AlignCenter);

    connect(&connect_button, &QPushButton::clicked, this, &ConnectToServerDialog::onConnectButtonClicked);
}



void ConnectToServerDialog::onConnectButtonClicked()
{
    std::clog << "Chat : ConnectToServerDialog - Connect button clicked" << std::endl;

    QString ip_address = ip_address_input_box.text();
    QString port = port_input_box.text();

    // Attempt to connect to server
    client_socket = new QWebSocket;
    connect(client_socket, &QWebSocket::connected, this, &ConnectToServerDialog::onConnectionEstablished);
    connect(client_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &ConnectToServerDialog::onNetworkError);

    QString url_string("ws://" + ip_address + ":" + port);
    client_socket->open(QUrl(url_string));
    connection_status_label.setText("Connecting");

    std::clog << "Chat : ConnectToServerDialog - Attempting to connect to server at url " << url_string.toStdString() << std::endl;
}



void ConnectToServerDialog::onConnectionEstablished()
{
    std::clog << "Connection Established" << std::endl;

    username = username_input_box.text();
    QString password = password_input_box.text();

    // Verify user
    client_socket->sendBinaryMessage("Credentials " + username.toLocal8Bit() + " " + password.toLocal8Bit());

    connect(client_socket, &QWebSocket::textMessageReceived, this, &ConnectToServerDialog::onDataReceived);
}



void ConnectToServerDialog::onDataReceived(QString reply)
{
    if (reply == "Ehlo") {
        std::clog << "Chat : ConnectToServerDialog - Welcome message received from server" << std::endl;
    }
    else if (reply == "Login authenticated") {
        std::clog << "Chat : ConnectToServerDialog - User successfully logged in" << std::endl;

        gui::chat_room_window = new ChatRoomWindow();
        gui::chat_room_window->show();
        this->hide();

        disconnect(client_socket, &QWebSocket::textMessageReceived, this, &ConnectToServerDialog::onDataReceived);
        disconnect(client_socket, &QWebSocket::connected, this, &ConnectToServerDialog::onConnectionEstablished);
    }
    else if (reply == "Invalid login") {
        std::clog << "Chat : ConnectToServerDialog - Invalid credentials passed" << std::endl;
        connection_status_label.setText("Invalid Login");
        client_socket->close();
        delete client_socket;
    }
    else {
        std::clog << "Chat : ConnectToServerDialog - Unknown response from server" << std::endl;
        connection_status_label.setText("Unknown error occured");
    }
}



void ConnectToServerDialog::onNetworkError()
{
    std::clog << "Chat : ConnectToServerDialog - Network Error" << std::endl;
    connection_status_label.setText("Error connecting to server! Please try again!");
}
