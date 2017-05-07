#include "regular.h"

/*
 * 返回炸弹的大小
 * 0 不是炸弹
 * 3-15 3-2炸弹
 * 16 大小王
 */
int Regular::is_bomb(const std::vector<int> & cards)
{
    int ret = 0;
    int num = cards.size();
    if(!(num==4||num==6||num==2))
    {
        return ret;
    }

    std::sort(cards.begin(),cards.end());
    if(num==2)
    {
        // 大小王
        if(cards[0]==16&&cards[1]==17) ret = 16;
    }
    else if(num==4)
    {
        // 不带牌
        if(cards[0]==cards[3])
        {
            return cards[0];
        }
        else if(cards[0]==cards[2])
        {
            return cards[0];
        }
        else if(cards[1]==cards[2])
        {
            return cards[2];
        }
    }
    else if(num==6)
    {
        if(cards[0]==cards[3])
        {
            return cards[0];
        }
        else if(cards[2]==cards[5])
        {
            return cards[2];
        }
    }
    return ret;
}
