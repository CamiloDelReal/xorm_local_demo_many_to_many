#ifndef MEMBERPROJECT_HPP
#define MEMBERPROJECT_HPP

#include <QObject>

#include "xtablemodel.hpp"


class Member;
class Project;

class MemberProject : public QObject, public XTableModel<MemberProject>
{
    Q_OBJECT
    Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
    Q_PROPERTY(quint64 memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)
    Q_PROPERTY(quint64 projectId READ projectId WRITE setProjectId NOTIFY projectIdChanged)

    Q_PROPERTY(Member* member READ member WRITE setMember NOTIFY memberChanged)
    Q_PROPERTY(Project* project READ project WRITE setProject NOTIFY projectChanged)

    X_TABLE_NAME("members_projects")
    X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                   X_FIELD(memberId, "member_id", X_FOREIGN_KEY(Member, X_CASCADE, X_CASCADE)),
                   X_FIELD(projectId, "project_id", X_FOREIGN_KEY(Project, X_CASCADE, X_CASCADE)))

public:
    explicit MemberProject(QObject *parent = nullptr);
    MemberProject(const quint64 &memberId, const quint64 &projectId, QObject *parent = nullptr);
    MemberProject(const quint64 &guid, const quint64 &memberId, const quint64 &projectId, QObject *parent = nullptr);
    MemberProject(const MemberProject &other);

    ~MemberProject();

    MemberProject& operator=(const MemberProject &other);

    quint64 guid() const;
    quint64 memberId() const;
    quint64 projectId() const;

    Member* member() const;
    Project* project() const;

public slots:
    void setGuid(const quint64 &guid);
    void setMemberId(const quint64 &memberId);
    void setProjectId(const quint64 &projectId);

    void setMember(Member* member);
    void setProject(Project* project);

signals:
    void guidChanged(const quint64 &guid);
    void memberIdChanged(const quint64 &memberId);
    void projectIdChanged(const quint64 &projectId);

    void memberChanged(Member* member);
    void projectChanged(Project* project);

private:
    quint64 m_guid;
    quint64 m_memberId;
    quint64 m_projectId;

    Member* m_member;
    Project* m_project;

    void clearMember();
    void clearProject();
};

#include "member.hpp"
#include "project.hpp"

#endif // MEMBERPROJECT_HPP
