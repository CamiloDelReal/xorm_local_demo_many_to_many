# XOrm persistance with One to One relationship
Many to Many relationship using XOrm library

### Features
- Members
  * CRUD operations
- Projects
  * CRUD operations
- MVVM architecture

### Entity relationship diagram
<p float="left">
<img src="https://github.com/CamiloDelReal/xorm_local_demo_one_to_one/blob/develop/design/exported_diagrams/persistence.jpg" width="80%" height="80%" />
</p>

### Entities definition

	class Member : public QObject, public XTableModel<Member>
	{
		Q_OBJECT

		Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString job READ job WRITE setJob NOTIFY jobChanged)

		Q_PROPERTY(QList<Project*> projects READ projects WRITE setProjects NOTIFY projectsChanged)

		X_TABLE_NAME("members")
		X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
					   X_FIELD(name),
					   X_FIELD(job))
		X_FOREIGN_LISTS(X_INTERMEDIATED_FOREIGN_LIST(Project, guid, Member, guid, MemberProject, projectId, memberId, projects))

	public:
		explicit Member(QObject *parent = nullptr);
		Member(const quint64 &guid, const QString &name, const QString &job, QObject *parent = nullptr);
		Member(const QString &name, const QString &job, QObject *parent = nullptr);
		Member(const Member &other);

		~Member();

		Member& operator=(const Member &other);

		quint64 guid() const;
		QString name() const;
		QString job() const;

		QList<Project*> projects() const;

	public slots:
		void setGuid(const quint64 &guid);
		void setName(const QString &name);
		void setJob(const QString &job);

		void setProjects(QList<Project*> projects);

	signals:
		void guidChanged(const quint64 &guid);
		void nameChanged(const QString &name);
		void jobChanged(const QString &job);

		void projectsChanged(QList<Project*> projects);

	private:
		quint64 m_guid;
		QString m_name;
		QString m_job;
		QList<Project*> m_projects;

		void clearProjects();
	};
	
	class Project : public QObject, public XTableModel<Project>
	{
		Q_OBJECT

		Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

		Q_PROPERTY(QList<Member*> members READ members WRITE setMembers NOTIFY membersChanged)

		X_TABLE_NAME("projects")
		X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
					   X_FIELD(name),
					   X_FIELD(description))

		X_FOREIGN_LISTS(X_INTERMEDIATED_FOREIGN_LIST(Member, guid, Project, guid, MemberProject, memberId, projectId, members))

	public:
		explicit Project(QObject *parent = nullptr);
		Project(const QString &name, const QString &description, QObject *parent = nullptr);
		Project(const quint64 &guid, const QString &name, const QString &description, QObject *parent = nullptr);
		Project(const Project &other);

		~Project();

		Project& operator=(const Project &other);

		quint64 guid() const;
		QString name() const;
		QString description() const;

		QList<Member*> members() const;

	public slots:
		void setGuid(const quint64 &guid);
		void setName(const QString &name);
		void setDescription(const QString &description);

		void setMembers(QList<Member*> members);

	signals:
		void guidChanged(const quint64 &guid);
		void nameChanged(const QString &name);
		void descriptionChanged(const QString &description);

		void membersChanged(QList<Member*> members);

	private:
		quint64 m_guid;
		QString m_name;
		QString m_description;

		QList<Member*> m_members;

		void clearMembers();
	};
	
	class MemberProject : public QObject, public XTableModel<MemberProject>
	{
		Q_OBJECT
		Q_PROPERTY(quint64 guid READ guid WRITE setGuid NOTIFY guidChanged)
		Q_PROPERTY(quint64 memberId READ memberId WRITE setMemberId NOTIFY memberIdChanged)
		Q_PROPERTY(quint64 projectId READ projectId WRITE setProjectId NOTIFY projectIdChanged)

		Q_PROPERTY(Member* member READ member WRITE setMember NOTIFY memberChanged)
		Q_PROPERTY(Project* project READ project WRITE setProject NOTIFY projectChanged)

		X_TABLE_NAME("members_projects")
		X_TABLE_FIELDS(X_FIELD(guid, X_PRIMARY_KEY),
					   X_FIELD(memberId, "member_id", X_FOREIGN_KEY(Member, X_CASCADE, X_CASCADE)),
					   X_FIELD(projectId, "project_id", X_FOREIGN_KEY(Project, X_CASCADE, X_CASCADE)))

	public:
		explicit MemberProject(QObject *parent = nullptr);
		MemberProject(const quint64 &memberId, const quint64 &projectId, QObject *parent = nullptr);
		MemberProject(const quint64 &guid, const quint64 &memberId, const quint64 &projectId, QObject *parent = nullptr);
		MemberProject(const MemberProject &other);

		~MemberProject();

		MemberProject& operator=(const MemberProject &other);

		quint64 guid() const;
		quint64 memberId() const;
		quint64 projectId() const;

		Member* member() const;
		Project* project() const;

	public slots:
		void setGuid(const quint64 &guid);
		void setMemberId(const quint64 &memberId);
		void setProjectId(const quint64 &projectId);

		void setMember(Member* member);
		void setProject(Project* project);

	signals:
		void guidChanged(const quint64 &guid);
		void memberIdChanged(const quint64 &memberId);
		void projectIdChanged(const quint64 &projectId);

		void memberChanged(Member* member);
		void projectChanged(Project* project);

	private:
		quint64 m_guid;
		quint64 m_memberId;
		quint64 m_projectId;

		Member* m_member;
		Project* m_project;

		void clearMember();
		void clearProject();
	};
	
### Screenshots
<p float="left">
<img src="https://github.com/CamiloDelReal/xorm_local_demo_many_to_many/blob/develop/screenshots/sshot-1.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_many_to_many/blob/develop/screenshots/sshot-2.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_many_to_many/blob/develop/screenshots/sshot-3.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_many_to_many/blob/develop/screenshots/sshot-4.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_many_to_many/blob/develop/screenshots/sshot-5.png" width="30%" height="30%" />
<img src="https://github.com/CamiloDelReal/xorm_local_demo_many_to_many/blob/develop/screenshots/sshot-6.png" width="30%" height="30%" />
</p>