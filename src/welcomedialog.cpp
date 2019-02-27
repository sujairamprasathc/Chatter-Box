#include "welcomedialog.h"



WelcomeDialog::WelcomeDialog() : server_button(QString("Host a server"), this),
    client_button(QString("Connect to server"), this), welcome_label("Welcome", this)
{
    server_button.setGeometry(245, 227, 150, 25);
    client_button.setGeometry(245, 277, 150, 25);

    connect(&server_button, &QPushButton::clicked, this, &WelcomeDialog::onServerButtonClicked);
    connect(&client_button, &QPushButton::clicked, this, &WelcomeDialog::onClientButtonClicked);

    welcome_label.setGeometry(245, 177, 150, 25);
    welcome_label.setAlignment(Qt::AlignHCenter);
    welcome_label.setFont(QFont(QString("Default"), 15));
}



void WelcomeDialog::onClientButtonClicked()
{
    std::clog << "Chat : WelcomeDialog - Client Button clicked" << std::endl;

    gui::connect_to_server_dialog = new ConnectToServerDialog;
    gui::connect_to_server_dialog->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), this->geometry().height());
    gui::connect_to_server_dialog->show();

    this->hide();
}



void WelcomeDialog::onServerButtonClicked()
{
    std::clog << "Chat : WelcomeDialog - Server Button clicked" << std::endl;

    gui::chat_server_window = new ChatServerWindow;
    gui::chat_server_window->setGeometry(this->geometry().x(), this->geometry().y(), this->geometry().width(), this->geometry().height());
    gui::chat_server_window->show();

    this->hide();
}
