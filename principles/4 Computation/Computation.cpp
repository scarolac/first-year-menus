#include <std_lib_facilities.h>

int square(int x)
{
	int squared = 0;
	for (int i = 0; i < x; ++i)
	{
		squared += x;
	}
	return squared;
}
void makeSquares(int x)
{
	for (int i = 1; i <= x; ++i)
	{
		cout << i << "\t" << square(i) << "\n";
	}
}
void drill()
{
	vector<double> numbers;
	vector<string> units;
	double numberEntry;
	string unitEntry;
	double largest = 0;
	double smallest = 0;
	double sum = 0;
	cout << "Enter a value with units (cm, m, in, or ft): " << endl;
	while (cin >> numberEntry >> unitEntry)
	{
		if (unitEntry == "cm" || unitEntry == "m" || unitEntry == "in" || unitEntry == "ft")
		{
			numbers.push_back(numberEntry);              //push values into numbers vector
			units.push_back(unitEntry);                  //push units along side numbers
			for (size_t i = 0; i < numbers.size(); ++i)     //search through the numbers vector
			{
				//convert all inputs to meters
				if (units[i] == "cm")
					numbers[i] /= 100.0;
				if (units[i] == "in")
					numbers[i] /= 39.3700787;
				if (units[i] == "ft")
					numbers[i] /= 3.280839892;
				//set initial largest and smallest
				if (numbers.size() == 1)
				{
					largest = numbers[i];
					smallest = numbers[i];
				}
				//adjust largest and smallest if there is a change
				if (numbers.size() > 1)
				{
					if (numbers[i] < smallest) smallest = numbers[i];
					if (numbers[i] > largest) largest = numbers[i];
				}

			}
			cout << "You entered: " << numberEntry << unitEntry << endl;
			if (numberEntry == smallest && numbers.size() > 1) cout << "the smallest so far\n";
			if (numberEntry == largest && numbers.size() > 1) cout << "the largest so far\n";
		}
		//if not one of the main units, allow input again
		else
			cout << "wrong units" << endl;
	}
	//When the loop is broken, process the final request
	cout << "The values are:\n";
	//sum, sort, and post values
	sort(numbers.begin(), numbers.end());
	for (size_t j = 0; j < numbers.size(); ++j)
	{
		sum += numbers[j];
		cout << numbers[j] << " ";
	}
	//post remaining variables
	cout << "\nThe smallest value was: " << smallest << " meters" << endl
		<< "The largest value was: " << largest << " meters" << endl
		<< "The number of values was: " << numbers.size() << endl
		<< "The sum of values: " << sum << " meters" << endl;
}
void bleep()
{
	vector<string> words;
	string disliked = "Broccoli";
	string temp;
	while (cin >> temp)
	{
		words.push_back(temp);
	}
	for (size_t i = 0; i < words.size(); ++i)
	{
		if (words[i] != disliked)
			cout << words[i] << endl;
		else
			cout << "BLEEP" << endl;
	}
}
void conversion()
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
}
void Wloops()
{
	int i = 0;
	char letter = 'a';
	while (i < 26)
	{
		cout << letter << "\t" << int(letter) << "\n";
		++letter;
		++i;
	}
}
void Floops()
{
	char upper = 'A';
	char lower = 'a';
	char digits = '0';
	for (int i = 0; i < 26; ++i)
	{
		cout << upper << "\t" << int(upper) << "\t"
			<< lower << "\t" << int(lower) << "\n";
		++upper;
		++lower;

	}
	for (int i = 0; i < 10; ++i)
	{
		cout << digits << "\t" << int(digits) << "\n";
		++digits;
	}
}
bool CheckPrime(int x, vector<int> v)     //Check primes against an array containing primes
{
	for (size_t i = 0; i < v.size(); ++i) //go through the array
	{
		if (x % v[i] == 0)                //divide input number (x) by each prime on the list to determine if prime
			return false;                 //A non prime will fail this
	}
	return true;                          //assuming no non primes, return true
}
void CreatePrimes(int x, vector<int> v)   //create a list of primes until (x) is reached, storing into primes array(v)
{
	int primeNumber = 1;                  //Start at arbitrary 1, cannot do 0 since it will increment to 1 then only add that, 
	int i = 0;							  //since everything divides by 1, do this until the limit is reached (x)	
	while (i < x)           
	{
		++primeNumber;                    //increment the primenumber outside the checking if statement
		if (CheckPrime(primeNumber, v))   //check if prime, if so, push into vector, if not, next number in loop then
		{
			v.push_back(primeNumber);
			++i;                          //increment the count if a prime is found
		}
	}
	//cout << v[v.size() - 1] << endl;    //print only the requested prime
	for (size_t j = 0; j < v.size(); ++j) //or print each prime on its own line.
	{
		cout << v[j] << endl;
	}
}
int main()
{
	vector<int> primeArray;           //create primes array, no size limit 
	CreatePrimes(10001, primeArray);  //make a list of primes
}