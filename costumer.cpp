#include "costumer.h"

Costumer::Costumer(const std::string& name,
                   const std::string& address,
                   const std::string& neighborhood,
                   const std::string& city,
                   const std::string& tax_id,
                   const std::string& address_number)
  : name(name)
  , address(address)
  , neighborhood(neighborhood)
  , city(city)
  , tax_id(tax_id)
  , address_number(address_number)
{
}
