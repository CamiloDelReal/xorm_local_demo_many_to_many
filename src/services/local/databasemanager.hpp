#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QObject>

#include "xdatabase.hpp"

static const QString DATABASE_FILE_NAME = QStringLiteral("database.db");
static const QString DATABASE_CONNECTION_NAME = QStringLiteral("XOrmDemoManyToMany");

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    void initialize();

private:
    QString m_databaseFilePath;
    XDatabase *m_database;
};

#endif // DATABASEMANAGER_HPP
