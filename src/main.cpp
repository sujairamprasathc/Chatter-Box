#include <QApplication>
#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gui::welcome_dialog = new WelcomeDialog;
    gui::welcome_dialog->show();

    return a.exec();
}
