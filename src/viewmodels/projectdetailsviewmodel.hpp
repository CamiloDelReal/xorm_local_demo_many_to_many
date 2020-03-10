#ifndef PROJECTDETAILSVIEWMODEL_HPP
#define PROJECTDETAILSVIEWMODEL_HPP

#include <QObject>

#include "xdao.hpp"
#include "project.hpp"
#include "member.hpp"
#include "membermodel.hpp"


class ProjectDetailsViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(Project* currentProject READ currentProject NOTIFY currentProjectChanged)
    Q_PROPERTY(QObject* memberModel READ memberModel NOTIFY memberModelChanged)

public:
    explicit ProjectDetailsViewModel(QObject *parent = nullptr);
    ~ProjectDetailsViewModel();

    bool isWorking() const;
    Project* currentProject() const;    
    QObject* memberModel();

    Q_INVOKABLE void readProject(const quint64 &guid);

signals:
    void isWorkingChanged(const bool &isWorking);
    void currentProjectChanged(Project* currentProject);

    void membersReset(QList<Member*> members);
    void memberModelChanged(QObject* projectModel);

private:
    bool m_isWorking;
    MemberModel m_memberModel;
    QSqlDatabase m_appDatabase;
    XDao<Project> m_projectDao;
    Project* m_currentProject;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // PROJECTDETAILSVIEWMODEL_HPP
