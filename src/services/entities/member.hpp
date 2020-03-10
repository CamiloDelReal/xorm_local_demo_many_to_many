#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <QObject>

#include "xtablemodel.hpp"


class Project;
class MemberProject;

class Member : public QObject, public XTableModel<Member>
{
    Q_OBJECT

    Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString job READ job WRITE setJob NOTIFY jobChanged)

    Q_PROPERTY(QList<Project*> projects READ projects WRITE setProjects NOTIFY projectsChanged)

    X_TABLE_NAME("members")
    X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                   X_FIELD(name),
                   X_FIELD(job))
    X_FOREIGN_LISTS(X_INTERMEDIATED_FOREIGN_LIST(Project, guid, Member, guid, MemberProject, projectId, memberId, projects))

public:
    explicit Member(QObject *parent = nullptr);
    Member(const quint64 &guid, const QString &name, const QString &job, QObject *parent = nullptr);
    Member(const QString &name, const QString &job, QObject *parent = nullptr);
    Member(const Member &other);

    ~Member();

    Member& operator=(const Member &other);

    quint64 guid() const;
    QString name() const;
    QString job() const;

    QList<Project*> projects() const;

public slots:
    void setGuid(const quint64 &guid);
    void setName(const QString &name);
    void setJob(const QString &job);

    void setProjects(QList<Project*> projects);

signals:
    void guidChanged(const quint64 &guid);
    void nameChanged(const QString &name);
    void jobChanged(const QString &job);

    void projectsChanged(QList<Project*> projects);

private:
    quint64 m_guid;
    QString m_name;
    QString m_job;
    QList<Project*> m_projects;

    void clearProjects();
};

#include "project.hpp"
#include "memberproject.hpp"

#endif // MEMBER_HPP
