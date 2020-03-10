#include <QtConcurrent/QtConcurrent>

#include "projectlistingviewmodel.hpp"
#include "databasemanager.hpp"


ProjectListingViewModel::ProjectListingViewModel(QObject *parent)
    : QObject(parent)
{
    m_isWorking = false;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);
    connect(this, &ProjectListingViewModel::projectsReset, &m_projectModel, &ProjectModel::projectsReset);
    connect(this, &ProjectListingViewModel::projectDeleted, &m_projectModel, &ProjectModel::deleteProject);
}

bool ProjectListingViewModel::isWorking() const
{
    return m_isWorking;
}

QObject* ProjectListingViewModel::projectModel()
{
    return dynamic_cast<QObject*>(&m_projectModel);
}

void ProjectListingViewModel::readProjects()
{
    setIsWorking(true);
    ProjectListingViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel]() {
        viewModel->m_projectDao.setDatabase(viewModel->m_appDatabase);
        QList<Project*> projects;
        viewModel->m_projectDao.readAll(projects);
        emit viewModel->projectsReset(projects);
        viewModel->setIsWorking(false);
    });
}

void ProjectListingViewModel::deleteProject(const quint64 &guid, const qint32 &index)
{
    setIsWorking(true);
    ProjectListingViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, guid, index]() {
        viewModel->m_projectDao.setDatabase(viewModel->m_appDatabase);
        QVariantMap map;
        map.insert("guid", guid);
        viewModel->m_projectDao.deleteBy(map);
        emit viewModel->projectDeleted(guid, index);
        viewModel->setIsWorking(false);
    });
}

void ProjectListingViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
