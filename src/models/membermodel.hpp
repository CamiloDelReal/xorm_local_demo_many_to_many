#ifndef MEMBERMODEL_HPP
#define MEMBERMODEL_HPP

#include <QObject>
#include <QAbstractListModel>

#include "member.hpp"

class MemberModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(quint32 count READ rowCount NOTIFY countChanged)

public:
    enum MemberModelRoles
    {
        GuidRole = Qt::UserRole + 1,
        NameRole,
        JobRole
    };

    explicit MemberModel(QObject *parent = nullptr);
    ~MemberModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QList<Member*> membersByIndexes(QList<qint32> indexes);

public slots:
    void membersReset(const QList<Member*> members);
    void insertMember(Member *member);
    void deleteMember(const quint64 &guid, const qint32 &index);

signals:
    void countChanged(qint32 count);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Member*> m_members;

    void clearData();
};

#endif // MEMBERMODEL_HPP
