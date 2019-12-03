#ifndef MEMBERLISTINGVIEWMODEL_HPP
#define MEMBERLISTINGVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "membermodel.hpp"


class MemberListingViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(QObject* memberModel READ memberModel NOTIFY memberModelChanged)

public:
    explicit MemberListingViewModel(QObject *parent = nullptr);

    bool isWorking() const;
    QObject* memberModel();

    Q_INVOKABLE void readMembers();
    Q_INVOKABLE void deleteMember(const quint64 &guid, const qint32 &index);

signals:
    void isWorkingChanged(const bool &isWorking);
    void memberModelChanged(QObject* memberModel);

    void membersReset(const QList<Member*> members);
    void memberDeleted(const quint64 &guid, const qint32 &index);

private:
    bool m_isWorking;
    MemberModel m_memberModel;

    QSqlDatabase m_appDatabase;
    XDao<Member> m_memberDao;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // MEMBERLISTINGVIEWMODEL_HPP
