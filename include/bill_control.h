#include "item.h"
#include "container.h"

class Bill_Control
{
private:
    std::string bill_file="bin/bill.txt";
public:
    bool new_bill=true;
    std::vector< std::pair<Bill::billPtr,Item::itemptr> >bill_container;
    void generate_bill();
    void quit_bill();
    void add_item(Container::containerPtr& container, std::string name,int quantity);
    void modify_item(int item_no,int quantity);
    void remove_item(int item_no);
};