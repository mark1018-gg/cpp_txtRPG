#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Item.h"
#include "Skill.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

int main()
{
    srand(time(NULL));

    string user_name;
    cout << "請輸入您的大名 > ";
    cin >> user_name;
    cout << endl << user_name << "您好 !!!"<<endl;

    cout << "==================================" << endl;
    cout << "        歡迎來到文字RPG !!!        " << endl;
    cout << "       這是一個勇者的故事...        " << endl;
    cout << "==================================" << endl;

    // 選擇職業
    int classChoice;
    cout << user_name << "請選擇你的職業:\n(1) 戰士 (HP:100, Atk:20, MP:120)\n(2) 射手 (HP:75, Atk:30, MP:100)\n(3) 法師 (HP:50, Atk:40, MP:80)\n> ";
    cin >> classChoice;

    Player* player = nullptr;
    if (classChoice == 1)
    {
        player = new Player("戰士", 100, 20, 120);
        player->addSkill(Skill("劈砍", 30, 30));
        player->addSkill(Skill("正義之劍", 50, 50));
    }
    else if (classChoice == 2)
    {
        player = new Player("射手", 75, 30, 100);
        player->addSkill(Skill("一箭穿心", 40, 25)); 
        player->addSkill(Skill("萬箭齊發", 60, 40));
    }
    else
    {
        player = new Player("法師", 50, 40, 80);
        player->addSkill(Skill("火球", 60, 20));
        player->addSkill(Skill("迷幻法陣", 70, 35));
    }

    player->initInventory();// 初始化item

    //設定怪物陣容
    vector<Monster> monsters= 
    {
        Monster("哥布林",60,10,10),
        Monster("哥布林長老",70,15,20),
        Monster("石頭人",80,20,20),
        Monster("閃電鳥",100,30,20),
        Monster("哥吉拉",150,50,0)
    };

    vector<Item> shopItems= 
    {
        Item("能量飲尿","MP_REGEN",20,10),
        Item("麻辣加血","HP_BUFF",15,20),
        Item("超級馬力","ATK_BUFF",20,30)
    };

    //遊戲主迴圈
    for (int stage = 0; stage < monsters.size(); stage++) 
    {
        Monster& currentMonster = monsters[stage];
        cout << "\n\n>>>>>>>> 第 " << stage + 1 << " 輪戰鬥開始 <<<<<<<<" << endl;
        
        if (stage == 0) 
        {
            cout << "【劇情】微風吹過新手村外的樹林，一隻流著口水的哥布林從草叢裡跳了出來！" << endl;
        } 
        else if (stage == 1) 
        {
            cout << "【劇情】你繼續深入叢林，四周的光線變得昏暗。一隻拄著法杖、眼神狡黠的哥布林長老擋住了你的去路！" << endl;
        } 
        else if (stage == 2) 
        {
            cout << "【劇情】穿過危險的叢林，你來到了荒蕪的山腳下。突然，腳下的巨石開始劇烈震動，一個巨大的石頭人站了起來！" << endl;
        }
        else if (stage == 3) 
        {
            cout << "【劇情】你辛苦地爬到了半山腰，四周雷聲大作。伴隨著刺眼的閃光，一隻渾身帶電的閃電鳥從烏雲中俯衝而下！" << endl;
        }
        else if (stage == 4)
        {
            cout << "【劇情】終於登上了山頂！火山口冒著濃煙，伴隨著震耳欲聾的咆哮，終極 Boss 哥吉拉帶著毀滅的氣息出現在你面前！" << endl;
        }
        cout << "遭遇了怪物: " << currentMonster.getName() << " ! " << endl;

        // 戰鬥階段
        while (player->isAlive() && currentMonster.isAlive())
        {
            player->showStatus();
            currentMonster.showInfo();

            int action;
            cout << "\n請選擇行動: (1) 普通攻擊  (2) 技能1  (3) 技能2\n> ";
            cin >> action;

            bool actionSuccess = false;

            if (action == 1)
            {
                player->attack(currentMonster);
                actionSuccess = true;
            }
            else if (action == 2)
            {
                actionSuccess = player->useSkill(0, currentMonster);
            }
            else if (action == 3)
            {
                actionSuccess = player->useSkill(1, currentMonster);
            }
            else
            {
                cout << "輸入錯誤，請重新選擇！" << endl;
            }

            if (!actionSuccess)
            {
                continue; 
            }

            if (currentMonster.isAlive())
            {
                currentMonster.attack(*player);
            }
        }

        if (!player->isAlive())
        {
            cout << "\n【遊戲結束】你被 " << currentMonster.getName() << " 擊敗了，勇者的傳說到此為止..." << endl;
            delete player;
            return 0;
        }

        cout << "\n戰鬥勝利 ! 擊殺了 " << currentMonster.getName() << " ! " << endl;
        
        if (stage == monsters.size() - 1)
        {
            cout << "\n恭喜 "<< user_name <<" !!! 你擊敗了終極 Boss 哥吉拉，成為了真正的英雄!!!" << endl;
            break;
        }

        player->addGold(currentMonster.getRewardGold());
        cout << "獲得金幣: " << currentMonster.getRewardGold() << " (目前金幣: " << player->getGold() << ")" << endl;

        // 商店購買模式
        cout << "\n======== 進入商店 ========" << endl;
        while (true)
        {
            cout << "\n[目前持有金幣]: " << player->getGold() << endl;
            cout << "--- 販售物品 ---" << endl;
            for (int i = 0; i < shopItems.size(); i++)
            {
                cout << "(" << i + 1 << ") ";
                shopItems[i].setQuantity(player->getItemQuantity(shopItems[i].getName()));
                shopItems[i].showInfo();
            }
            cout << "(0) 結束購買並出發" << endl;
            
            int buyChoice;
            cout << "請輸入購買選項 > ";
            cin >> buyChoice;

            if (buyChoice == 0)
            {
                break;
            }
            else if (buyChoice >= 1 && buyChoice <= 3)
            {
                Item& selectedItem = shopItems[buyChoice - 1];
                if (player->getGold() >= selectedItem.getCost())
                {
                    player->deductGold(selectedItem.getCost());
                    player->buyItem(selectedItem.getName());
                    cout << ">> 購買【" << selectedItem.getName() << "】成功！" << endl;
                }
                else
                {
                    cout << ">> [錯誤] 金幣不足！" << endl;
                }
            }
            else
            {
                cout << ">> [錯誤] 無效的選項！" << endl;
            }
        }

    return(0);
}
