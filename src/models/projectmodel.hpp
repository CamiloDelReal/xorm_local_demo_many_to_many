#ifndef PROJECTMODEL_HPP
#define PROJECTMODEL_HPP

#include <QObject>
#include <QAbstractListModel>

#include "project.hpp"

class ProjectModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(quint32 count READ rowCount NOTIFY countChanged)

public:
    enum ProjectModelRoles
    {
        GuidRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole
    };

    explicit ProjectModel(QObject *parent = nullptr);
    ~ProjectModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QList<Project*> projects();
    QList<Project*> projectsByIndexes(QList<qint32> indexes);

public slots:
    void projectsReset(const QList<Project*> projects);
    void insertProject(Project *project);
    void deleteProject(const quint64 &guid, const qint32 &index);

signals:
    void countChanged(qint32 count);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Project*> m_projects;

    void clearData();
};

#endif // PROJECTMODEL_HPP
