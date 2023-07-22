#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>
using namespace std;
class Bank_Account_Info
{
    private:
    int account_no;
    char name[100];
    char type;    // S is for saving, C is for current.
    char gender; //F for female : M for male : N for other.
    int currentMoney;
    public:
    int retacno() const{
        return account_no;
    }
    void depos(int x)
    {
        currentMoney+=x;
    }
    void draw(int x)
    {
        currentMoney -=x;
    }
    int retdeposit() const{
        return currentMoney;
    }
     
    void create_new_account();
    void display();
   
};
    void write_account();
    void display_info(int);
    void delete_account(int);
    void money_d_w(int,int);

void Bank_Account_Info::create_new_account()
{
    system("cls");
    cout<<"\t Please enter the required details"<<endl;
    cout<<"\t----------------------------------"<<endl;
    cout<<"\tEnter the Account Number(6-digit code):  ";
    cin>>account_no; 
    cout<<endl;
    cout<<"\tName of the account holder: ";
    cin>>name; 
    cout<<endl;
    cout<<"\tEnter your gender - M/F : ";
    cin>>gender; 
    gender=toupper(gender); 
    cout<<endl;
    cout<<"\tAnd we are almost there!"<<endl;
    cout<<"\tPlease select the type of account you want - C/S: ";
    cin>>type; 
    type=toupper(type); 
    cout<<endl;
    cout<<"\t IMP: Please note that the amount should be >=1000 for saving account and >=2000 for current account"<<endl;
    cout<<endl;
    cout<<"\t ENTER THE INITIAL AMOUNT: ";
    cin>>currentMoney;
    cout<<endl;
    cout<<"\t\t Congralutions! Your account is created successfully"<<endl;
}

void Bank_Account_Info::display()
{
    cout<<"Here are your details"<<endl;
     cout<<"-----------------------------------"<<endl;
    cout<<"\t PERSONAL INFORMATION:    "<<endl;
    cout<<"Bank Account Number:     "<<account_no<<endl;
    cout<<"Account Holder's Name:   "<<name<<endl;
    cout<<"Gender:                  "<<gender<<endl;
    cout<<"\t ACCOUNT INFORMATION      "<<endl;
    cout<<"Type of account:         "<<type<<endl;
    cout<<"Current balanced amount: "<<currentMoney<<endl;
}

int main()
{
    char ch;
    int num;
    do {
    cout<<"\t\t--------------------------------------------------------------------------------\t\t"<<endl;
    cout<<"\t\t Welcome to Serenity Savings Banks - Your Financial Journey, Our Trusted Guidance"<<endl;
    cout<<"\t\t--------------------------------------------------------------------------------\t\t"<<endl;
    cout<<"\t\t Select the operation of your choice by entering the number \t\t"<<endl;
    cout<<endl;
    cout<<"\t Main Menu \t\t"<<endl;
    cout<<"\t 1.Create an Account"<<endl;
    cout<<"\t 2.Deposit my money"<<endl;
    cout<<"\t 3.Withdraw my money"<<endl;
    cout<<"\t 4.Display account information"<<endl;
    cout<<"\t 5.Close my account"<<endl;
    cout<<"\t 6.Exit"<<endl;
    cout<<endl;
    cout<<"\t\t--------------------------------------------------------------------------------\t\t"<<endl;
    cout<<endl;
    cout<<"\t ENTER YOUR CHOICE-(1-6): ";
    cin>>ch;
    cout<<endl;
    switch (ch)
    {
    case '1': //new account
         write_account();
        break;
    case '2': // deposit
    system("cls");
    cout<<"\t Enter your account number: ";
    cin>>num;
    money_d_w(num,1); // Money deposite and withdraw together- there working is same.
    break;          //1 means deposite and 2 means withdrawal

    case '3': //withdraw
    system("cls");
    cout<<"\t Enter your account number: ";
    cin>>num;
    money_d_w(num,2);
    break;

    case '4': //displaying account details
    system("cls");
    cout<<"\t Enter your account number: ";
    cin>>num;
    display_info(num); //display information
    break;

    case '5': //close my account
    system("cls");
    cout<<"\t Enter your account number: ";
    cin>>num;
    delete_account(num);  // function for delecting
    break;
     case '6': //exit
     cout<<"\t Thank you so much for using my Bank Management System!"<<endl;
    break;
    }
    
    cin.ignore();
    cin.get();
    } 
    while(ch!='6');
   
    return 0;
}

void write_account() //function to write record in binary file
{
    Bank_Account_Info ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_new_account();
    outFile.write(reinterpret_cast<char*>(&ac),sizeof(Bank_Account_Info));
    outFile.close();
}

void delete_account(int n)
{
     Bank_Account_Info ac;
     ifstream inFile;     // input file
     ofstream outFile;   //output file
     inFile.open("account.dat",ios::binary);
     if(!inFile)
     {
        cout<<"File could not be opened!! Press any key";
        return;
     }
     outFile.open("Temp.dat",ios::binary);
     inFile.seekg(0,ios::beg);
     //we will read the file and then check
     while(inFile.read(reinterpret_cast<char*>(&ac),sizeof(Bank_Account_Info)))
     {
        if(ac.retacno()!=n) // return account number
        {
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(Bank_Account_Info));
        }
     }
     inFile.close();
     outFile.close();
     remove("Bank_Account_info");
     rename("Temp.dat","Bank_Account.dat");
     cout<<"Account deleted"<<endl; 
     return;
}

void display_info(int n)
{
    Bank_Account_Info ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be opened !! Press any key";
        return;
    }
    cout<<"\t Bank Account Details"<<endl;
    while (inFile.read(reinterpret_cast<char*>(&ac),sizeof(Bank_Account_Info)))
    {
        if(ac.retacno()==n)
        {
            ac.display();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
    {
        cout<<"Account does not exist.Please try with a valid account number"<<endl;
    }
}

void money_d_w(int n,int select)
{
     int amt;
     bool found=false; 
     Bank_Account_Info ac;
     fstream File;
     File.open("account.dat",ios::binary|ios::in|ios::out);
     if(!File)
     {
        cout<<"File does not exist. Press any key to continue";
        cout<<endl;
        return;
     }
     while(!File.eof() && found==false)
     {
        File.read(reinterpret_cast<char*>(&ac), sizeof(Bank_Account_Info));
        if(ac.retacno()==n) // if the account number exists
        {
            ac.display();
            if(select==1)
            {
                cout<<"Enter the amount of money you want to deposite: ";
                cin>>amt;
                ac.depos(amt);
                cout<<endl;
            }
            if(select==2)
            {
                cout<<"Enter the amount you want to withdraw: ";
                cin>>amt;
                int balance = ac.retdeposit()-amt;
                if(balance<0)
                {
                    cout<<"Sorry,Insufficient Balance in your account.You can not withdraw"<<endl;
                }
                else 
                {
                    ac.draw(amt);
                }

            }
            int pos = (-1)*static_cast<int>(sizeof(Bank_Account_Info));
            File.seekp(pos,ios::cur); //moving the pointer to the position of the file
            File.write(reinterpret_cast<char*>(&ac),sizeof(Bank_Account_Info));
            cout<<"\t Record Updated"<<endl;
            found=true;
        }
     }
     File.close();
     if(found==false)
     {
        cout<<"\t Error: Account does not exist"<<endl;
     }
}