#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>
#include <QWidget>
#include <iostream>
#include <QtWidgets>

#include "gui.h"
#include "englishtextlabels.h"

class WelcomeDialog : public QDialog
{
private:
    QPushButton server_button, client_button;
    QLabel welcome_label;

private slots:
    void onServerButtonClicked();
    void onClientButtonClicked();

public:
    WelcomeDialog();
};

#endif // WELCOMEDIALOG_H
