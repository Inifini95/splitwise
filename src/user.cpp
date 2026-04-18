#include "user.hpp"

user::user(string name, int serialNo)
{
    this->serialNo = serialNo;
    this->name = name;
    simplifiedTotal = 0.00;
    balance = 0.00;
}
user::~user(){}

