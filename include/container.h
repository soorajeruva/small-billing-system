#ifndef CONTAINER_H
#define CONTAINER_H

#include "item.h"

class Container
{
    std::string _file_name;
private:
    std::vector<Item::itemptr>Main_Container;
    bool New_file=true;
    void flush_BufferData();
    void buffer();
    
public:
    void flush();
    void add2Container(Item::itemptr data);
    std::pair<Item::itemptr, int> searchContainer(std::string& element);
    const Item::itemptr searchContainer(const std::string& element);
    void deleteFromContainer(std::string& element);
    void print();
    typedef Container* containerPtr;
    Container(std::string& file_name);
    ~Container();
};
#endif