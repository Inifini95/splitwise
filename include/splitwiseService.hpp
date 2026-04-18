#pragma once
#include<stdio.h>
#include<iostream>
#include<string>
#include "splitwise.hpp"
#include "user.hpp"
#include "splitLogicService.hpp"
#include "splitInput.hpp"
using namespace std;
class splitwiseService
{
    public:
        Splitwise* sw;

        splitwiseService();
        ~splitwiseService();
        void addUser(string name);
        void removeUser(string name);
        void splitAmount();
        void displayBalance();
        void addPayment(double amount, string name, splitLogicService* splitLogic, splitInput* si);
        void settle(string name);
        void simplify();
        int findAvailableIndex();
        user* findUser(string name);

};