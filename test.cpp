
//write a program to convert line data to record and print it 


#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

struct SdataClient
{
	string AccountNumber;
	string pinCode;
	string Name;
	string Phone;
	double AccountBalance;


};


vector<string> Spilt(string s1, string delim)
{
	vector<string> Vstring;
	string Sword;
	short pos=0;
	while (pos=s1.find(delim)!=std::string::npos)
	{
		Sword = s1.substr(0, pos);
		if (Sword!="")
		{
			Vstring.push_back(Sword);
		}
		s1.erase(0, pos + delim.length());
		if (s1!="")
		{
			Vstring.push_back(s1);
		}
	}
	return Vstring;
}

SdataClient ConvertLineToRecord(string s1, string seperator = "#\\#")
{
	SdataClient Client;
	vector <string> vstring;
	vstring = Spilt(s1, seperator);
	Client.AccountNumber = vstring[0];
	Client.pinCode = vstring[1];
	Client.Name = vstring[2];
	Client.Phone = vstring[3];
	Client.AccountBalance = stod(vstring[4]);

	return Client;

}

void printClientRecord(SdataClient Client)
{
	cout<< "\n\nThe following is the extracted client record:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.pinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}


int main()
{
	string stLine = "A150#//#1234#//#Mohammed Abu-Hadhoud#//#079999#//#5270.000000";
	cout << "\nLine Record is:\n"; 
	cout << stLine;
	SdataClient Client = ConvertLineToRecord(stLine);
	printClientRecord(Client);

}