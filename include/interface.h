#ifndef INTERFACE_H
#define INTERFACE_H

#include "item_control.h"
#include "bill_control.h"

template<typename T> 
void input(std::string data,T &data2)
{
    PRINT(data);
    std::cin>>data2;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void input();
void input_line();

class Interface:private Item_Control, Bill_Control
{
private:
    bool esc();
    void manage_items();
        void add_items();
        void remove_items();
        void search_items();
    void new_bill();
        void bill_details();
        void add2Bill();
        void modifyBill();
    void report();

public:
    Interface(Container& container);
    ~Interface();
    void start_menu();
};

#endif