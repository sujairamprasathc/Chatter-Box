#include "conversationmodel.h"



ConversationModel::ConversationModel(QObject *parent) : QAbstractListModel(parent)
{}




int ConversationModel::rowCount(const QModelIndex &parent) const
{
    return user_list.size();
}



QVariant ConversationModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= user_list.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return QString(user_list.at(index.row()).getNickname().c_str());
    }
    return QVariant();
}



void ConversationModel::updateUserList(const std::vector<User> &user_list)
{
    beginResetModel();
    this->user_list = user_list;
    endResetModel();

    beginInsertRows(QModelIndex(), 0, user_list.size() - 1);
    endInsertRows();
}
