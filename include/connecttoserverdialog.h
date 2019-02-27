#ifndef CONNECTTOSERVERDIALOG_H
#define CONNECTTOSERVERDIALOG_H

#include <QtWidgets>
#include <iostream>
#include <QDialog>
#include <QWidget>

#include "gui.h"
#include "network.h"
#include "englishtextlabels.h"


class ConnectToServerDialog : public QDialog
{
private:
    QPushButton connect_button;
    QLineEdit ip_address_input_box, port_input_box, username_input_box, password_input_box;
    QLabel ip_address_label, port_label, username_label, password_label, connection_status_label;
    QIntValidator port_input_validator;

    QString username;

private slots:
    void onConnectButtonClicked();
    void onConnectionEstablished();
    void onDataReceived(QString);
    void onNetworkError();

public:
    ConnectToServerDialog();
};

#endif // CONNECTTOSERVERDIALOG_H
