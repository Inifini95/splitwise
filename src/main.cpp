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

cout << "\n--- TEST 3: Uneven ---\n";

    splitwiseService sw;

    sw.addUser("A");
    sw.addUser("B");
    sw.addUser("C");

    equalSplitLogicService equalSplit;
    splitLogicService* splitLogic = &equalSplit;

    equalSplitInput eqi;

    eqi.participants = {"A","B","C"};
    sw.addPayment(300, "A", splitLogic, &eqi); // B,C owe 100

    eqi.participants = {"B","C"};
    sw.addPayment(150, "B", splitLogic, &eqi); // C owes 75

    sw.displayBalance();
}
