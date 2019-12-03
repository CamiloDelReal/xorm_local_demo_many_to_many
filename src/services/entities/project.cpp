#include "project.hpp"
#include "member.hpp"

Project::Project(QObject *parent)
    : QObject(parent), XTableModel<Project>()
{
    m_guid = 0;
}

Project::Project(const QString &name, const QString &description, QObject *parent)
    : QObject(parent), XTableModel<Project>()
{
    m_name = name;
    m_description = description;
}

Project::Project(const quint64 &guid, const QString &name, const QString &description, QObject *parent)
    : QObject(parent), XTableModel<Project>()
{
    m_guid = guid;
    m_name = name;
    m_description = description;
}

Project::Project(const Project &other)
    : QObject(other.parent()), XTableModel<Project>()
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_description = other.m_description;
    m_members.append(other.m_members);
}

Project::~Project()
{
    clearMembers();
}

Project& Project::operator=(const Project &other)
{
    m_guid = other.m_guid;
    m_name = other.m_name;
    m_description = other.m_description;
    clearMembers();
    m_members.append(other.m_members);

    setParent(other.parent());

    return *this;
}

quint64 Project::guid() const
{
    return m_guid;
}

QString Project::name() const
{
    return m_name;
}

QString Project::description() const
{
    return m_description;
}

QList<Member*> Project::members() const
{
    return m_members;
}

void Project::setGuid(const quint64 &guid)
{
    if (m_guid != guid)
    {
        m_guid = guid;
        emit guidChanged(m_guid);
    }
}

void Project::setName(const QString &name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Project::setDescription(const QString &description)
{
    if (m_description != description)
    {
        m_description = description;
        emit descriptionChanged(m_description);
    }
}

void Project::setMembers(QList<Member*> members)
{
    clearMembers();
    m_members = members;
    emit membersChanged(m_members);
}

void Project::clearMembers()
{
    if(!m_members.isEmpty())
    {
        foreach(Member* member, m_members)
        {
            member->deleteLater();
            member = nullptr;
        }
        m_members.clear();
    }
}
