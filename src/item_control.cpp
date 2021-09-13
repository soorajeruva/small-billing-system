#include "../include/item_control.h"

int Item::_TOTAL_ITEM=0;

Item_Control::Item_Control()
{
}
Item_Control::~Item_Control()
{
}
void Item_Control::add_item(std::string name,int quantity,float price,float tax,float discount)
{   
    auto new_item=new Item(name,quantity,price,tax,discount);
    container->add2Container(new_item);
    std::cout<<"\t\tAdded item: "<<new_item->_name<<"\n";
    return;
}
void Item_Control::search_item(const std::string& name)//add a print too...
{
    Item::itemptr result;
    result=container->searchContainer(name);
    if(result==nullptr)PRINT("\tNO ELEMENT BY THE NAME "<<name<<" FOUND!\n");
    else std::cout<<result;
    return;
}

void Item_Control::remove_item(std::string name)
{
    std::vector<std::string>elements;
    boost::split(elements,name,boost::is_any_of(","));
    itemptr data;
    for (int i=0;i<elements.size();i++)
    {
        container->deleteFromContainer(elements[i]);
    }
    container->flush();
    return;
}
//------------------------------------construction................................
void Item_Control::show_item(std::string name)
{
    container->print();
}