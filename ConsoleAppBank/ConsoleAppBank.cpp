#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<cmath>

using namespace std;

void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
int acc_number;

class account 
{
public:
	long acno;
	char lastname[50];
	char firstname[50];
	int deposit;
	char type;
	
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of account

	account() {

	}

	account(int num) {
		acc_number = num;
	}

	// Overload << operator to display Account details.
	friend ostream &operator<<(ostream &output,
		const account &D) {


		account ac;
		bool flag = false;
		ifstream inFile;
		inFile.open("account.dat", ios::binary);
		if (!inFile)
		{
			cout << "File could not be open !! Press any Key...";
			return output;
		}
		cout << "\n----------------------------\n";
		cout << "\tBALANCE DETAILS\n";

		cout << "----------------------------\n";
		while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
		{

			if (ac.retacno() == acc_number)
			{
				ac.show_account();
				flag = true;
				cout << "\n----------------------------\n";
				cout << "\tBALANCE DETAILS\n";

				cout << "----------------------------\n";
			}
		}
		inFile.close();
		if (flag == false)
			cout << "\n-------Account number does not exist-------\n\n";

		return output;
	}
};

void account::create_account()
{
	cout << "\nEnter The Last Name : ";
	cin.ignore();
	//cin.getline(lastname, 50);
	cin >> lastname;

	cout << "Enter The First Name : ";
	cin.ignore();
	//cin.getline(firstname, 50);
	cin >> firstname;

	cout << "Enter Type of The account (C/S) : ";
	cin >> type;
	type = toupper(type);

	cout << "Enter The Initial amount( >=500 for Saving and >=1000 for current ) : ";
	cin >> deposit;

	//Code to generate random 6-digit account number

	srand(time(0));

	long int j = 0;
	j = 100000 + (rand() % 900000);

	acno = j;


	cout << "\nYour Generated Account Number : " << acno;
	cout << "\n\n---------Account Created.-----------\n\n";

}

void account::show_account() const
{
	cout << "\nAccount No. : " << acno;
	cout << "\nAccount Holder Name : " << firstname << " " << lastname;
	cout << "\nType of Account : " << type;
	cout << "\nBalance amount : " << deposit << "\n\n";
}


void account::modify()
{
	cout << "\nAccount No. : " << acno;
	cout << "\nModify Account Holder Last Name : ";
	cin.ignore();
	cin.getline(lastname, 50);

	cout << "Modify Account Holder First Name : ";
	cin.ignore();
	cin.getline(firstname, 50);

	cout << "Modify Type of Account : ";
	cin >> type;
	type = toupper(type);

	cout << "Modify Balance amount : ";
	cin >> deposit;
}

								 //THE MAIN FUNCTION OF PROGRAM
int main()
{
	char ch;
	int num;
	
	do
	{
		cout << "\n\tMAIN MENU";
		cout << "\na. Display a list of existing bank accounts";
		cout << "\nb. Add a new bank account";
		cout << "\nc. Edit an existing bank account";
		cout << "\nd. Exit the program\n\n";

		cout << "Enter your choice : ";
		cin >> ch;

		switch (ch)
		{
		case 'a':
		{
			cout << "\nEnter The account No. : "; cin >> num;
			account ac1(num);
			cout << ac1;
			break;
		}
		case 'b':
		{
			write_account();
			break;
		}
		case 'c':
		{
			cout << "\nEnter The account No. : "; cin >> num;
			modify_account(num);
			break;
		}
		case 'd':
		{
			cout << "Bye!" << endl;
			break;
		}
		default:
		{
			cout << "choice not available try again";
			break;
		}
	}
	
		cin.ignore();

	} while (ch != 'd');
	return 0;
}


//function to write in file
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//function to read specific record from file
void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n----------------------------\n";
	cout << "\tBALANCE DETAILS\n";

	cout << "----------------------------\n";
	while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
			cout << "\n----------------------------\n";
			cout << "\tBALANCE DETAILS\n";

			cout << "----------------------------\n";
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n------Account number does not exist------\n\n";
}


//    	function to modify record of file
void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\nEnter The New Details of account" << endl;
			ac.modify();
			int pos = (-1)*static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n-------Record Updated----------\n\n";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}



//    	function to deposit and withdraw amounts
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter The amount to be deposited";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal<500 && ac.rettype() == 'S') || (bal<1000 && ac.rettype() == 'C'))
					cout << "Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos = (-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}
int account::retacno() const
{
	return acno;
}
void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}
int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}