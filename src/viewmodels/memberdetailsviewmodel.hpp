#ifndef MEMBERDETAILSVIEWMODEL_HPP
#define MEMBERDETAILSVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "member.hpp"
#include "project.hpp"
#include "projectmodel.hpp"


class MemberDetailsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(Member* currentMember READ currentMember NOTIFY currentMemberChanged)
    Q_PROPERTY(QObject* projectModel READ projectModel NOTIFY projectModelChanged)

public:
    explicit MemberDetailsViewModel(QObject *parent = nullptr);
    ~MemberDetailsViewModel();

    bool isWorking() const;
    Member* currentMember() const;    
    QObject* projectModel();

    Q_INVOKABLE void readMember(const quint64 &guid);

signals:
    void isWorkingChanged(const bool &isWorking);
    void currentMemberChanged(Member* currentMember);

    void projectsReset(QList<Project*> projects);
    void projectModelChanged(QObject* projectModel);

private:
    bool m_isWorking;
    Member* m_currentMember;
    ProjectModel m_projectModel;
    QSqlDatabase m_appDatabase;
    XDao<Member> m_memberDao;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // MEMBERDETAILSVIEWMODEL_HPP
