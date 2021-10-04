#include <QStandardPaths>

#include "databasemanager.hpp"
#include "pathutils.hpp"
#include "member.hpp"
#include "project.hpp"
#include "memberproject.hpp"

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{    
    m_database = nullptr;
}

DatabaseManager::~DatabaseManager()
{
    if(m_database != nullptr) {
        if(m_database->isOpen()) {
            m_database->close();
        }

        m_database->deleteLater();
    }
}

void DatabaseManager::initialize()
{
    m_databaseFilePath = PathUtils::appicationDataPath() + PathUtils::SEPARATOR + DATABASE_FILE_NAME;
    PathUtils::makeParentPath(m_databaseFilePath);
    m_database = new XDatabase(m_databaseFilePath, DATABASE_CONNECTION_NAME, EMPTY_TEMPLATE);
    bool opened = m_database->open();
    if(opened) {
        QSqlError error;
        error = m_database->registerModel<Member>();
        if(error.isValid()) qWarning("%s", error.text().toLocal8Bit().data());
        error = m_database->registerModel<Project>();
        if(error.isValid()) qWarning("%s", error.text().toLocal8Bit().data());
        error = m_database->registerModel<MemberProject>();
        if(error.isValid()) qWarning("%s", error.text().toLocal8Bit().data());
    }
}
