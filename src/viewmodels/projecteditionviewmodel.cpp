#include <QtConcurrent/QtConcurrent>

#include "projecteditionviewmodel.hpp"
#include "databasemanager.hpp"

ProjectEditionViewModel::ProjectEditionViewModel(QObject *parent)
    : QObject(parent)
{
    m_isWorking = false;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);

    connect(this, &ProjectEditionViewModel::membersReset, &m_memberModel, &MemberModel::membersReset);
}

bool ProjectEditionViewModel::isWorking() const
{
    return m_isWorking;
}

QObject* ProjectEditionViewModel::memberModel()
{
    return dynamic_cast<QObject*>(&m_memberModel);
}

void ProjectEditionViewModel::readMembers()
{
    setIsWorking(true);
    ProjectEditionViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel]()
    {
        QList<Member*> members;
        viewModel->m_memberDao.setDatabase(viewModel->m_appDatabase);
        viewModel->m_memberDao.readAll(members);
        emit viewModel->membersReset(members);
        viewModel->setIsWorking(false);
    });
}

void ProjectEditionViewModel::createProject(const QString &name, const QString &description, const QList<qint32> &indexes)
{
    setIsWorking(true);
    ProjectEditionViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, name, description, indexes]()
    {
        Project *project = new Project(name, description);
        viewModel->m_projectDao.setDatabase(viewModel->m_appDatabase);
        viewModel->m_projectDao.createOne(project);
        QList<Member*> members = viewModel->m_memberModel.membersByIndexes(indexes);
        viewModel->m_memberProjectDao.setDatabase(viewModel->m_appDatabase);
        foreach(Member* member, members)
        {
            MemberProject* memberProject = new MemberProject(member->guid(), project->guid());
            viewModel->m_memberProjectDao.createOne(memberProject);
            memberProject->deleteLater();
            memberProject = nullptr;
        }
        emit viewModel->projectCreated(project);
        viewModel->setIsWorking(false);
    });
}

void ProjectEditionViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
