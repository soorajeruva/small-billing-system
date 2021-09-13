#ifndef ITEM_H
#define ITEM_H

#include<iostream>
#include<limits>
#include<fstream>
#include<boost/algorithm/string.hpp>

#include<vector>
#include<array>
#include<tuple>

#define PRINT(X) std::cout<<"\n"<<X

class Item
{
private:
    static int _TOTAL_ITEM;
public:
    Item(std::string name,int quantity,float price,float tax,float discount):
    _name(name),_quantity(quantity),_price(price),_tax(tax),_discount(discount)
    {_TOTAL_ITEM++;}

    Item(){}

    ~Item()
    {
        _TOTAL_ITEM--;
    }
    
    int _item_no=_TOTAL_ITEM;
    std::string _name="NA";
    int _quantity=0;
    float _price=0;
    float _tax=0;
    float _discount=0;

    typedef Item* itemptr;
};
std::ofstream& operator <<(std::ofstream& stream,Item::itemptr item);
std::ostream& operator <<(std::ostream& stream,Item::itemptr item);

struct Bill
{
    std::string _name;
    int _quantity;
    float _cost=0;
    typedef Bill* billPtr;
    Bill(std::string name, int quantity,float cost):_name(name),_quantity(quantity),_cost(cost){}
};
std::ofstream& operator <<(std::ofstream& stream,Bill::billPtr item);
std::ostream& operator <<(std::ostream& stream,Bill::billPtr item);
#endif