#include "../include/container.h"
//--------------------------------------------------------------------------------------------------------
Container::Container(std::string& file_name):_file_name(file_name)
{
    buffer();
}
Container::~Container()
{
    flush();
}
void Container::add2Container(Item::itemptr data)
{
    Main_Container.push_back(data);
    flush_BufferData();
}
void Container::print()
{
    int count=0;
    for (Item::itemptr data: Main_Container)
    {
        count++;
        std::cout<<data;
    }
    std::cout<<std::endl;
}
void Container::flush()
{   
    std::ofstream f_out(_file_name);
    if (f_out.is_open())
    {
        f_out<<"name,quantity,price,tax,discount\n";
        if(! Main_Container.empty())
        {
            for (int i=0; i<Main_Container.size();i++)
            {
                Item::itemptr item;
                item=Main_Container[i];
                f_out<<item;
            }
        }
    }
    // else PRINT("ERROR OPENING FILE !");
    f_out.close();
    return;
}
void Container::flush_BufferData()
{   
    std::ofstream f_out(_file_name,std::ios::app);
    if (f_out.is_open())
    {
        if(New_file)f_out<<"name,quantity,price,tax,discount\n";
        if(! Main_Container.empty())
        {
                Item::itemptr item;
                item=Main_Container.back();
                f_out<<item;
        }
    }
    // else PRINT("ERROR OPENING FILE DURING ADDING ITEMS!");
    f_out.close();
    return;
}
void Container::buffer()
{
    std::ifstream f_in(_file_name);
    Main_Container.clear();
    if (f_in.is_open())
    {
            Item::itemptr item;
            std::string line;std::vector<std::string>data;
            if(getline(f_in,line))
            {
                New_file=false;
                while(std::getline(f_in,line))
                {
                    boost::split(data,line,boost::is_any_of(","));
                    item=new Item(data[0],std::stoi(data[1]),std::stof(data[2])
                                        ,std::stof(data[3]),std::stof(data[4]));
                    Main_Container.push_back(item);
                }
            }
            else New_file=true;
    }
    // else PRINT("ERROR OPENING FILE !\n Buffer not created !");
    f_in.close();
    return;
}

const Item::itemptr Container::searchContainer(const std::string &element)
{
    for (Item::itemptr item:Main_Container)
    {
        if(element==item->_name)return item;
    }
    return nullptr;
}
std::pair<Item::itemptr, int> Container::searchContainer(std::string &element)
{
    for (int i=0;i<Main_Container.size();i++)
    {
        Item::itemptr item=Main_Container[i];
        if(element==item->_name)return std::make_pair(item,i);
    }
    return std::make_pair(nullptr,0);
}
void Container::deleteFromContainer(std::string& element)
{
    auto [item,position]=searchContainer(element);
    if(item==nullptr)PRINT("Item: "<<element<<" not found!");
    else
    {
        delete item;
        auto iterator=Main_Container.begin()+position;
        Main_Container.erase(iterator);
        PRINT("Item: "<<element<<" has been removed!");
    }
    return;
}

//--------------------------------------------------------------------------------------------------------