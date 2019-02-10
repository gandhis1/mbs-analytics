#ifndef SECURITY_H
#define SECURITY_H

#include <string>

class Security
{
  private:
    std::string id;

  public:
    Security(std::string id);
    friend class Engine;
};

#endif