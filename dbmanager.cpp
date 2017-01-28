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
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DbManager::openDB(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
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

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE users(id integer primary key, user text, password text);");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'users': one might already exist.";
        success = false;
    }

    return success;
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
