#include <iostream>

#include <crow.h>

int
main(const int argc, const char** argv)
{
  if (argc <= 3) {
    std::cout << "usage: wsa <username> <password> <connection>\n";
    return 1;
  }

  crow::SimpleApp app;

  CROW_ROUTE(app, "/v1/costumers/<int>")
  ([](const int code) { return std::to_string(code); });

  CROW_ROUTE(app, "/v1/products/<int>")
  ([](const int code) { return std::to_string(code); });

  app.port(18080).multithreaded().run();

  return 0;
}
