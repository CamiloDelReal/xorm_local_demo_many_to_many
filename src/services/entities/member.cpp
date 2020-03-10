#include "member.hpp"

Member::Member(QObject *parent)
    : QObject(parent), XTableModel<Member>()
{
    m_guid = 0;
}

Member::Member(const quint64 &guid, const QString &name, const QString &job, QObject *parent)
    : QObject (parent), XTableModel<Member>()
{
    m_guid = guid;
    m_name = name;
    m_job = job;
}

Member::Member(const QString &name, const QString &job, QObject *parent)
    : QObject (parent), XTableModel<Member>()
{
    m_guid = 0;
    m_name = name;
    m_job = job;
}

Member::Member(const Member &other)
    : QObject (other.parent()), XTableModel<Member>()
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_job = other.m_job;
    m_projects.append(other.m_projects);
}

Member::~Member()
{
    clearProjects();
}

Member& Member::operator=(const Member &other)
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_job = other.m_job;
    clearProjects();
    m_projects.append(other.m_projects);

    setParent(other.parent());

    return *this;
}

quint64 Member::guid() const
{
    return m_guid;
}

QString Member::name() const
{
    return m_name;
}

QString Member::job() const
{
    return m_job;
}

QList<Project*> Member::projects() const
{
    return m_projects;
}

void Member::setGuid(const quint64 &guid)
{
    if (m_guid != guid)
    {
        m_guid = guid;
        emit guidChanged(m_guid);
    }
}

void Member::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Member::setJob(const QString &job)
{
    if (m_job != job)
    {
        m_job = job;
        emit jobChanged(m_job);
    }
}

void Member::setProjects(QList<Project*> projects)
{
    clearProjects();
    m_projects = projects;
    emit projectsChanged(m_projects);
}

void Member::clearProjects()
{
    if(!m_projects.isEmpty())
    {
        foreach(Project* project, m_projects)
        {
            project->deleteLater();
            project = nullptr;
        }
        m_projects.clear();
    }
}
