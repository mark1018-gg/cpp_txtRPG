#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Item.h"
#include "Skill.h"

class Monster; 

class Player
{
    private:
        std::string name;
        int hp;
        int maxHp;
        int attackPower;
        int mp;
        int maxMp;
        int gold;
        std::vector<Item> items;
        std::vector<Skill> skills;

    public:
        Player(std::string n, int h, int atk, int m);

        std::string getName();
        int getHp();
        int getGold();
    
        void addGold(int g);
        void deductGold(int g);
        void addSkill(Skill s);
        void initInventory();
        int getItemQuantity(std::string itemName);
        void buyItem(std::string itemName);

        // 隨機事件
        void takeDirectDamage(int damage);
        void reduceMaxHp(int amount);
        void loseRandomItem();

        void attack(Monster& target);
        bool useSkill(int skillIndex, Monster& target);
        void takeDamage(int damage);
        void useItem();
        bool isAlive();
        void showStatus();
};

#endif