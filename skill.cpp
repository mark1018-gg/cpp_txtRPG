#include "Skill.h"
#include <iostream>
using namespace std;

Skill::Skill(string n,int d,int mc):name(n),damage(d),mpCost(mc){}

string Skill::getName()
{ 
    return name; 
}
int Skill::getDamage()
{ 
    return damage; 
}
int Skill::getMpCost()
{ 
    return mpCost; 
}

void Skill::showInfo()
{
    cout<<" 技能: "<<name<<" (消耗 MP: " << mpCost << ", 傷害: " << damage << ")"<<endl;
}

void Skill::use(int currentMp, int maxMp)
{
    cout<<"施放了技能【" << name << "】！ (剩餘魔力: " << currentMp << "/" << maxMp << ")"<<endl;
}