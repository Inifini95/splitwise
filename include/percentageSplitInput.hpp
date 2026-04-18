#pragma once
#include "splitInput.hpp"

class percentageSplitInput : public splitInput
{
    public:
        unordered_map<string, double> percentages;
};