#include "equalSplitLogicService.hpp"



vector<pair<string,double>> equalSplitLogicService::split(double amount, string name, splitInput* si)
{
    auto equalSi = static_cast<equalSplitInput*>(si) ;
    int participantCount = equalSi->participants.size();
    double split_amount = round(amount/(participantCount) *100)/100;
    cout<<name<<" "<<split_amount<<endl;
    
    vector<pair<string,double>> ans;
    for(int i=0;i<participantCount;i++)
    {
        if(equalSi->participants[i] == name)
        {
            continue;
        }
        ans.push_back({equalSi->participants[i] , split_amount});
    }
    return ans;
}
