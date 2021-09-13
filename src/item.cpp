#include"../include/item.h"

std::ofstream& operator <<(std::ofstream& stream,Item::itemptr item)
{
    stream<<item->_name<<","
        <<item->_quantity<<","<<item->_price<<","
        <<item->_tax<<","<<item->_discount<<"\n";
    return stream;
}
std::ostream& operator <<(std::ostream& stream,Item::itemptr item)
{
    stream<<"\n\t"<<item->_name<<"\n\n\tQuantity: "
        <<item->_quantity<<"\n\tPrice\t: "<<item->_price<<"\n\tTax\t: "
        <<item->_tax<<"\n\tDiscount: "<<item->_discount<<
        "\n---------------------------------------\n";
    return stream;
}

std::ofstream& operator <<(std::ofstream& stream,Bill::billPtr item)
{
    stream<<item->_name<<","<<item->_quantity<<","<<item->_cost<<"\n";
    return stream;
}
std::ostream& operator <<(std::ostream& stream,Bill::billPtr item)
{
    stream<<"\n\t"<<item->_name<<"\n\n\tQuantity: "
        <<item->_quantity<<"\n\tCost\t: "<<item->_cost
        <<"\n---------------------------------------\n";
    return stream;
}