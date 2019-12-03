#include <QtConcurrent/QtConcurrent>

#include "memberdetailsviewmodel.hpp"
#include "databasemanager.hpp"


MemberDetailsViewModel::MemberDetailsViewModel(QObject *parent)
    : QObject (parent)
{
    m_isWorking = false;
    m_currentMember = nullptr;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);

    connect(this, &MemberDetailsViewModel::projectsReset, &m_projectModel, &ProjectModel::projectsReset);
}

MemberDetailsViewModel::~MemberDetailsViewModel()
{
    if(m_currentMember != nullptr)
    {
        m_currentMember->deleteLater();
    }
}

bool MemberDetailsViewModel::isWorking() const
{
    return m_isWorking;
}

Member* MemberDetailsViewModel::currentMember() const
{
    return m_currentMember;
}

QObject* MemberDetailsViewModel::projectModel()
{
    return dynamic_cast<QObject*>(&m_projectModel);
}

void MemberDetailsViewModel::readMember(const quint64 &guid)
{
    setIsWorking(true);
    MemberDetailsViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, guid]() {
        viewModel->m_memberDao.setDatabase(viewModel->m_appDatabase);
        if (viewModel->m_currentMember != nullptr)
        {
            Member *oldMember = viewModel->m_currentMember;
            oldMember->deleteLater();
            oldMember = nullptr;
            viewModel->m_currentMember = new Member();
        }
        XMatcher matcher;
        matcher.insert("guid", guid);
        viewModel->m_memberDao.findOneBy(viewModel->m_currentMember, matcher);
        viewModel->m_memberDao.resolveForeigns(viewModel->m_currentMember);
        viewModel->m_currentMember->moveToThread(viewModel->thread());
        emit viewModel->currentMemberChanged(viewModel->m_currentMember);
        emit viewModel->projectsReset(viewModel->m_currentMember->projects());
        viewModel->setIsWorking(false);
    });
}

void MemberDetailsViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
