#include <QtConcurrent/QtConcurrent>

#include "memberlistingviewmodel.hpp"
#include "databasemanager.hpp"


MemberListingViewModel::MemberListingViewModel(QObject *parent)
    : QObject(parent)
{
    m_isWorking = false;
    m_appDatabase = QSqlDatabase::database(DATABASE_CONNECTION_NAME);
    connect(this, &MemberListingViewModel::membersReset, &m_memberModel, &MemberModel::membersReset);
    connect(this, &MemberListingViewModel::memberDeleted, &m_memberModel, &MemberModel::deleteMember);
}

bool MemberListingViewModel::isWorking() const
{
    return m_isWorking;
}

QObject* MemberListingViewModel::memberModel()
{
    return dynamic_cast<QObject*>(&m_memberModel);
}

void MemberListingViewModel::readMembers()
{
    setIsWorking(true);
    MemberListingViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel]() {
        viewModel->m_memberDao.setDatabase(viewModel->m_appDatabase);
        QList<Member*> members;
        viewModel->m_memberDao.readAll(members);
        emit viewModel->membersReset(members);
        viewModel->setIsWorking(false);
    });
}

void MemberListingViewModel::deleteMember(const quint64 &guid, const qint32 &index)
{
    setIsWorking(true);
    MemberListingViewModel *viewModel = this;
    QFuture<void> future = QtConcurrent::run([viewModel, guid, index]() {
        viewModel->m_memberDao.setDatabase(viewModel->m_appDatabase);
        QVariantMap map;
        map.insert("guid", guid);
        viewModel->m_memberDao.deleteBy(map);
        emit viewModel->memberDeleted(guid, index);
        viewModel->setIsWorking(false);
    });
}

void MemberListingViewModel::setIsWorking(const bool &isWorking)
{
    if(m_isWorking != isWorking)
    {
        m_isWorking = isWorking;
        emit isWorkingChanged(m_isWorking);
    }
}
