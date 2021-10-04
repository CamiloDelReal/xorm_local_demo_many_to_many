#include <QtConcurrent/QtConcurrent>

#include "projectdetailsviewmodel.hpp"
#include "databasemanager.hpp"


ProjectDetailsViewModel::ProjectDetailsViewModel(QObject *parent)
    : QObject (parent)
{
    m_isWorking = false;
    m_currentProject = nullptr;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);

    connect(this, &ProjectDetailsViewModel::membersReset, &m_memberModel, &MemberModel::membersReset);
}

ProjectDetailsViewModel::~ProjectDetailsViewModel()
{
    if(m_currentProject != nullptr)
    {
        m_currentProject->deleteLater();
    }
}

bool ProjectDetailsViewModel::isWorking() const
{
    return m_isWorking;
}

Project* ProjectDetailsViewModel::currentProject() const
{
    return m_currentProject;
}

QObject* ProjectDetailsViewModel::memberModel()
{
    return dynamic_cast<QObject*>(&m_memberModel);
}

void ProjectDetailsViewModel::readProject(const quint64 &guid)
{
    setIsWorking(true);
    ProjectDetailsViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, guid]() {
        viewModel->m_projectDao.setDatabase(viewModel->m_appDatabase);
        if (viewModel->m_currentProject != nullptr)
        {
            Project *oldProject = viewModel->m_currentProject;
            oldProject->deleteLater();
            oldProject = nullptr;
            viewModel->m_currentProject = new Project();
        }
        XMatcher matcher;
        matcher.insert("guid", guid);
        viewModel->m_projectDao.findOneBy(viewModel->m_currentProject, matcher);
        viewModel->m_projectDao.resolveForeigns(viewModel->m_currentProject);
        viewModel->m_currentProject->moveToThread(viewModel->thread());
        emit viewModel->currentProjectChanged(viewModel->m_currentProject);
        emit viewModel->membersReset(viewModel->m_currentProject->members());
        viewModel->setIsWorking(false);
    });
}

void ProjectDetailsViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
