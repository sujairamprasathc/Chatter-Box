#include "chatroomwindow.h"
using namespace chat_room;




ChatRoomWindow::ChatRoomWindow() : QMainWindow(nullptr), initialized(false)
{
    // Set up Window
    this->setGeometry(150, 150, 640, 480);
    setWindowTitle(tr("Chat"));
    setMinimumSize(640, 480);

    // Menu Bar
    exit_chat_action = new QAction(QString("Exit"), this);
    chat_menu = menuBar()->addMenu(tr("Chat"));
    chat_menu->addAction(exit_chat_action);
    connect(exit_chat_action, &QAction::triggered, this, &ChatRoomWindow::exitCurrentChat);
    menuBar()->hide();

    // Conversation List
    conversation_model = new ConversationModel(this);
    conversation_list = new QListView(this);
    conversation_list->setModel(conversation_model);
    conversation_list->setGeometry(0, 0, 640, 480);
    connect(conversation_list, &QListView::clicked, this, &ChatRoomWindow::onConversationListClicked);

    // Additional set-up
    app_data_directory = QString(getenv("LOCALAPPDATA")) + QString("/ChatApp/");
    connect(client_socket, &QWebSocket::textMessageReceived, this, &ChatRoomWindow::onTextMessageReceived);
    connect(client_socket, &QWebSocket::binaryMessageReceived, this, &ChatRoomWindow::onBinaryMessageReceived);

    std::clog << "Chat : ChatRoomWindow set up!" << std::endl;
}



ChatRoomWindow::~ChatRoomWindow()
{
    if (message_list) {
        delete message_list;
    }
    if (conversation_list) {
        delete conversation_list;
    }
    if (message_model) {
        delete message_model;
    }
    if (conversation_model) {
        delete conversation_model;
    }
    if (send_text_button) {
        delete send_text_button;
    }
    if (message_input_box) {
        delete message_input_box;
    }
    if (chat_menu_bar) {
        delete chat_menu_bar;
    }
    if (chat_menu) {
        delete chat_menu;
    }
    if (exit_chat_action) {
        delete exit_chat_action;
    }
}



void ChatRoomWindow::onConversationListClicked(const QModelIndex& model_index)
{
    std::clog << "Chat : ChatRoomWindow - Chat list item clicked" << std::endl;

    unsigned int index = model_index.row();
    User clicked_user = user_list[index];
    current_receiver = clicked_user;

    // Open the particular conversation
    this->setUpChatRoom();

    // Add pending messages
    std::stringstream file_name_stream;
    file_name_stream << current_receiver << current_user;
    std::string file_name;
    std::getline(file_name_stream, file_name);

    std::ifstream pending_message_file(file_name);
    if (pending_message_file.is_open())
    {
        Message message;

        while (!(pending_message_file >> message).eof()) {
            message_model->addMessage(message);
        }

        pending_message_file.close();
        std::remove(file_name.c_str());
    }

    initialized = true;
}



void ChatRoomWindow::onSendTextButtonClicked()
{
    std::clog << "Chat : ChatRoomWindow - Send text button clicked" << std::endl;

    QString text = message_input_box->text();
    message_input_box->setText(QString(""));
    if (!text.isEmpty()) {
        Message message(current_user, current_receiver, text.toStdString());
        message_model->addMessage(message);

        std::stringstream message_stream;
        message_stream << message;
        std::string data;
        std::getline(message_stream, data);
        client_socket->sendTextMessage(QString(data.c_str()));
    }
}



void ChatRoomWindow::onReturnKeyPressed()
{
    std::clog << "Chat : ChatRoom - Return key pressed" << std::endl;

    QString text = message_input_box->text();
    message_input_box->setText(QString(""));
    if (!text.isEmpty()) {
        Message message(current_user, current_receiver, text.toStdString());
        message_model->addMessage(message);

        std::stringstream message_stream;
        message_stream << message;
        std::string data;
        std::getline(message_stream, data);
        client_socket->sendTextMessage(QString(data.c_str()));
    }
}



void ChatRoomWindow::onTextMessageReceived(const QString &data)
{
    std::clog << "Chat : ChatRoomWindow - New message received" << std::endl;

    std::stringstream data_stream(data.toStdString());
    User from, to;
    std::string text;
    std::getline(data_stream >> from >> to, text);

    Message message(from, to, text);

    if (!text.empty()) {
        if (from == current_receiver) {
            message_model->addMessage(message);
        }
        else {
            std::stringstream file_name_stream;
            file_name_stream >> from >> to;
            std::string file_name;
            std::getline(file_name_stream, file_name);

            std::ofstream pending_messages_file(file_name, std::ios::app);
            pending_messages_file << message << std::endl;
        }
    }
}



void ChatRoomWindow::onBinaryMessageReceived(const QByteArray &byte_stream)
{
    std::clog << "Chat : ChatRoomWindow - Binary data received from server" << std::endl;

    std::stringstream data_stream(byte_stream.toStdString());

    std::string type;
    data_stream >> type;

    if (type == "userlist")
    {
        User user;
        user_list.erase(user_list.begin(), user_list.end());

        while (!(data_stream >> user).eof())
        {
            user_list.push_back(user);
        }

        conversation_model->updateUserList(user_list);
    }
    else if (type == "userdata") {
        data_stream >> current_user;
        std::clog << "Chat : ChatRoomWindow - Current user data populated" << std::endl;
    }
}



void ChatRoomWindow::setUpChatRoom()
{
    conversation_list->hide();

    send_text_button = new QPushButton(SEND_TEXT_BUTTON_TEXT, this);
    message_input_box = new QLineEdit(this);
    message_list = new QListView(this);

    send_text_button->setGeometry(540, 460, 80, 40);

    message_input_box->setGeometry(0, 440, 560, 40);
    message_input_box->setFont(QFont("Default", 15));

    message_model = new MessageModel(this);
    message_list->setModel(message_model);
    message_list->setGeometry(0, 25, 640, 415);
    message_list->setFont(QFont("Default", 15));

    menuBar()->show();

    send_text_button->show();
    message_input_box->show();
    message_list->show();

    connect(send_text_button, &QPushButton::clicked, this, &ChatRoomWindow::onSendTextButtonClicked);
    connect(message_input_box, &QLineEdit::returnPressed, this, &ChatRoomWindow::onReturnKeyPressed);
}



void ChatRoomWindow::exitCurrentChat()
{
    std::clog << "Chat : ChatRoom - Current chat exited" << std::endl;

    send_text_button->disconnect();
    message_input_box->disconnect();
    message_list->disconnect();

    delete send_text_button;
    delete message_input_box;
    delete message_list;

    menuBar()->hide();

    conversation_list->show();
}
