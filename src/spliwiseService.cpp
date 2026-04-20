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
vector<double> splitwiseService::buildNetBalance() {
    int n = sw->matrix.size();
    vector<double> net(n, 0.0);

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {

            double val = sw->matrix[i][j];

            // ONLY consider one direction to avoid double counting
            if (val > 0) {
                net[i] += val;   // i should receive
                net[j] -= val;   // j should pay
            }
        }
    }

    return net;
}
void splitwiseService::displayBalance()
{

    vector<double> net = buildNetBalance();

    // Step 2: minimize
    auto transactions = minimizeTransactions(net);

    // Step 3: display
    if (transactions.empty()) {
        cout << "No balances to settle\n";
        return;
    }

    

    for (auto& [fromIdx, toIdx, amount] : transactions) {
    cout << sw->userIndex[fromIdx] << " pays "
         << sw->userIndex[toIdx] << " ₹ " << amount << endl;
}
    
}

void splitwiseService::addPayment(double amount, string name, splitLogicService* splitLogic, splitInput* si)
{
    if(amount<0.00)
    {
        cout<<"Enter a valid amount"<<endl;
        return;
    }
    if(sw->findIndex.find(name)==sw->findIndex.end())
    {
        cout<<"User doesn't exist";
        return;
    }
    vector<pair<string,double>> ans = splitLogic->split(amount,name, si);

    int payerIndex = this->sw->findIndex[name];

    for(int i = 0;i<ans.size();i++)
    {
        int payeeIndex = this->sw->findIndex[ans[i].first];
        double amt = ans[i].second;
        this->sw->matrix[payerIndex][payeeIndex] += amt;
        this->sw->matrix[payeeIndex][payerIndex] -= amt;
    }
    

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

//settles only the amount that the person owes to others.
void splitwiseService::settle(string name)
{
    if(sw->findIndex.find(name)==sw->findIndex.end())
    {
        cout<<"user not found"<<endl;
        return;
    }
    double amount = 0.00;
    int serial = sw->findIndex[name];
    for(int i = 1;i<=sw->userCount;i++)
    {
        if(i==serial)continue;

        if(sw->matrix[serial][i]<0)
        {
            amount+=sw->matrix[serial][i]*(-1);
            sw->matrix[serial][i] = 0.00;
            sw->matrix[i][serial] = 0.00;
        }
    }
    
    cout<<"amount settled by "<<name<<" is "<<amount<<endl;
}

vector<tuple<int, int, double>> splitwiseService::minimizeTransactions(vector<double> net) {
    int n = net.size();

    vector<pair<int, double>> debtors, creditors;

    for (int i = 0; i < n; i++) {
        if (net[i] < -1e-6)
            debtors.push_back({i, net[i]});
        else if (net[i] > 1e-6)
            creditors.push_back({i, net[i]});
    }

    // Most negative first (largest debtor)
    sort(debtors.begin(), debtors.end());

    // Largest creditor first
    sort(creditors.begin(), creditors.end(),
         [](auto& a, auto& b) { return a.second > b.second; });

    int i = 0, j = 0;
    vector<tuple<int, int, double>> result;

    while (i < debtors.size() && j < creditors.size()) {
        auto& [dIdx, dAmt] = debtors[i];
        auto& [cIdx, cAmt] = creditors[j];

        double settleAmount = min(-dAmt, cAmt);

        result.push_back({dIdx, cIdx, settleAmount});

        dAmt += settleAmount;
        cAmt -= settleAmount;

        if (abs(dAmt) < 1e-6) i++;
        if (abs(cAmt) < 1e-6) j++;
    }

    return result;
}
 void splitwiseService::simplify()
{

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
}
