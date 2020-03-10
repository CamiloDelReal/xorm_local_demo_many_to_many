#ifndef MEMBEREDITIONVIEWMODEL_HPP
#define MEMBEREDITIONVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "member.hpp"
#include "projectmodel.hpp"


class MemberEditionViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(QObject* projectModel READ projectModel NOTIFY projectModelChanged)

public:
    explicit MemberEditionViewModel(QObject *parent = nullptr);

    bool isWorking() const;
    QObject* projectModel();

    Q_INVOKABLE void readProjects();
    Q_INVOKABLE void createMember(const QString &name, const QString &job, QList<int> selectedProjects);

signals:
    void isWorkingChanged(const bool &isWorking);
    void projectModelChanged(QObject* projectModel);

    void projectsReset(QList<Project*> projects);
    void memberCreated(Member *member);

private:
    bool m_isWorking;
    ProjectModel m_projectModel;
    QSqlDatabase m_appDatabase;
    XDao<Project> m_projectDao;
    XDao<Member> m_memberDao;
    XDao<MemberProject> m_memberProjectDao;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // MEMBEREDITIONVIEWMODEL_HPP
