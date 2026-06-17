#ifndef SKILL_H
#define SKILL_H
#include <string>

class Skill
{
    private:
        std::string name;
        int damage;
        int mpCost;

    public:
        Skill(std::string n, int d, int mc);

        std::string getName();
        int getDamage();
        int getMpCost();

        void showInfo();
        void use(int currentMp, int maxMp);
};

#endif