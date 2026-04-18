#pragma once
#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
class user
{
    public:
        string name;
        double balance;
        int serialNo;
        double simplifiedTotal;
        user(string name, int serialNo);
        ~user();
};