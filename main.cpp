#include <iostream>

#include <crow.h>
#include <occi.h>

int
main(const int argc, const char** argv)
{
  if (argc <= 3) {
    std::cout << "usage: wsa <username> <password> <connection>\n";
    return 1;
  }

  crow::SimpleApp app;

  CROW_ROUTE(app, "/v1/costumers/<int>")
  ([&argv](const int code) {
    using namespace oracle::occi;

    Environment* env = Environment::createEnvironment(Environment::DEFAULT);
    Connection* conn = env->createConnection(argv[1], argv[2], argv[3]);

    const char* sql{ "SELECT cliente, endercob, bairrocob, municcob, cgcent, "
                     "numeroent FROM PCCLIENT WHERE CODCLI = :v1" };

    Statement* sttm = conn->createStatement(sql);
    sttm->setNumber(1, code);

    ResultSet* rset{ sttm->executeQuery() };
    crow::json::wvalue json_res;

    while (rset->next()) {
      json_res["name"] = rset->getString(1);
      json_res["address"] = rset->getString(2);
      json_res["neighborhood"] = rset->getString(3);
      json_res["city"] = rset->getString(4);
      json_res["tax_id"] = rset->getString(5);
      json_res["address_number"] = rset->getString(6);
    }

    sttm->closeResultSet(rset);
    conn->terminateStatement(sttm);
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);

    return json_res;
  });

  CROW_ROUTE(app, "/v1/products/<int>")
  ([](const int code) {
    using namespace oracle::occi;

    Environment* env = Environment::createEnvironment(Environment::DEFAULT);
    Connection* conn = env->createConnection(argv[1], argv[2], argv[3]);

    const char* sql{ "SELECT descricao FROM PCPRODUT WHERE CODPROD = :v1" };

    Statement* sttm = conn->createStatement(sql);
    sttm->setNumber(1, code);

    ResultSet* rset{ sttm->executeQuery() };
    crow::json::wvalue json_res;

    while (rset->next()) {
      json_res["name"] = rset->getString(1);
    }

    sttm->closeResultSet(rset);
    conn->terminateStatement(sttm);
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);

    return json_res;
  });

  app.port(18080).multithreaded().run();

  return 0;
}
