#ifndef TIGREFRAMEWORK_INDEXCONTROLLER_H
#define TIGREFRAMEWORK_INDEXCONTROLLER_H

#include <TigreFramework/SimpleRouter/Controller.h>
#include <TigreFramework/Database/DataObject.h>

class IndexController : public Controller {

    Controller(IndexController);

    public:
        Response index(){
            //DataObject conn("pgsql:host=172.18.0.2 port=5432 dbname=postgres", "postgres", "1234");
            DataObject conn("sqlite:sqlite_database.sqlite");

            //auto result = conn.prepare("select * from users;");
            //result->execute();

            //auto result = conn.prepare("select * from users where email = :email;");
            //result->execute(std::map<string, Value>({{":email", "jhon@due.com"}}));

            //auto result = conn.prepare("select * from users where email = ? or password = ?;");
            //result->execute(std::vector<Value>({"jhon@due.com", "1234"}));

            //auto result = conn.prepare("select * from users where email = ? and password = ?;");
            //result->execute(std::vector<Value>({"jhon@due.com", "5555"}));

            int res = 0;

            //int res = conn.exec(R"(CREATE TABLE IF NOT EXISTS `users` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `name` TEXT, `email` TEXT, `password` TEXT );)");
            //int res = conn.exec(R"(CREATE TABLE IF NOT EXISTS "users" ( "id" SERIAL PRIMARY KEY, "name" character varying, "email" character varying, "password" character varying );)");
            //int res = conn.exec(R"(insert into users (name, email, password) values ("a", "a", "a");)");
            //int res = conn.exec(R"(delete from users where name = "a";)");

            //auto result = conn.prepare("insert into users (name, email, password) values (\"a\", \"a\", \"a\");");
            //result->execute();
            //auto res = result->fetchAll();

            std::string name = "Jhon Due";

            conn.beginTransaction();

            auto a = conn.prepare("insert into users (name, email, password) values (:name, :email, :password);");
            a->bindValue(":name", &name);
            a->bindValue(":email", "jhon@due.com");
            a->bindValue(":password", "1234");

            name = "Richard";

            a->execute();

            //auto a = conn.prepare("insert into users (name, email, password) values (?, ?, ?);");
            //a->execute({"a", "a", "a"});

            a->fetchAll();
            //conn.exec("insert into users (name, email, password) values ('b', 'b', 'b');");
            //conn.exec("insert into users (name, email, password) values ('c', 'c', 'c');");
            //conn.exec("delete from users where LENGTH(name) = 1 and name != 'a';");
            //conn.commit();
            //conn.rollBack();

            auto result = conn.prepare("select * from users;");
            result->execute();

            return Response(nlohmann::json({
                res,
                result->rowCount(), // Not work With SQLite
                result->fetch(),
                result->fetchAll(),
            }));
        }

};

#endif //TIGREFRAMEWORK_INDEXCONTROLLER_H
