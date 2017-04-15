#include <dbmanager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QFile>

DbManager::DbManager()
{

}

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    dbpath = path;

    if (!m_db.open())
        qDebug() << Q_FUNC_INFO << "ERROR: connection with database " + path + " fail.";
    else
        qDebug() << Q_FUNC_INFO << "Connection with database " + path + " successful.";
}

DbManager::openDB(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
    dbpath = path;

    if (!m_db.open())
        qDebug() << Q_FUNC_INFO << "ERROR: connection with database " + path + " fail.";
    else
        qDebug() << Q_FUNC_INFO << "Connection with database " + path + " successful.";

    return m_db.isOpen();
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
        m_db.close();
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTableUsers()
{
    bool status = true;
    QSqlQuery query;
    QString queryText;
    queryText.append("CREATE TABLE " + TABLE_USERS + " (");
    queryText.append("id INT AUTO_INCREMENT, ");
    queryText.append(FIELD_USER + " varchar (255)" + ", ");
    queryText.append(FIELD_USER_PASSWORD + " varchar (255)");
    queryText.append(");");

    query.prepare(queryText);

    if (!query.exec())
    {
        qDebug() << Q_FUNC_INFO << "Couldn't create the table "+ TABLE_USERS + ", may already exist." << query.lastError();
        status = false;
    }
    query.clear();
    return status;
}

bool DbManager::createTableGlobals()
{
    bool statusQueryCreate = true;
    bool statusQueryInsert = true;
    QSqlQuery query;
    QString queryText;
    queryText.append("CREATE TABLE " + TABLE_GLOBALS + " (");
    queryText.append("id INT AUTO_INCREMENT NOT NULL, ");
    queryText.append(FIELD_DB_VERSION + " varchar (255)");
    queryText.append(");");

    query.prepare(queryText);

    if (!query.exec())
    {
        qDebug() << Q_FUNC_INFO << "Couldn't create the table "+ TABLE_GLOBALS + ", may already exist." << query.lastError();
        statusQueryCreate = false;
    }

    queryText.clear();
    queryText.append("INSERT INTO " + TABLE_GLOBALS + " ");
    queryText.append("( id ," + FIELD_DB_VERSION + ")");
    queryText.append(" VALUES ");
    queryText.append("( 1," + DB_VERSION + ")");
    queryText.append(";");

    query.prepare(queryText);

    if (!query.exec())
    {
        qDebug() << Q_FUNC_INFO << "Couldn't create version tuple in "+ TABLE_GLOBALS + ", may already exist." << query.lastError();
        statusQueryInsert = false;
    }
    query.clear();
    return statusQueryCreate & statusQueryInsert;
}

bool DbManager::chekDbVersion() const
{
    bool statusQuery = true;
    bool checkStatus = true;
    QSqlQuery query;
    QString queryText;
    QString version;
    queryText.append("SELECT " + FIELD_DB_VERSION + " FROM " + TABLE_GLOBALS);
    queryText.append(";");
    query.prepare(queryText);

    if (!query.exec())
    {
        qDebug() << Q_FUNC_INFO << "Couldn't find " << FIELD_DB_VERSION << "in "+ TABLE_GLOBALS << query.lastError();
        statusQuery = false;
    }

    int idversion = query.record().indexOf(FIELD_DB_VERSION);

    while (query.next())
        version = query.value(idversion).toString();

    if (version != DB_VERSION)
    {
        qDebug() << Q_FUNC_INFO << "Db version check failed (version: " << version << ", required version: " << DB_VERSION << ")";
        checkStatus = false;
    }
    if (checkStatus)
        qDebug() << Q_FUNC_INFO << "Db version check passed (version: " << version << ", required version: " << DB_VERSION << ")";

    query.clear();
    return statusQuery & checkStatus;
}


bool DbManager::createTables()
{
    bool users_created = true;
    bool globals_created = true;
    bool vesionCheckPassed = true;
    bool fileDeleted = true;

    vesionCheckPassed = chekDbVersion();

    if (!vesionCheckPassed)
    {
        m_db.close();
        if (QFile::remove(this->dbpath))
            qDebug() << Q_FUNC_INFO << "DB " << this->dbpath << " deleted";
        else
        {
            qDebug() << Q_FUNC_INFO << "Error deleting DB " << this->dbpath;
            fileDeleted = false;
        }
        openDB(dbpath);
        users_created = createTableUsers();
        globals_created = createTableGlobals();

    }

    return users_created & globals_created & vesionCheckPassed & fileDeleted;
}

bool DbManager::addUser(const QString& user, const QString& password)
{
    if (!user.isEmpty() && !password.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO users (user, password) VALUES (:user, :password)");
        queryAdd.bindValue(":user", user);
        queryAdd.bindValue(":password", password);

        if(queryAdd.exec())
        {
            return true;
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "add user failed: " << queryAdd.lastError();
            return false;
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "add user failed: name cannot be empty";
        return false;
    }
    return true;
}

bool DbManager::removeUser(const QString& name)
{
    bool queryStatus = true;
    QSqlQuery queryDelete;

    if (userExists(name))
    {
        queryDelete.prepare("DELETE FROM users WHERE name = (:name)");
        queryDelete.bindValue(":name", name);
        queryStatus = queryDelete.exec();

        if(!queryStatus)
        {
            qDebug() << Q_FUNC_INFO << "remove user failed: " << queryDelete.lastError();
            queryStatus = false;
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "remove user failed: person doesnt exist";
        queryStatus = false;
    }
    queryDelete.clear();
    return queryStatus;
}

void DbManager::printAllUsers() const
{
    qDebug() << Q_FUNC_INFO << "Users in db:";
    QSqlQuery query("SELECT * FROM users");
    int idName = query.record().indexOf("user");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << Q_FUNC_INFO << "===" << name;
    }
}

bool DbManager::userExists(const QString& name) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM users WHERE name = (:name)");
    checkQuery.bindValue(":name", name);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "user exists failed: " << checkQuery.lastError();
    }
    return exists;
}

bool DbManager::removeAllUsers()
{
    QSqlQuery query;
    query.prepare("DELETE FROM users");
    if (!query.exec())
    {
        qDebug() << Q_FUNC_INFO << "remove all users failed: " << query.lastError();
        return false;
    }
    return true;
}
