#include "splitwiseService.hpp"
#include "equalSplitLogicService.hpp"
#include "splitLogicService.hpp"
splitwiseService::splitwiseService()
{
    sw = new Splitwise(0);
    sw->matrix = vector<vector<double>>(100,vector<double>(100,0.00));
    sw->indexAvailable = vector<bool>(100,true);
}

splitwiseService::~splitwiseService(){}

void splitwiseService::addUser(string name)
{
    cout<<"add user"<<endl;
    int serialNo = findAvailableIndex();
    if(serialNo ==-1)
    {
        cout<<"group full buddy"<<endl;
        return;
    }
    sw->userList.push_back(make_unique<user>(name,serialNo));
    sw->userCount++;
    sw->userIndex[serialNo] = name;
    sw->findIndex[name] = serialNo;
    sw->indexAvailable[serialNo] = false;
}

int splitwiseService::findAvailableIndex()
{
    for(int i=1;i<sw->indexAvailable.size();i++)
    {
        if(sw->indexAvailable[i] ==true)
        {
            return i;
        }
    }
    return -1;
}
void splitwiseService::removeUser(string name)
{
    
    
    int serialNo = this->sw->findIndex[name];
    for(int i=1;i<=sw->userCount;i++)
    {
        if(sw->matrix[i][serialNo]!=0.0)
        {
            cout<<"due balance, cant delete user"<<endl;
            return;
        }
    }
    sw->userIndex.erase(serialNo);
    sw->findIndex.erase(name);
    for(int i=0;i<sw->userList.size();i++)
    {
        if(sw->userList[i].get()->serialNo == serialNo)
        {
            sw->userList.erase(sw->userList.begin()+i);
            break;
        }
    }
    sw->userCount--;
    
}

void splitwiseService::displayBalance()
{
    cout<<"a"<<endl;
    for(int i=1;i<=sw->userCount;i++)
    {
        
        string curr = sw->userIndex[i];
        for(int j = 1;j<=sw->userCount;j++)
        {
            if(sw->matrix[i][j] > 0.00)
            {
                cout<<sw->userIndex[j]<<" owes "<<sw->matrix[i][j]<<" to "<<sw->userIndex[i]<<endl;
            }
        }
    }
    
}

void splitwiseService::addPayment(double amount, string name, splitLogicService* splitLogic, splitInput* si)
{
    
    vector<pair<string,double>> ans = splitLogic->split(amount,name, si);

    int payerIndex = this->sw->findIndex[name];

    for(int i = 0;i<ans.size();i++)
    {
        int payeeIndex = this->sw->findIndex[ans[i].first];
        double amt = ans[i].second;
        this->sw->matrix[payerIndex][payeeIndex] += amt;
        this->sw->matrix[payeeIndex][payerIndex] -= amt;
    }
    // double split_amount = amount/sw->userCount;
    // cout<<name<<" "<<split_amount<<endl;
    // user* u = findUser(name);
    
    // if(u==nullptr)
    // {
    //     cout<<"user not found"<<endl;
    //     return;
    // }
    // int serial = u->serialNo;

    // cout<<"serial no "<<serial<<endl;
    // cout<<" user count "<<sw->userCount<<endl;
    // for(int i = 1;i<=sw->userCount;i++)
    // {
    //     if(i==serial)
    //     {continue;}
    //     sw->matrix[serial][i] += split_amount;
    //     sw->matrix[i][serial] -= split_amount;
    // }

}
user* splitwiseService::findUser(string name)
{
    for(auto& x : sw->userList)
    {
        if(x.get()->name == name)
        {
            return x.get();
        }
    }
    return nullptr;
}

void splitwiseService::settle(string name)
{
    // user* u = findUser(name);
    
    // if(u==nullptr)
    // {
    //     cout<<"user not found"<<endl;
    //     return;
    // }
    // double amount = 0.00;
    // int serial = u->serialNo;
    // for(int i = 1;i<=sw->userCount;i++)
    // {
    //     if(i==serial)continue;

    //     if(sw->matrix[serial][i]<0)
    //     {
    //         amount+=sw->matrix[serial][i]*(-1);
    //         sw->matrix[serial][i] = 0.00;
    //         sw->matrix[i][serial] = 0.00;
    //     }
    // }
    
    // cout<<"amount settled by "<<name<<" is "<<amount<<endl;
}
// void splitwiseService::simplify()
// {
//     cout<<"aaaa"<<endl;
//     user* giver = nullptr;
//     for(auto x : sw->userList)
//     {
//         if(x->balance-x->simplifiedTotal<0)
//         {
//             if(giver == nullptr)
//             {
//                 giver = x;

//             }
//             else
//             {
//                 if(giver->balance-giver->simplifiedTotal<x->balance-x->simplifiedTotal)
//                 {
//                     giver = x;
//                 }
//                 else{
//                     continue;
//                 }
//             }
//         }

//     }
//     if(giver == nullptr)
//     {
//         return;
//     }
//     user* taker = nullptr;

//     for(auto x : sw->userList)
//     {
//         if(x->balance - x->simplifiedTotal>0)
//         {
//             if(taker == nullptr)
//             {
//                 taker = x;

//             }
//             else
//             {
//                 if(taker->balance-taker->simplifiedTotal>x->balance-x->simplifiedTotal)
//                 {
//                     taker = x;
//                 }
//                 else{
//                     continue;
//                 }
//             }
//         }

//     }

//     cout<<giver->name<<" is the giver"<<endl;
//     cout<<taker->name<<" is the taker "<<endl;
//     if(giver->balance-giver->simplifiedTotal + taker->balance- taker->simplifiedTotal >=0)
//     {
//         giver->owesfrom.push_back({taker,taker->balance - taker->simplifiedTotal});
//         taker->owesTo.push_back({giver, taker->balance-taker->simplifiedTotal});
//         cout<<taker->name<<" owes "<<taker->balance - taker->simplifiedTotal<<" to "<<giver->name<<endl;
//         giver->simplifiedTotal +=  taker->balance-taker->simplifiedTotal;
//         taker->simplifiedTotal += taker->balance-taker->simplifiedTotal;
//     }
//     else
//     {
//         giver->owesfrom.push_back({taker, taker->balance-taker->simplifiedTotal});
//         taker->owesTo.push_back({giver, taker->balance-taker->simplifiedTotal});
//         cout<<taker->name<<" owes "<<taker->balance-taker->simplifiedTotal<<" to "<<giver->name<<endl;

//         giver->simplifiedTotal = giver->balance-giver->simplifiedTotal;
//         taker->simplifiedTotal += giver->balance - giver->simplifiedTotal;
//     }
//     simplify();
// }
