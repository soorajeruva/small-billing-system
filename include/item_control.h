#ifndef ITEM_CONTROL_H
#define ITEM_CONTROL_H

#include"item.h"
#include "container.h"



class Item_Control:private Item
{
public:
    Item_Control();
    ~Item_Control();
    Container::containerPtr container;
    void add_item(std::string name,int quantity,float price,float tax,float discount);
    void search_item(const std::string& name);
    void remove_item(std::string name);
    void show_item(std::string name);
    typedef Item_Control* item_ControlPtr;
};

#endif