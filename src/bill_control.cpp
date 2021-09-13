#include "../include/bill_control.h"

void Bill_Control::add_item(Container::containerPtr& container,std::string name,int quantity)
{
    Bill::billPtr bill;int pos;Item::itemptr item;
    std::tie(item,pos)=container->searchContainer(name);
    if (item==nullptr){PRINT("ITEM NOT FOUND!\n");}
    else
    {
        int temp= item->_quantity-quantity;
        if(temp<0){PRINT("NOT ENOUGH STOCK!");}
        else 
        {   
            float cost=item->_price*quantity;
            bill=new Bill(name,quantity,cost);
            bill_container.push_back(std::make_pair(bill,item));
            PRINT("ITEM ADDED!");
        }
    }
    return;
}
void Bill_Control::modify_item(int item_no,int quantity)
{
    if (item_no>bill_container.size())
    {
        PRINT("ENTER VALID ITEM NUMBER!");
        return;
    }
    item_no-=1;
    auto bill=std::get<Bill::billPtr>(bill_container[item_no]);
    auto item=std::get<Item::itemptr>(bill_container[item_no]);
    int temp= item->_quantity-quantity;
    if(temp<0){PRINT("NOT ENOUGH STOCK!");}
    else 
    {
        bill->_quantity=quantity;
        bill->_cost=item->_price*quantity;
    }
    PRINT("ITEM QUANTITY HAS BEEN MODIFIED!");
    return;
}
void Bill_Control::remove_item(int item_no)
{
    if (item_no>bill_container.size())
    {
        PRINT("ENTER VALID ITEM NUMBER!");
        return;
    }
    item_no-=1;
    auto bill=std::get<Bill::billPtr>(bill_container[item_no]);
    delete bill;
    bill=nullptr;
    auto iterator=bill_container.begin()+item_no;
    bill_container.erase(iterator);
    PRINT("ITEM DELETED!");
    return;
}
void Bill_Control::generate_bill()
{
    std::ofstream f_out(bill_file,std::ios::app);
    if (f_out.is_open())
    {
        for (int i=0; i<bill_container.size();i++)
        {
            auto bill=std::get<Bill::billPtr>(bill_container[i]);
            f_out<<bill;
            auto item=std::get<Item::itemptr>(bill_container[i]);
            item->_quantity-=bill->_quantity;
            delete bill;
            bill=nullptr;
        }
        bill_container.clear();
    }
    else PRINT("ERROR OPENING FILE !");
    f_out.close();
    return;
}
void Bill_Control::quit_bill()
{
    if(! bill_container.empty())
    {
        for (int i=0; i<bill_container.size();i++)
        {
            auto bill=std::get<Bill::billPtr>(bill_container[i]);
            delete bill;
            bill=nullptr;
        }
        bill_container.clear();
    }
    return;
}
