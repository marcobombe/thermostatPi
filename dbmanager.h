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

static const QString DB_VERSION = "0.0";

static const QString TABLE_USERS = "Users";

static const QString FIELD_USER = "User";
static const QString FIELD_ADMIN = "Admin";
static const QString FIELD_USER_PASSWORD = "UserPassword";
static const QString FIELD_ADMIN_PASSWORD = "AdminPassword";

static const QString DEFAULT_USER = "User";
static const QString DEFAULT_ADMIN = "Admin";
static const QString DEFAULT_USER_PASSWORD = "12345678";
static const QString DEFAULT_ADMIN_PASSWORD = "12345678";

static const QString TABLE_GLOBALS = "Globals";

static const QString FIELD_DB_VERSION = "db_version";

class DbManager
{
public:
    DbManager();
    DbManager(const QString& path);
    ~DbManager();
    int openDB(const QString &path);
    bool isOpen() const;
    bool createTables();
    bool addUser(const QString& user, const QString& password);
    bool removeUser(const QString& name);
    bool userExists(const QString& name) const;
    void printAllUsers() const;
    bool removeAllUsers();

private:
    QSqlDatabase m_db;
    bool createTableUsers();
    bool createTableGlobals();
};

#endif // DBMANAGER_H
