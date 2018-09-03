#include <std_lib_facilities.h>

void unsafe()
{
	double d = 0;
	while (cin >> d)
	{
		int i = d;
		char c = i;
		int i2 = c;
		cout << "d == " << d
			<< " i == " << i
			<< " i2 == " << i2
			<< " char(" << c << ")\n";

	}
}
void repeated()
{
	int number_of_words = 0;
	string previous = " ";
	string current;
	while (cin >> current)
	{
		++number_of_words;
		if (previous == current)
			cout << "word number " << number_of_words
			<< " repeated word: " << current << "\n";
		previous = current;
	}
}
void numbers()
{
	cout << "Please enter a floating-point value (number with a decimal): ";
	double m;
	cin >> m;
	int n = m;
	cout << "n == " << n
		<< "\nn+1 == " << n + 1
		<< "\nthree times n == " << n * 3
		<< "\ntwice n == " << n + n
		<< "\nn squared == " << n * n
		<< "\nhalf of n == " << n / 2
		<< "\nmodulus of n/3 == " << n % 3
		<< "\nm == " << m
		<< "\nsquare root of m == " << sqrt(m)
		<< endl;
}
void names()
{
	cout << "Please enter your name and age:\n";
	string first_name = "???";  //first_name is a variable to type string
	double age = -1;            //Age
	cin >> first_name >> age;   //read characters into first_name and then age
	cout << "Hello, " << first_name << " (age " << age * 12 << " months)\n";
}
void drill()
{
	cout << "Enter the name of the person you want to write to:\n";
	string first_name = "???";
	cin >> first_name;
	cout << "Dear " << first_name << ",\n"
		<< "\tHow are you? I am fine. I miss you.\n";
	cout << "Enter the name of another friend:\n";
	string friend_name = "???";
	cin >> friend_name;
	cout << "Have you seen " << friend_name << " lately?\n";
	cout << "What is the gender of " << friend_name << "? (use m or f)\n";
	char gender = '0';
	while (cin >> gender)
	{
		if (gender == 'M' || gender == 'm' || gender == 'f' || gender == 'F')
		{
			if (gender == 'm' || gender == 'M')
			{
				cout << "If you see " << friend_name << " please ask him to call me.\n";
				break;
			}
			else
			{
				cout << "If you see " << friend_name << " please ask her to call me.\n";
				break;
			}
		}
		else
			cout << "That is not a valid gender. Try again.\n";
	}
	cout << "How old is " << friend_name << "?\n";
	int age = -1;
	while (cin >> age)
	{
		if (age < 0 || age >= 110) cout << "You are lying. Tell me again.\n";
		else
			break;
	}
	cout << "I hear you just had a birthday and you are " << age << " years old.\n";
	if (age < 12) cout << "Next year you will be " << age + 1 << ".\n";
	if (age == 17) cout << "Next year you will be able to vote.\n";
	if (age > 70) cout << "I hope you are enjoying retirement.\n";
	cout << "Yours sincerly,\n\nChris\n";
}
int main()
{
	drill();
}