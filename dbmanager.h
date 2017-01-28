#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

/**
 * \class DbManager
 *
 * \brief SQL Database Manager class
 *
 * DbManager sets up the connection with SQL database
 * and performs some basics queries. The class requires
 * existing SQL database. You can create it with sqlite:
 * 1. $ sqlite3 users.db
 * 2. sqilte> CREATE TABLE users(ids integer primary key, name text);
 * 3. sqlite> .quit
 */
class DbManager
{
public:
    DbManager();
    DbManager(const QString& path);
    ~DbManager();
    int openDB(const QString &path);
    bool isOpen() const;
    bool createTable();
    bool addUser(const QString& user, const QString& password);
    bool removeUser(const QString& name);
    bool userExists(const QString& name) const;
    void printAllUsers() const;
    bool removeAllUsers();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
