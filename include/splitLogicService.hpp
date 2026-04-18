#pragma once
#include<stdio.h>
#include<iostream>
#include<string>
#include "splitwise.hpp"
#include "user.hpp"
#include "splitInput.hpp"
using namespace std;
class splitLogicService
{
    public:

        virtual vector<pair<string,double>> split( double amount, string name, splitInput* si) = 0;
        virtual ~splitLogicService(){} ;
};