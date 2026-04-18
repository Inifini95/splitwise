#pragma once
#include "splitLogicService.hpp"
#include "splitInput.hpp"
#include "percentageSplitInput.hpp"
class percentSplitLogicService : public splitLogicService
{
    public:
        vector<pair<string,double>> split( double amount, string name, splitInput* si);
};        