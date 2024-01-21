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
                     "numeroent FROM PCCLIENT WHERE CODCLI = 7" };

    Statement* sttm = conn->createStatement(sql);
    sttm->setInt(1, code);

    conn->terminateStatement(sttm);
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);

    return sttm->getSQL();
  });

  CROW_ROUTE(app, "/v1/products/<int>")
  ([](const int code) { return std::to_string(code); });

  app.port(18080).multithreaded().run();

  return 0;
}
