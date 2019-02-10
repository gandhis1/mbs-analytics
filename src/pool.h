#ifndef POOL_H
#define POOL_H

#include <string>

class Pool
{
  private:
    std::string id;

  public:
    Pool(std::string id);
    friend class Engine;
};

#endif
