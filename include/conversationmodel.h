#ifndef CONVERSATIONMODEL_H
#define CONVERSATIONMODEL_H

#include <QListView>
#include <vector>

#include "User.h"


class ConversationModel : public QAbstractListModel
{
    Q_OBJECT

private:
    std::vector<User> user_list;

public:
    ConversationModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void updateUserList(const std::vector<User>&);
};

#endif // CONVERSATIONMODEL_H
