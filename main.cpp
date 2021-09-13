#include "include/interface.h"

int main()
{
    std::string store_item="bin/text.txt";
    Container storage(store_item);
    Interface interface(storage);
    interface.start_menu();
    return 0;
}