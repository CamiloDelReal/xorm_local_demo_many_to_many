#include "projectmodel.hpp"

ProjectModel::ProjectModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

ProjectModel::~ProjectModel()
{
    clearData();
}

int ProjectModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_projects.size();
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const
{
    QVariant wrapper;

    if(index.row() >= 0 && index.row() < m_projects.size())
    {
        const Project * const item = m_projects.at(index.row());

        switch(role)
        {
        case GuidRole:
            wrapper.setValue(item->guid());
            break;
        case NameRole:
            wrapper.setValue(item->name());
            break;
        case DescriptionRole:
            wrapper.setValue(item->description());
            break;
        }
    }

    return wrapper;
}

QList<Project*> ProjectModel::projects()
{
    return m_projects;
}

QList<Project*> ProjectModel::projectsByIndexes(QList<qint32> indexes)
{
    QList<Project*> projects;

    foreach (qint32 index, indexes)
    {
        projects.append(m_projects.at(index));
    }

    return projects;
}

void ProjectModel::projectsReset(const QList<Project*> projects)
{
    beginResetModel();
    clearData();
    m_projects.clear();
    m_projects.append(projects);
    endResetModel();
    emit countChanged(m_projects.size());
}

void ProjectModel::insertProject(Project* project)
{
    beginInsertRows(QModelIndex(), m_projects.size(), m_projects.size());
    m_projects.append(project);
    endInsertRows();
    emit countChanged(m_projects.size());
}

void ProjectModel::deleteProject(const quint64 &guid, const qint32 &index)
{
    Q_UNUSED(guid)
    beginRemoveRows(QModelIndex(), index, index);
    m_projects.removeAt(index);
    endRemoveRows();
    emit countChanged(m_projects.size());
}

QHash<int, QByteArray> ProjectModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[GuidRole] = QByteArrayLiteral("guid");
    roles[NameRole] = QByteArrayLiteral("name");
    roles[DescriptionRole] = QByteArrayLiteral("description");
    return roles;
}

void ProjectModel::clearData()
{
    if(!m_projects.isEmpty())
    {
        for (int i = 0; i < m_projects.size(); ++i) {
            Project* project;
            project = m_projects.at(i);
            project->deleteLater();
            project = nullptr;
        }
    }
}
