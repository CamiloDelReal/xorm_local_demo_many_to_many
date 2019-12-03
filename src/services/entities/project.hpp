#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <QObject>

#include "xtablemodel.hpp"


class Member;
class MemberProject;

class Project : public QObject, public XTableModel<Project>
{
    Q_OBJECT

    Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

    Q_PROPERTY(QList<Member*> members READ members WRITE setMembers NOTIFY membersChanged)

    X_TABLE_NAME("projects")
    X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
                   X_FIELD(name),
                   X_FIELD(description))

    X_FOREIGN_LISTS(X_INTERMEDIATED_FOREIGN_LIST(Member, guid, Project, guid, MemberProject, memberId, projectId, members))

public:
    explicit Project(QObject *parent = nullptr);
    Project(const QString &name, const QString &description, QObject *parent = nullptr);
    Project(const quint64 &guid, const QString &name, const QString &description, QObject *parent = nullptr);
    Project(const Project &other);

    ~Project();

    Project& operator=(const Project &other);

    quint64 guid() const;
    QString name() const;
    QString description() const;

    QList<Member*> members() const;

public slots:
    void setGuid(const quint64 &guid);
    void setName(const QString &name);
    void setDescription(const QString &description);

    void setMembers(QList<Member*> members);

signals:
    void guidChanged(const quint64 &guid);
    void nameChanged(const QString &name);
    void descriptionChanged(const QString &description);

    void membersChanged(QList<Member*> members);

private:
    quint64 m_guid;
    QString m_name;
    QString m_description;

    QList<Member*> m_members;

    void clearMembers();
};

#include "member.hpp"
#include "memberproject.hpp"

#endif // PROJECT_HPP

