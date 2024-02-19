#pragma once

#include <string>

class Costumer
{

public:
  std::string name, address, neighborhood, city, tax_id, address_number;
  Costumer(const std::string& name,
           const std::string& address,
           const std::string& neighborhood,
           const std::string& city,
           const std::string& tax_id,
           const std::string& address_number);
};
