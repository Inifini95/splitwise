#include "percentSplitLogicService.hpp"

vector<pair<string,double>> percentSplitLogicService::split(double amount, string name, splitInput* si)
{

    auto percentSi = static_cast<percentageSplitInput*>(si);

    int participantCount = percentSi->participants.size();
    vector<pair<string,double>> ans;

    double sum = 0.00;
    for(auto x:percentSi->percentages)
    {
        sum+=x.second;
    }
    if(sum!=100.00)
    {
        cout<<"percentages dont add up"<<endl;
        return {};
    }
    for(int i=0;i<participantCount;i++)
    {
        if(percentSi->participants[i] == name)continue;

        double p = percentSi->percentages[percentSi->participants[i]];
        double amt = round((p / 100.0) * amount * 100) / 100;
        ans.push_back({percentSi->participants[i],amt});

    }
    return ans;
}