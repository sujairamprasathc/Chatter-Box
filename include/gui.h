#ifndef GUI_H
#define GUI_H

class WelcomeDialog;
class ChatServerWindow;
class ConnectToServerDialog;
class ChatRoomWindow;

namespace gui
{

    extern WelcomeDialog *welcome_dialog;
    extern ChatServerWindow *chat_server_window;
    extern ConnectToServerDialog *connect_to_server_dialog;
    extern ChatRoomWindow *chat_room_window;

}


#include "welcomedialog.h"
#include "chatserverwindow.h"
#include "chatroomwindow.h"
#include "connecttoserverdialog.h"

#endif // GUI_H
