#include "membermodel.hpp"

MemberModel::MemberModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

MemberModel::~MemberModel()
{
    clearData();
}

int MemberModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_members.size();
}

QVariant MemberModel::data(const QModelIndex &index, int role) const
{
    QVariant wrapper;

    if(index.row() >= 0 && index.row() < m_members.size())
    {
        const Member * const item = m_members.at(index.row());

        switch(role)
        {
        case GuidRole:
            wrapper.setValue(item->guid());
            break;
        case NameRole:
            wrapper.setValue(item->name());
            break;
        case JobRole:
            wrapper.setValue(item->job());
            break;
        }
    }

    return wrapper;
}

QList<Member*> MemberModel::membersByIndexes(QList<qint32> indexes)
{
    QList<Member*> members;
    foreach(qint32 index, indexes)
    {
        members.append(m_members.at(index));
    }
    return members;
}

void MemberModel::membersReset(const QList<Member *> members)
{
    beginResetModel();
    clearData();
    m_members.clear();
    m_members.append(members);
    endResetModel();
    emit countChanged(m_members.size());
}

void MemberModel::insertMember(Member *member)
{
    beginInsertRows(QModelIndex(), m_members.size(), m_members.size());
    m_members.append(member);
    endInsertRows();
    emit countChanged(m_members.size());
}

void MemberModel::deleteMember(const quint64 &guid, const qint32 &index)
{
    Q_UNUSED(guid)
    beginRemoveRows(QModelIndex(), index, index);
    m_members.removeAt(index);
    endRemoveRows();
    emit countChanged(m_members.size());
}

QHash<int, QByteArray> MemberModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GuidRole] = QByteArrayLiteral("guid");
    roles[NameRole] = QByteArrayLiteral("name");
    roles[JobRole] = QByteArrayLiteral("job");
    return roles;
}

void MemberModel::clearData()
{
    if(!m_members.isEmpty())
    {
        for (int i = 0; i < m_members.size(); ++i) {
            Member* member;
            member = m_members.at(i);
            member->deleteLater();
            member = nullptr;
        }
    }
}
