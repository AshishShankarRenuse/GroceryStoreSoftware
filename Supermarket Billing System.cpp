#include<iostream>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<fstream>
#include<windows.h>
#include<stdio.h>
#include<cstdlib>
#include<iomanip>
using namespace std;

int k=7;
COORD coord = {0,0};

void gotoxy(int column, int line)
{
  COORD coord;
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
  GetStdHandle( STD_OUTPUT_HANDLE ),
  coord
    );
}

    //***************************************************************
    // CLASS USED IN PROJECT
    //****************************************************************
    class product 
    {
    	public:
        int pno;
        char name[50];
        float price, qty, tax, dis;
        public:
        void create_product();	
                      
        void show_product() 
        {
            cout << "\nThe Product No. of The Product : " << pno;
            cout << "\nThe Name of The Product : ";
            puts(name);
            cout << "\nThe Price of The Product : " << price;
            cout << "\nDiscount : " << dis;
        }

        int retpno() 
        {
            return pno;
        }

        float retprice() 
        {
            return price;
        }

        char * retname() 
        {
            return name;
        }

        int retdis() 
        {
            return dis;
        }

    }; //class ends here

//***************************************************************
// global declaration for stream object, object
//****************************************************************

fstream fp;
product pr;
//***************************************************************
// function to write in file
//****************************************************************

void product::create_product()  
{          	
    cout<<"\n Please Enter The Product No. of The Product ";
    cin>>pno;
    cout<< "\n\nPlease Enter The Name of The Product ";
    cin>>name;
    cout<<"\nPlease Enter The Price of The Product ";
    cin>>price;
    cout << "\nPlease Enter The Discount (%) ";
    cin >> dis;     
}
void write_product() 
{ 
    fp.open("Shop.txt",ios::app);
    pr.create_product();
    fp.write((char * ) & pr, sizeof(product));
    fp.close();
    cout << "\n\nThe Product Has Been Created "; 
}
//***************************************************************
// function to read all records from file
//***************************************************************
void display_all() 
{
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.txt", ios:: in );
    while (fp.read((char * ) & pr, sizeof(product))) 
    {
        pr.show_product();
        cout << "\n\n====================================\n";
        getch();
    }
    fp.close();
    getch();
}
//***************************************************************
// function to read specific record from file
//****************************************************************
void display_sp(int n) 
{
    int flag = 0;
    fp.open("Shop.txt", ios:: in );
    while(fp.read((char * ) & pr, sizeof(product))) 
    {
        if (pr.retpno() == n) 
        {
            pr.show_product();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        cout << "\n\nRecord not exist";
    getch();
}
//***************************************************************
// function to modify record of file
//****************************************************************
void modify_product() 
{
    int no, found = 0;
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product No. of The Product";
    cin >> no;
    fp.open("Shop.txt", ios:: in | ios::out);
    while (fp.read((char * ) & pr, sizeof(product)) && found == 0) 
    {
        if (pr.retpno() == no) 
        {
            pr.show_product();
            cout << "\nPlease Enter The New Details of Product" << endl;
            pr.create_product();
            int pos = -1 * sizeof(pr);
            fp.seekp(pos, ios::cur);
            fp.write((char * ) & pr, sizeof(product));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    getch();
}
//***************************************************************
// function to delete record of file
//****************************************************************
void delete_product() 
{
    int no;
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("Shop.txt", ios:: in | ios::out);
    fstream fp2;
    fp2.open("Temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char * ) & pr, sizeof(product))) 
    {
        if (pr.retpno() != no) 
        {
            fp2.write((char * ) & pr, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.txt");
    rename("Temp.txt", "Shop.txt");
    cout << "\n\n\tRecord Deleted ..";
    getch();
}
//***************************************************************
// function to display all products price list
//****************************************************************
void garbage()
{
	remove("Shop.txt");
    fstream fp("Shop.txt");
    getch();

}
void menu() 
{
    
    fp.open("Shop.txt", ios:: in );
    if (!fp) 
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File ";
        cout << "\n\n\n Program is closing ....";
        getch();
        exit(0);
    }

    cout << "\n\n\t\tProduct MENU\n\n";
    cout << "====================================================\n";
    cout << "P.NO.\t\tNAME\t\tPRICE\n";
    cout << "====================================================\n";

    while (fp.read((char * ) & pr, sizeof(product))) 
    {
        cout << pr.retpno() << "\t\t" << pr.retname() << "\t\t" << pr.retprice() << endl;
    }
    fp.close();
}

//***************************************************************
// function to place order and generating bill for Products
//****************************************************************

void place_order() 
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';
    menu();
    cout << "\n============================";
    cout << "\n PLACE YOUR ORDER";
    cout << "\n============================\n";
    do 
    {
        cout << "\n\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        c++;
        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    
    cout << "\n\n\t\tThank You For Placing The Order";
    gotoxy(30,3);
    cout << "\n\n******************************** BILL RECEIPT ************************\n";
    
            gotoxy(3,5);
            cout<<"ITEM NO";
            gotoxy(13,5);
            cout<<"NAME";
            gotoxy(23,5);
            cout<<"PRICE";
            gotoxy(33,5);
            cout<<"QUANTITY";
            gotoxy(44,5);
            cout<<"DISCOUNT %";
            gotoxy(52,5);
            cout<<"NET AMOUNT";
    for (int x = 0; x <= c; x++) 
    {
        fp.open("Shop.txt", ios:: in );
        fp.read((char * ) & pr, sizeof(product));
        while (!fp.eof()) 
        {
            if (pr.retpno() == order_arr[x]) 
            {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdis() / 100);
				cout<<"\n";
                gotoxy(3,7);
                cout<<order_arr[x];
                gotoxy(13,k);
                cout<<pr.retname();
                gotoxy(23,k);
                cout<<pr.retprice();
                gotoxy(33,k);
                cout<<quan[x];
                gotoxy(44,k);
                cout<<pr.retdis();             
                gotoxy(52,k);
                cout<<damt;
                total += damt;
            }
            fp.read((char * ) & pr, sizeof(product));
        }

        fp.close();
    }
    cout << "\n\n\t\t\t\t\tGRAND TOTAL =Rs." << total;
    garbage();
    getch();
}

//***************************************************************
// INTRODUCTION FUNCTION
//****************************************************************

void intro() 
{   int k=6;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
    cout<<k<<"\t\t\tWelcome To The Supermarket\t\t\t\t";
    int l=2;
	HANDLE jConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(jConsole, l);
    cout<<l<<"\n\n\t\tPress an Enter Key to goto the Main Menu\t\t\t\t";
    getch();

}

//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************
void admin_menu() 
{	label:
    char ch2;
    cout << "\n\n\n\t\tADMIN MENU";
    cout << "\n\n\t1.ADD PRODUCT TO BUCKET";
    cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
    cout << "\n\n\t3.QUERY ";
    cout << "\n\n\t4.MODIFY PRODUCT";
    cout << "\n\n\t5.DELETE PRODUCT";
    cout << "\n\n\t6.VIEW PRODUCT MENU";
    cout << "\n\n\t7.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-7) ";
    ch2 = getche();
    switch (ch2) 
    {
    case '1':
        write_product();
        goto label;
        break;
    case '2':
        display_all();
        goto label;
        break;
    case '3':
        int num;
        cout << "\n\n\tPlease Enter The Product No. ";
        cin >> num;
        display_sp(num);
        goto label;
        break;
    case '4':
        modify_product();
        goto label;
        break;
    case '5':
        delete_product();
        goto label;
        break;
    case '6':
        menu();
        goto label;
        getch();
    case '7':
        break;
    default:
        cout << "\a";
        admin_menu();
    }
}
//***************************************************************
// THE MAIN FUNCTION OF PROGRAM
//****************************************************************
using namespace std;
int main() 
{
    char ch;
    intro();
    do 
    {
        cout << "\n\n\n\t\t\t\tMAIN MENU"<<endl;
        cout<<"\t\t\t\t---------";
        cout << "\n\n\t\t\t01. PLACE YOUR ORDER HERE"<<endl;
        cout << "\n\n\t\t\t02. ADMINISTRATOR"<<endl;
        cout << "\n\n\t\t\t03. EXIT"<<endl;
        cout << "\n\n\n\t\t\tPlease Select Your Option (1-3) ";
        ch = getche();
        switch (ch) 
        {
        case '1':
            place_order();
            getch();
            break;
        case '2':
            admin_menu();
            break;
        case '3':
        	garbage();
            exit(0);
        default:
            cout << "\a";
        }
    } while (ch != '3');
}

//***************************************************************
// END OF PROJECT
//***************************************************************
