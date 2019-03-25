module academy.learnprogramming.db {
    exports academy.learnprogamming.db;
    requires java.sql;
    requires transitive academy.learnprogramming.common;
    requires sqlite.jdbc;
}