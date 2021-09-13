#include "../include/interface.h"

void input()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
void input_line(std::string stream,std::string &data)
{
    PRINT(stream);
    std::getline(std::cin,data);
}
//----------------------------------------------------------------------
Interface::Interface(Container& container)
{
    this->container=&container;
}
Interface::~Interface()
{}
void Interface::start_menu()
{
    int selection;bool running=true;
    
    while (running)
    {
        system("clear");
        PRINT("\n\n================ BILLING SYSTEM ================\n");
        PRINT("\t1. MANANGE ITEM");
        PRINT("\t2. NEW BILL");
        PRINT("\t3. CREATE SALES REPORT");
        PRINT("\t4. QUIT");
        input("\n\n\tEnter the selection: ",selection);

        switch(selection)
        {
            case 1:
                Interface::manage_items();
                break;
            case 2:
                Interface::new_bill();
                break;
            case 3:
                Interface::report();
                break;
            case 4:
                running=false;
                break;
            default:
                PRINT("\tEnter Valid Key!!");
                input();
        }
    }
    system("clear");
    return;
}

bool Interface::esc()
{
    char esc;
    input("\tESC: E\tCONTINUE: press any key*\t",esc);
    esc=std::toupper(esc);
    if (esc=='E')return true;
    else return false;
}

void Interface::manage_items()
{
    int selection;bool running =true;
    while(running)
    {
        system("clear");
        PRINT("\n\n================ ITEMS SECTION ================\n");
        PRINT("\t1. ADD ITEM");
        PRINT("\t2. REMOVE ITEM");
        PRINT("\t3. SEARCH ITEM DETAILS");
        PRINT("\t4. BACK");
        input("\n\n\tEnter the selection: ",selection);
        switch(selection)
        {
            case 1:
                Interface::add_items();
                break;
            case 2:
                Interface::remove_items();
                break;
            case 3:
                Interface::search_items();
                break;
            case 4:
                running=false;
                break;
            default:
                PRINT("\tEnter Valid Key!!");
                input();
        }
    }
    system("clear");
    return;
}
void Interface::add_items()
{
    char save;
    std::string name;int quantity;float price,tax,discount;
    
    while(true)
    {
        system("clear");
        PRINT("\n\n================ ADD ITEMS ================");
        PRINT("\t\tITEM DETAILS\n");
        input_line("\t1. ITEM NAME   :\t",name);
        while(name=="")
        {
            if(esc()){return;}
            else input_line("\t1. ITEM NAME:\t",name);
        }
        boost::to_upper(name);
        input("\t2. QUANTITY    :\t",quantity);
        input("\t3. PRICE       :\t",price);
        input("\t4. TAX     (%) :\t",tax);
        input("\t5. DISCOUNT(%) :\t",discount);
        
        while (true)
        {
            input("\tSAVE(Y/N) ?\t",save);
            save=std::toupper(save);
            if (save=='Y'){Item_Control::add_item(name,quantity,price,tax,discount);break;}
            else if (save=='N')
            {
                PRINT("ITEM NOT ADDED!\n");
                if (esc())return;
                break;
            }
            else PRINT("INVALID ENTRY!\n");
        } 
        }
    return;
}
void Interface::remove_items()
{
    char ans;std::string name;
    system("clear");
    PRINT("\n\n================ REMOVE ITEMS ================");
    while(true)
    {
        input_line("\t1. ITEM NAME:\t",name);
        while(name=="")
        {
            if(esc()){return;}
            else input_line("\t1. ITEM NAME:\t",name);
        }
        boost::to_upper(name);
        input("\t DELETE (Y/N)\t",ans);
        ans=std::toupper(ans);
        if (ans=='Y'){Item_Control::remove_item(name);return;}
        else if (ans=='N'){PRINT("ITEM NOT REMOVED!\n");return;}
        else
        {
            std::cout<<"Invalid Entry\t";
        }
        input(); 
    }
    return;
}
void Interface::search_items()
{
    system("clear");
    PRINT("\n\n================ SEARCH ITEMS ================");
    std::string name;
    input_line("\t1. ITEM NAME:\t",name);
    while(name=="")
    {
        if(esc()){return;}
        else input_line("\t1. ITEM NAME:\t",name);
    }
    boost::to_upper(name);
    Item_Control::search_item(name);
    input();
}

void Interface::new_bill()
{
    int selection;bool running=true;
    while(running)
    {
        system("clear");
        PRINT("\n\n=================== NEW BILL ===================\n");
        bill_details();
        PRINT("\n\t1. ADD TO LIST\t2. MODIFY LIST\t3. CONFIRM PURCHASE\t4. BACK");
        input("\n\n\tEnter the selection: ",selection);
        switch (selection)
        {
        case 1:
            add2Bill();
            break;
        case 2:
            modifyBill();
            break;
        case 3:
            system("clear");
            bill_details();
            if(bill_container.empty())PRINT("\t LIST IS EMPTY !");
            else
            {
                PRINT("\nHAVE A NICE DAY!\n");
                Bill_Control::generate_bill();
                container->flush();
            }
            input();
            running=false;
            break;
        case 4:
            running=false;
            Bill_Control::quit_bill();
            break;
        
        default:
            PRINT("\tEnter Valid Key!!");
            input();
            break;
        }
    }
    return;
}
void Interface::add2Bill()
{
    char save;
    std::string name;int quantity;float cost;
    Bill::billPtr bill_item;
    
    while(true)
    {
        system("clear");
        PRINT("\n\n========================= ADD ITEM TO BILL =========================\n");
        bill_details();
        PRINT("\n\n!!!SKIP NAMING ITEM TO EXIT!!!\n");
        PRINT("\t\tITEM DETAILS\n");
        input_line("\t1. ITEM NAME:\t",name);
        while(name=="")
        {
            if(esc()){return;}
            else input_line("\t1. ITEM NAME:\t",name);
        }
        boost::to_upper(name);
        input("\t2. QUANTITY :\t",quantity);
        Bill_Control::add_item(container,name,quantity);
        input();
    }
    return;
}
void Interface::modifyBill()
{
    int item_no;std::string name;char ans;int new_quantity;
    system("clear");
    PRINT("\n\n================ MODIFY ITEMS IN BILL ================\n");
    bill_details();
    if(bill_container.empty())
    {
        PRINT("\t LIST IS EMPTY !");
        PRINT("NO MODIFICATION MADE!\n");
        input();
        return;
    }
    input("\tENTER NO. :\t",item_no);
    while(true)
    {
        input("\t CHANGE QUANTITY (Y/N)\t",ans);
        ans=std::toupper(ans);
        if (ans=='Y')
        {
            input("\t QUANTITY:\t",new_quantity);
            Bill_Control::modify_item(item_no,new_quantity);
            break;
        }
        else if (ans=='N')
        {
            input("\t DELETE ITEM (Y/any_key)\t",ans);
            ans=std::toupper(ans);
            if (ans=='Y')Bill_Control::remove_item(item_no);
            else PRINT("NO MODIFICATION MADE!\n");
            break;
        }
        else
        {
            PRINT("\tInvalid Key!!");
        }
    }
    input();
    return;
}
void Interface::bill_details()
{
    float total_cost=0;
    if (!bill_container.empty())
    {
        PRINT("----------------------------------------------------------------\n");
        for (int i=0; i<bill_container.size();i++)
        {
            auto [bill,_]=bill_container[i];
            PRINT("  NO:"<<(i+1)<<"\tITEM NAME:"<<bill->_name
                <<"\t Quantity: "<<bill->_quantity
                <<"\t COST: "<<bill->_cost<<"\n");
                total_cost+=bill->_cost;
        }
        PRINT("----------------------------------------------------------------\n");
        PRINT("\t TOTAL COST: "<<total_cost<<"\n");
    }
}

void Interface::report()
{
    system("clear");
    PRINT("\n\n================ NEW REPORT ================");
    return;
}