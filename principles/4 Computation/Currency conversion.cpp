/*#include <std_lib_facilities.h>

int main()
{
	const double yen_to_dollar = 122.50;
	const double euro_to_dollar = 1.0720;
	const double pound_to_dollar = 1.55;
	const double yuan_to_dollar = 0.18;
	const double kroner_to_dollar = 0.14;
	double money = 0.0;
	string moneyType = "usd";
	char type = 'X';
	cout << "Please enter the amount of money followed by the\ntype of currency (euros, yen, pounds, yuan, or kroner):\n";
	cin >> money >> moneyType;
	if (moneyType == "euros") type = 'e';
	if (moneyType == "yen") type = 'y';
	if (moneyType == "pounds") type = 'p';
	if (moneyType == "yuan") type = 'a';
	if (moneyType == "kroner") type = 'k';
	switch (type)
	{
	case 'e':
		cout << money << " Euros == $" << money / euro_to_dollar << " Dollars.\n";
		break;
	case 'y':
		cout << money << " Yen == $" << money / yen_to_dollar << " Dollars.\n";
		break;
	case 'p':
		cout << money << " Pounds == $" << money / pound_to_dollar << " Dollars.\n";
		break;
	case 'a':
		cout << money << " Yuan == $" << money * yuan_to_dollar << " Dollars.\n";
		break;
	case 'k':
		cout << money << " Kroner == $" << money * kroner_to_dollar << " Dollars.\n";
		break;
	default:
		cout << "Wrong currency type.\n";
		break;
	}

}*/