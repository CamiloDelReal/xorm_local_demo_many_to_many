#include <QtConcurrent/QtConcurrent>

#include "membereditionviewmodel.hpp"
#include "databasemanager.hpp"

MemberEditionViewModel::MemberEditionViewModel(QObject *parent)
    : QObject(parent)
{
    m_isWorking = false;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);
    connect(this, &MemberEditionViewModel::projectsReset, &m_projectModel, &ProjectModel::projectsReset);
}

bool MemberEditionViewModel::isWorking() const
{
    return m_isWorking;
}

QObject *MemberEditionViewModel::projectModel()
{
    return dynamic_cast<QObject*>(&m_projectModel);
}

void MemberEditionViewModel::readProjects()
{
    setIsWorking(true);
    MemberEditionViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel]()
    {
        QList<Project*> projects;
        viewModel->m_projectDao.setDatabase(viewModel->m_appDatabase);
        viewModel->m_projectDao.readAll(projects);
        emit viewModel->projectsReset(projects);
        viewModel->setIsWorking(false);
    });
}

void MemberEditionViewModel::createMember(const QString &name, const QString &job, QList<int> selectedProjects)
{
    setIsWorking(true);
    MemberEditionViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, name, job, selectedProjects]()
    {
        Member *member = new Member(name, job);
        viewModel->m_memberDao.setDatabase(viewModel->m_appDatabase);
        viewModel->m_memberDao.createOne(member);
        viewModel->m_memberProjectDao.setDatabase(viewModel->m_appDatabase);
        QList<Project*> projects = viewModel->m_projectModel.projectsByIndexes(selectedProjects);
        foreach (Project* project, projects)
        {
            MemberProject* memberProject = new MemberProject(member->guid(), project->guid());
            viewModel->m_memberProjectDao.createOne(memberProject);
            memberProject->deleteLater();
            memberProject = nullptr;
        }
        emit viewModel->memberCreated(member);
        viewModel->setIsWorking(false);
    });
}

void MemberEditionViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
