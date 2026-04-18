#pragma once
#include<stdio.h>
#include<iostream>
#include<vector>
#include "user.hpp"
using namespace std;
class Splitwise
{
    public:
        int userCount;
        vector<unique_ptr<user>> userList;
        vector<bool> indexAvailable;
        vector<vector<double>> matrix;//each persons row would depict the amount that column owes to the row. and vice versa.
        //matrix[i][j] = amount j owes to i. +ve amount means owes. _ve means is owed.
        unordered_map<int,string> userIndex;
        unordered_map<string,int> findIndex;
        Splitwise(int n);
        ~Splitwise();


};