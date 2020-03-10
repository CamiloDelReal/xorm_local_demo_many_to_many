#ifndef PROJECTEDITIONVIEWMODEL_HPP
#define PROJECTEDITIONVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "project.hpp"
#include "member.hpp"
#include "membermodel.hpp"


class ProjectEditionViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(QObject* memberModel READ memberModel NOTIFY memberModelChanged)

public:
    explicit ProjectEditionViewModel(QObject *parent = nullptr);

    bool isWorking() const;
    QObject* memberModel();

    Q_INVOKABLE void readMembers();
    Q_INVOKABLE void createProject(const QString &name, const QString &job, const QList<qint32> &indexes);

signals:
    void isWorkingChanged(const bool &isWorking);
    void memberModelChanged(QObject* memberModel);

    void membersReset(QList<Member*> members);
    void projectCreated(Project *project);

private:
    bool m_isWorking;
    MemberModel m_memberModel;
    QSqlDatabase m_appDatabase;
    XDao<Member> m_memberDao;
    XDao<Project> m_projectDao;
    XDao<MemberProject> m_memberProjectDao;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // PROJECTEDITIONVIEWMODEL_HPP
