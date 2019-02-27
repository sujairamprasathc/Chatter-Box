#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QListView>
#include <vector>

#include "Message.h"


class MessageModel : public QAbstractListModel
{
    Q_OBJECT

private:
    std::vector<Message> message_list;

public:
    MessageModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addMessage(const Message&);
};

#endif // MESSAGEMODEL_H
