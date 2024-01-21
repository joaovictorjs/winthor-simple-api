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

    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);

    return std::to_string(code);
  });

  CROW_ROUTE(app, "/v1/products/<int>")
  ([](const int code) { return std::to_string(code); });

  app.port(18080).multithreaded().run();

  return 0;
}
