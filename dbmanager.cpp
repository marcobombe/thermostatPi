#include <dbmanager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager()
{

}

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
        qDebug() << Q_FUNC_INFO << "ERROR: connection with database " + path + " fail.";
    else
        qDebug() << Q_FUNC_INFO << "Connection with database " + path + " successful.";
}

DbManager::openDB(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
        qDebug() << Q_FUNC_INFO << "ERROR: connection with database " + path + " fail.";
    else
        qDebug() << Q_FUNC_INFO << "Connection with database " + path + " successful.";

    return m_db.isOpen();
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTableUsers()
{
    bool success = false;

    QSqlQuery query;
    QString queryText;
    queryText.append("CREATE TABLE " + TABLE_USERS + " (");
    queryText.append("id INT AUTO_INCREMENT, ");
    queryText.append(FIELD_USER + " varchar (255)" + ", ");
    queryText.append(FIELD_USER_PASSWORD + " varchar (255)");
    queryText.append(");");
    qDebug() << Q_FUNC_INFO << queryText;

    query.prepare(queryText);

    if (!query.exec())
    {
        qDebug() << Q_FUNC_INFO << "Couldn't create the table "+ TABLE_USERS + ", may already exist." << query.lastError();
        success = false;
    }

    return success;
}

bool DbManager::createTableGlobals()
{
    bool success = false;

    QSqlQuery query;
    QString queryText;
    queryText.append("CREATE TABLE " + TABLE_GLOBALS + " (");
    queryText.append("id INT AUTO_INCREMENT, ");
    queryText.append(FIELD_DB_VERSION + " varchar (255)");
    queryText.append(");");
    qDebug() << Q_FUNC_INFO << queryText;

    query.prepare(queryText);

    if (!query.exec())
    {
        qDebug() << Q_FUNC_INFO << "Couldn't create the table "+ TABLE_GLOBALS + ", may already exist." << query.lastError();
        success = false;
    }

    queryText.clear();
    queryText.append("INSERT INTO " + TABLE_GLOBALS + " ");
    queryText.append("(" + FIELD_DB_VERSION + ")");
    queryText.append(" VALUES ");
    queryText.append("('" + DB_VERSION + "')");
    queryText.append(";");
    qDebug() << Q_FUNC_INFO << queryText;

    query.prepare(queryText);

    if (!query.exec())
    {
        qDebug() << Q_FUNC_INFO << "Couldn't create version tuple in "+ TABLE_GLOBALS + ", may already exist." << query.lastError();
        success = false;
    }

    return success;
}


bool DbManager::createTables()
{
    bool users_created = false;
    bool globals_created = false;

    users_created = createTableUsers();
    globals_created = createTableGlobals();

    return users_created && globals_created;
}

bool DbManager::addUser(const QString& user, const QString& password)
{
    bool success = false;

    if (!user.isEmpty() && !password.isEmpty())
    {
        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO users (user, password) VALUES (:user, :password)");
        queryAdd.bindValue(":user", user);
        queryAdd.bindValue(":password", password);

        if(queryAdd.exec())
        {
            success = true;
        }
        else
        {
            qDebug() << "add user failed: " << queryAdd.lastError();
        }
    }
    else
    {
        qDebug() << "add user failed: name cannot be empty";
    }

    return success;
}

bool DbManager::removeUser(const QString& name)
{
    bool success = false;

    if (userExists(name))
    {
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM users WHERE name = (:name)");
        queryDelete.bindValue(":name", name);
        success = queryDelete.exec();

        if(!success)
        {
            qDebug() << "remove user failed: " << queryDelete.lastError();
        }
    }
    else
    {
        qDebug() << "remove user failed: person doesnt exist";
    }

    return success;
}

void DbManager::printAllUsers() const
{
    qDebug() << "Users in db:";
    QSqlQuery query("SELECT * FROM users");
    int idName = query.record().indexOf("user");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
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
        qDebug() << "user exists failed: " << checkQuery.lastError();
    }

    return exists;
}

bool DbManager::removeAllUsers()
{
    bool success = false;

    QSqlQuery removeQuery;
    removeQuery.prepare("DELETE FROM users");

    if (removeQuery.exec())
    {
        success = true;
    }
    else
    {
        qDebug() << "remove all users failed: " << removeQuery.lastError();
    }

    return success;
}
