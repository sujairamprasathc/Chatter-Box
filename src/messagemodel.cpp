#include "messagemodel.h"



MessageModel::MessageModel(QObject *parent) : QAbstractListModel(parent)
{}




int MessageModel::rowCount(const QModelIndex &parent) const
{
    return message_list.size();
}



QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= message_list.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return QString((message_list.at(index.row()).getSender().getNickname() + " : " + message_list.at(index.row()).getTextMessage()).c_str());
    }
    return QVariant();
}



void MessageModel::addMessage(const Message &message)
{
    beginResetModel();
    message_list.push_back(message);
    endResetModel();

    beginInsertRows(QModelIndex(), 0, message_list.size() - 1);
    endInsertRows();
}
