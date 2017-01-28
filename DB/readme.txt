$ sqlite3 users.db
sqlite> CREATE TABLE users(id integer primary key, user text, password text);
sqlite> .quit


INSERT INTO users values (1, pino, psw1);

INSERT INTO users (user, password) VALUES ('pino','psw');
INSERT INTO users (user, password) VALUES ('car','ppp');

SELECT * FROM users