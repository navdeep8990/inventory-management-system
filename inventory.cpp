#include <iostream>
#include <conio.h>
#include <fstream>
#include <process.h>
#include <string.h>
#include <windows.h>
#include <cmath>
using namespace std;

class menus
{
private:
    int ch;

public:
    void thanks()
    {
        system("cls");
        cout << "\t====================================\n";
        cout << "\tThanks For Using Our Application\n";
        cout << "\t====================================\n\n";
        Sleep(800);
        system("cls");
        exit(-1);
    }
    void main_menu();
    void update_menu();
} obj;

class operation
{
    friend void menus::update_menu();
    struct stock
    {
        char itemname[25];
        int quantity;
        float itemprice;
        char itemcode[6];
    } sct;
    char ch;

public:
    int strlen(char temp[])
    {
        int i = 0;
        while (temp[i] != '\0')
        {
            i++;
        }
        return i;
    }
    int count_digit(float n)
    {
        return (log10(n) + 1);
    }
    void spacing(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            cout << " ";
        }
    }
    void additem()
    {
        system("cls");
        cout << "\t===========================\n";
        cout << "\t\tADD ITEM\n";
        cout << "\t===========================\n\n";
        cin.ignore();
        ofstream file;
        file.open("fact.txt", ios::app);
        cout << "enter the name of item:" << endl;
        gets(sct.itemname);
        cout << "enter the price of item:" << endl;
        cin >> sct.itemprice;
        cout << "enter the quantity of item:" << endl;
        cin >> sct.quantity;
        cin.ignore();
        cout << "enter the code of item:" << endl;
        gets(sct.itemcode);
        file.write((char *)&sct, sizeof(sct));
        file.close();
        cout << "\n Want to Add More ? y/n:";
        cin >> ch;
        switch (toupper(ch))
        {
        case 'Y':
            additem();
            break;
        case 'N':
            obj.main_menu();
            break;
        }
    }
    void display()
    {
        cin.ignore();
        system("cls");
        ifstream file;
        file.open("fact.txt");
        if (!file)
        {
            cout << "the file is not exsist" << endl;
        }
        cout << "ITEM CODE";
        spacing(21);
        cout << "ITEM NAME";
        spacing(21);
        cout << "PRICE";
        spacing(25);
        cout << "QUANTITY\n";
        for (int i = 1; i <= 100; i++)
        {
            cout << "=";
        }
        cout << endl;
        while (file.read((char *)&sct, sizeof(sct)))
        {

            cout << sct.itemcode;
            spacing(30 - strlen(sct.itemcode));
            cout << sct.itemname;
            spacing(30 - strlen(sct.itemname));
            cout << sct.itemprice;
            spacing(30 - count_digit(sct.itemprice));
            cout << sct.quantity << endl;
        }
        file.close();
        cout << "\nPress Any Key to go to menu";
        getch();
        obj.main_menu();
    }
    void idelete()
    {
        system("cls");
        cout << "\t===========================\n";
        cout << "\t\tDELETE ITEM\n";
        cout << "\t===========================\n\n";
        char itemcode[6];
        cout << "Enter item code to delete: ";
        gets(itemcode);
        fstream file;
        file.open("fact.txt", ios::in);
        ofstream tfile;
        tfile.open("tmp.txt", ios::app);
        while (file.read((char *)&sct, sizeof(sct)))
        {
            if (!strcmp(sct.itemcode, itemcode))
            {
                cout << "This item is going to be delted :" << sct.itemname;
            }
            else
            {
                tfile.write((char *)&sct, sizeof(sct));
            }
        }
        file.clear();
        file.close();
        tfile.close();
        remove("fact.txt");
        rename("tmp.txt", "fact.txt");
        cout << "\nPress Any Key to Continue";
        getch();
        obj.main_menu();
    }
    void searchitem()
    {
        system("cls");
        cout << "\t===========================\n";
        cout << "\t\tSEARCH ITEM\n";
        cout << "\t===========================\n\n";
        char itemcode[6];
        cout << "Enter item code to search: ";
        gets(itemcode);
        fstream file;
        file.open("fact.txt", ios::in);
        while (file.read((char *)&sct, sizeof(sct)))
        {
            if (strcmp(sct.itemcode, itemcode) == 0)
            {
                system("cls");
                cout << "ITEM CODE";
                spacing(21);
                cout << "ITEM NAME";
                spacing(21);
                cout << "PRICE";
                spacing(25);
                cout << "QUANTITY\n";
                for (int i = 1; i <= 100; i++)
                {
                    cout << "=";
                }
                cout << endl;
                cout << sct.itemcode;
                spacing(30 - strlen(sct.itemcode));
                cout << sct.itemname;
                spacing(30 - strlen(sct.itemname));
                cout << sct.itemprice;
                spacing(30 - count_digit(sct.itemprice));
                cout << sct.quantity << endl;
            }
        }
        file.close();
        cout << "\nPress Any Key to go to menu";
        getch();
        obj.main_menu();
    }

    void updateitembyprice()
    {
        system("cls");
        cout << "\t===========================\n";
        cout << "\t   UPDATE ITEM PRICE\n";
        cout << "\t===========================\n\n";
        char itemcode[6];
        cout << "ENTER THE ITEM CODE: ";
        cin >> itemcode;
        fstream file;
        file.open("fact.txt", ios::in | ios::out);
        while (file.read((char *)&sct, sizeof(sct)))
        {
            if (!strcmp(sct.itemcode, itemcode))
            {
                cout << "your details are:" << sct.itemcode << "    " << sct.itemname << "    " << sct.itemprice << " " << sct.quantity << endl;
                cout << "\n\n\tEnter New Price of That Product:";
                float price;
                cin >> price;
                sct.itemprice = price;
                file.seekp(size_t(file.tellg()) - sizeof(sct));
                file.write((char *)&sct, sizeof(sct));
                break;
            }
        }
        file.close();
        obj.main_menu();
    }
    void updateitembyname()
    {
        system("cls");
        cout << "\t===========================\n";
        cout << "\t   UPDATE ITEM NAME\n";
        cout << "\t===========================\n\n";
        char itemcode[6];
        cout << "ENTER THE ITEM CODE: ";
        cin >> itemcode;
        fstream file;
        file.open("fact.txt", ios::in | ios::out);
        while (file.read((char *)&sct, sizeof(sct)))
        {
            if (!strcmp(sct.itemcode, itemcode))
            {
                cout << "your details are:" << sct.itemcode << "    " << sct.itemname << "    " << sct.itemprice << " " << sct.quantity << endl;
                cout << "\n\n\tEnter New NAME of That Product:";
                char name[25];
                cin.ignore();
                gets(name);
                strcpy(sct.itemname, name);
                file.seekp(size_t(file.tellg()) - sizeof(sct));
                file.write((char *)&sct, sizeof(sct));
                break;
            }
        }
        file.close();
        obj.main_menu();
    }
    void updatebyquantity()
    {
        system("cls");
        cout << "\t===========================\n";
        cout << "\t   UPDATE ITEM QUANTITY\n";
        cout << "\t===========================\n\n";
        char itemcode[6];
        cout << "ENTER THE ITEM CODE: ";
        cin >> itemcode;
        fstream file;
        file.open("fact.txt", ios::in | ios::out);
        while (file.read((char *)&sct, sizeof(sct)))
        {
            if (!strcmp(sct.itemcode, itemcode))
            {
                cout << "your details are:" << sct.itemcode << "    " << sct.itemname << "    " << sct.itemprice << " " << sct.quantity << endl;
                cout << "\n\n\tEnter New QUantity of That Product:";
                int quantity;
                cin >> quantity;
                sct.quantity = quantity;
                file.seekp(size_t(file.tellg()) - sizeof(sct));
                file.write((char *)&sct, sizeof(sct));
                break;
            }
        }
        file.close();
        obj.main_menu();
    }
} obj1;
int main()
{
    obj.main_menu();
    return 0;
}
void menus::main_menu()
{
    system("cls");
    cout << "\t====================================================\n";
    cout << "\t\tWELCOME TO INVENTORY MANAGEMENT SYSTEM\n";
    cout << "\t====================================================\n\n";
    cout << "\t\t1. ADD AN ITEM\n";
    cout << "\t\t2. DELETE THE ITEM\n";
    cout << "\t\t3. UPDATE THE ITEM\n";
    cout << "\t\t4. SEARCH THE ITEM\n";
    cout << "\t\t5. DISPLAY ALL THE ITEMS\n";
    cout << "\t\t6. EXIT FROM APPLICATION\n";
    cout << "\t\tChoose the option: ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        obj1.additem();
        break;
    case 2:
        cin.ignore();
        obj1.idelete();
        break;
    case 3:
        cin.ignore();
        obj.update_menu();
        break;
    case 4:
        cin.ignore();
        obj1.searchitem();
        break;
    case 5:
        // cin.ignore();
        obj1.display();
        break;
    case 6:
        obj.thanks();
        break;
    default:
        cout << "Enter Valid Choice";
        Sleep(600);
        obj.main_menu();
    }
}

void menus::update_menu()
{
    system("cls");
    cout << "\t===========================\n";
    cout << "\t\tUPDATE MENU\n";
    cout << "\t===========================\n\n";
    cout << "\t\t1. Update Name\n";
    cout << "\t\t2. Update quantity\n";
    cout << "\t\t3. Update Price\n";
    cout << "\t\t4. Return\n";
    cout << "\t\tChoose the option: ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        obj1.updateitembyname();
        break;
    case 2:
        obj1.updatebyquantity();
        break;
    case 3:
        obj1.updateitembyprice();

        break;
    case 4:
        main_menu();
        break;
    }
}
