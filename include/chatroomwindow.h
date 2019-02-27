#ifndef CHATROOMWINDOW_H
#define CHATROOMWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <iostream>
#include <cstdio>
#include <list>

#include "User.h"
#include "network.h"
#include "Message.h"
#include "messagemodel.h"
#include "conversationmodel.h"
#include "englishtextlabels.h"

class ChatRoomWindow : public QMainWindow
{
private:
    User current_user, current_receiver;

    MessageModel *message_model;
    ConversationModel *conversation_model;
    QListView *message_list, *conversation_list;
    QPushButton *send_text_button;
    QLineEdit *message_input_box;
    QString app_data_directory;
    QMenuBar *chat_menu_bar;
    QMenu *chat_menu;
    QAction *exit_chat_action;
    bool initialized;

    std::vector<User> user_list;

    void buildMenu();
    void setUpChatRoom();

private slots:
    void onBinaryMessageReceived(const QByteArray&);
    void onTextMessageReceived(const QString&);
    void onReturnKeyPressed();
    void onSendTextButtonClicked();
    void onConversationListClicked(const QModelIndex&);

    // Menu Slots
    void exitCurrentChat();

public:
    ChatRoomWindow();
    ~ChatRoomWindow();
};

#endif // CHATROOMWINDOW_H
