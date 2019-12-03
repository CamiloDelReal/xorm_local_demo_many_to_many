#include <QtQml>
#include <QStandardPaths>

#include "applicationmanager.hpp"
#include "pathutils.hpp"
#include "xdatabase.hpp"

#include "memberdetailsviewmodel.hpp"
#include "membereditionviewmodel.hpp"
#include "memberlistingviewmodel.hpp"
#include "projectdetailsviewmodel.hpp"
#include "projecteditionviewmodel.hpp"
#include "projectlistingviewmodel.hpp"


ApplicationManager::ApplicationManager(QObject *parent)
    : MobileManager(parent)
{
}

void ApplicationManager::addContextProperty(QQmlEngine *engine, QQmlContext *context)
{
    m_engine = engine;

    //Register singletons
    qmlRegisterSingletonType(QUrl(QLatin1String("qrc:/qml/XMaterialControls.qml")), "XApps.XMaterialControls", 1, 0, "XMaterialControls");

    //Link C++ objects with QML
    context->setContextProperty("ApplicationManagerObj", this);
    context->setContextProperty("ApplicationSettingsObj", &m_applicationSettings);

    //Register data types
    qRegisterMetaType<Member>("Member");
    qRegisterMetaType<QList<Member*>>("QList<Member*>");
    qmlRegisterType<MemberDetailsViewModel>("XApps.XOrmDemoManyToMany", 1, 0, "MemberDetailsViewModel");
    qmlRegisterType<MemberEditionViewModel>("XApps.XOrmDemoManyToMany", 1, 0, "MemberEditionViewModel");
    qmlRegisterType<MemberListingViewModel>("XApps.XOrmDemoManyToMany", 1, 0, "MemberListingViewModel");
    qRegisterMetaType<Member>("Project");
    qRegisterMetaType<QList<Member*>>("QList<Project*>");
    qmlRegisterType<ProjectDetailsViewModel>("XApps.XOrmDemoManyToMany", 1, 0, "ProjectDetailsViewModel");
    qmlRegisterType<ProjectEditionViewModel>("XApps.XOrmDemoManyToMany", 1, 0, "ProjectEditionViewModel");
    qmlRegisterType<ProjectListingViewModel>("XApps.XOrmDemoManyToMany", 1, 0, "ProjectListingViewModel");
}

void ApplicationManager::initialize()
{
    m_databaseManager.initialize();
}

void ApplicationManager::onAboutToQuit()
{
    m_applicationSettings.saveSettings();
}

void ApplicationManager::onApplicationStateChanged(Qt::ApplicationState applicationState)
{
    if(applicationState == Qt::ApplicationState::ApplicationSuspended)
        onAboutToQuit();
}
