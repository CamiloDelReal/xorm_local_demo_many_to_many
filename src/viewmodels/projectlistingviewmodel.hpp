#ifndef PROJECTLISTINGVIEWMODEL_HPP
#define PROJECTLISTINGVIEWMODEL_HPP

#include "xdao.hpp"
#include "projectmodel.hpp"


class ProjectListingViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(QObject* projectModel READ projectModel NOTIFY projectModelChanged)

public:
    explicit ProjectListingViewModel(QObject *parent = nullptr);

    bool isWorking() const;
    QObject* projectModel();

    Q_INVOKABLE void readProjects();
    Q_INVOKABLE void deleteProject(const quint64 &guid, const qint32 &index);

signals:
    void isWorkingChanged(const bool &isWorking);
    void projectModelChanged(QObject* projectModel);

    void projectsReset(const QList<Project*> projects);
    void projectDeleted(const quint64 &guid, const qint32 &index);

private:
    bool m_isWorking;
    ProjectModel m_projectModel;

    QSqlDatabase m_appDatabase;
    XDao<Project> m_projectDao;

private slots:
    void setIsWorking(const bool &isWorking);
};

#endif // PROJECTLISTINGVIEWMODEL_HPP
