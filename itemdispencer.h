#ifndef ITEMDISPENCER_H
#define ITEMDISPENCER_H

#include <map>
#include <string>

#include "chinese_chess.h"


namespace ChineseChess
{

// a class template to store items of specified class, and it's subclasses.
// is to be used as a singletone
template <class Base>
class ItemDispencer
{
private:
    // Base should provide a pointer to itself as a ::ptr
    typedef std::shared_ptr<Base> Base_ptr;
    std::map<std::string, Base_ptr> items_;
    ItemDispencer(const ItemDispencer &);
    void operator =(const ItemDispencer &);
    ItemDispencer() {};
public:
    // declare exception classes
    struct ItemDispencerException {};
    struct ItemDoesNotExist: ItemDispencerException {};
    struct ItemAlreadyExists: ItemDispencerException {};


    // add an item to dictionary with
    void Add(const std::string &key, Base_ptr new_item)
    {
        if(items_.find(key) == items_.end())
        {
            // item already exists
            items_[key] = new_item;
        }
    }

    Base_ptr Get(const std::string &key)
    {
        typename std::map<std::string, Base_ptr>::const_iterator iter = items_.find(key);
        if(iter == items_.end())
            throw ItemDoesNotExist();
        return iter->second;
    }

    static ItemDispencer &Instance()
    {
        static ItemDispencer disp_;
        return disp_;
    }

};

template <class Base> class ItemDispencer<Base *>;

template <class Base>
ItemDispencer<Base>& dispencer()
{
    return ItemDispencer<Base>::Instance();
}

}

#endif // ITEMDISPENCER_H
