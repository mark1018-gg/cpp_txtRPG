#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
    private:
        std::string name;
        std::string type;
        int effectValue;
        int quantity;
        int cost;

    public:
        Item(std::string n, std::string t, int ev, int c, int q = 0);

        std::string getName();
        std::string getType();
        int getEffectValue();
        int getQuantity();
        int getCost();
    
        void addQuantity(int q);
        void setQuantity(int q); 

        void showInfo();
        bool isAvailable();
        void use();
};

#endif