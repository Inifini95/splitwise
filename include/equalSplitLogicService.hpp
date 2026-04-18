#pragma once
#include<stdio.h>
#include<iostream>
#include<string>
#include "splitwise.hpp"
#include "user.hpp"
#include "splitInput.hpp"
#include "equalSplitInput.hpp"
#include "percentageSplitInput.hpp"
#include "splitLogicService.hpp"
using namespace std;
class equalSplitLogicService : public splitLogicService
{
    public:
        vector<pair<string,double>> split( double amount, string name, splitInput* si);
        

};