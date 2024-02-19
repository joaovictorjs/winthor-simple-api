#include <iostream>

#include <crow.h>

#include "dummy_data.h"

int
main(const int argc, const char** argv)
{
  crow::SimpleApp app;

  CROW_ROUTE(app, "/v1/costumers/<int>")
  ([&argv](const int code) {
    crow::json::wvalue json_res;

    Costumer costumer = costumers[code % 10];

    json_res["name"] = costumer.name;
    json_res["address"] = costumer.address;
    json_res["neighborhood"] = costumer.neighborhood;
    json_res["city"] = costumer.city;
    json_res["tax_id"] = costumer.tax_id;
    json_res["address_number"] = costumer.address_number;

    return json_res;
  });

  CROW_ROUTE(app, "/v1/products/<int>")
  ([&argv](const int code) {
    crow::json::wvalue json_res;

    json_res["name"] = products[code % 10];

    return json_res;
  });

  app.port(18080).multithreaded().run();

  return 0;
}
