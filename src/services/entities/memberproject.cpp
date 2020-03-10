#include "memberproject.hpp"

MemberProject::MemberProject(QObject *parent)
    : QObject(parent), XTableModel<MemberProject> ()
{
    m_guid = 0;
    m_memberId = 0;
    m_projectId = 0;
    m_member = nullptr;
    m_project = nullptr;
}

MemberProject::MemberProject(const quint64 &memberId, const quint64 &projectId, QObject *parent)
    : QObject(parent), XTableModel<MemberProject>()
{
    m_guid = 0;
    m_memberId = memberId;
    m_projectId = projectId;
    m_member = nullptr;
    m_project = nullptr;
}

MemberProject::MemberProject(const quint64 &guid, const quint64 &memberId, const quint64 &projectId, QObject *parent)
    : QObject(parent), XTableModel<MemberProject>()
{
    m_guid = guid;
    m_memberId = memberId;
    m_projectId = projectId;
    m_member = nullptr;
    m_project = nullptr;
}

MemberProject::MemberProject(const MemberProject &other)
    : QObject(other.parent()), XTableModel<MemberProject>()
{
    m_guid = other.m_guid;
    m_memberId = other.m_memberId;
    m_projectId = other.m_projectId;
    m_member = other.m_member;
    m_project = other.m_project;
}

MemberProject::~MemberProject()
{
    clearMember();
    clearProject();
}

MemberProject& MemberProject::operator=(const MemberProject &other)
{
    m_guid = other.m_guid;
    m_memberId = other.m_memberId;
    m_projectId = other.m_projectId;
    clearMember();
    clearProject();
    m_member = other.m_member;
    m_project = other.m_project;

    setParent(other.parent());

    return *this;
}

quint64 MemberProject::guid() const
{
    return m_guid;
}

quint64 MemberProject::memberId() const
{
    return m_memberId;
}

quint64 MemberProject::projectId() const
{
    return m_projectId;
}

Member* MemberProject::member() const
{
    return m_member;
}

Project* MemberProject::project() const
{
    return m_project;
}

void MemberProject::setGuid(const quint64 &guid)
{
    if (m_guid != guid)
    {
        m_guid = guid;
        emit guidChanged(m_guid);
    }
}

void MemberProject::setMemberId(const quint64 &memberId)
{
    if (m_memberId != memberId)
    {
        m_memberId = memberId;
        emit memberIdChanged(m_memberId);
        setMember(nullptr);
    }
}

void MemberProject::setProjectId(const quint64 &projectId)
{
    if (m_projectId != projectId)
    {
        m_projectId = projectId;
        emit projectIdChanged(m_projectId);
        setProject(nullptr);
    }
}

void MemberProject::setMember(Member *member)
{
    if (m_member != member)
    {
        clearMember();
        m_member = member;
        emit memberChanged(m_member);
    }
}

void MemberProject::setProject(Project *project)
{
    if (m_project != project)
    {
        clearProject();
        m_project = project;
        emit projectChanged(m_project);
    }
}

void MemberProject::clearMember()
{
    if(m_member != nullptr)
    {
        m_member->deleteLater();
        m_member = nullptr;
    }
}

void MemberProject::clearProject()
{
    if(m_project != nullptr)
    {
        m_project->deleteLater();
        m_project = nullptr;
    }
}
