#include<stdio.h>
#include<iostream>
using namespace std;
#include "splitwiseService.hpp"
#include "equalSplitLogicService.hpp"
#include "splitInput.hpp"
#include "equalSplitInput.hpp"
#include "percentageSplitInput.hpp"
#include "percentSplitLogicService.hpp"
int main()
{

    // splitwiseService sw;
    // sw.addUser("abhishek");
    // sw.addUser("rahul");
    // splitLogicService* splitLogic;
    // equalSplitLogicService equalSplit;
    // cout<<"dd"<<endl;
    // splitInput* si;
    // equalSplitInput eqi;
    // eqi.participants = {"abhishek","rahul"};
    // si = &eqi;
    // splitLogic = &equalSplit;
    // sw.addPayment(300.00,"abhishek",splitLogic,si);
    // // splitLogic->split(splitLogic,300.00, "abhishek",{"abhishek", "rahul"},{},{});
    // sw.addUser("atharva");
    // percentageSplitInput pci;
    // pci.participants = {"abhishek","rahul","atharva"};
    // pci.percentages = {{"abhishek",33.33},{"rahul",33.33},{"atharva",33.33}};
    // si = &pci;
    // sw.addPayment(400.00,"atharva",splitLogic,si);
    // // splitLogic->split(400.00, "atharva", {"abhishek", "rahul", "atharva"},{},{});
    // sw.displayBalance();
    // sw.removeUser("rahul");
    // sw.settle("rahul");
    // sw.displayBalance();
    splitwiseService sw;

sw.addUser("abhishek");
sw.addUser("rahul");
sw.addUser("atharva");

equalSplitLogicService equalSplit;
percentSplitLogicService percentSplit;

splitLogicService* splitLogic;

// Equal split
equalSplitInput eqi;
eqi.participants = {"abhishek","rahul","atharva"};

splitLogic = &equalSplit;
sw.addPayment(300, "abhishek", splitLogic, &eqi);

// Percentage split
percentageSplitInput pci;
pci.participants = {"abhishek","rahul","atharva"};
pci.percentages = {
    {"abhishek",50},
    {"rahul",25},
    {"atharva",25}
};

splitLogic = &percentSplit;
sw.addPayment(400, "atharva", splitLogic, &pci);

sw.displayBalance();
    return 0;
}
