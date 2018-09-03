#include <std_lib_facilities.h>
#include <numeric>
#include <map>
#include <set>
#include <iterator>

namespace notes
{
	template<class In, class T> In find(In first, In last, const T& val)
	{
		while (first != last && *first != val)++first;
		return first;
	}

	//searchs until pred(*first) succeeds, a predicate returns true/false
	template<class In, class Pred> In find_if(In first, In last, Pred pred)
	{
		while (first != last && !pred(*first))++first;
		return first;
	}

	bool odd(int x) { return x % 2; }

	bool larger_than_42(int x) { return x > 42; }

	//find_if takes a bool function and check each iterator against it

	//Function object - creates an object that acts like a function
	class Larger_than
	{
		int v;
	public:
		Larger_than(int vv) : v(vv) {}
		bool operator()(int x) { return x > v; }
	};

	/*
	class F		//abstract of a function object
	{
	S s;	//state
	public:
	F(const S& ss) : s(ss) {}
	T operator()(const S& ss) const
	{
	//do something with ss to s
	//retrun a value of type T(void, bool or S)
	}

	const S& state() const {retrun s;}	//reveal state
	void reset(const S& ss){s = ss;}	//reset state
	};
	*/

	struct Record
	{
		string name;
		char addr[24];
	};

	struct Cmp_by_name
	{
		bool operator()(const Record& a, const Record& b) const { return a.name < b.name; }
	};

	struct Cmp_by_addr
	{
		bool operator()(const Record& a, const Record& b) const { return strncmp(a.addr, b.addr, 24) < 0; }
		//strncmp compares two fixed length char arrays
	};

	vector<Record> vr;

	/*
	can be sorted by name and addr
	sort(vr.begin(), vr.end(), Cmp_by_name());
	sort(vr.begin(), vr.end(), Cmp_by_addr());
	*/

	//Accumulate - adds sequence of values, iterates from first to last, returns the same type as the init (initial value)
	template<class In, class T> T accumulate(In first, In last, T init)
	{
		while (first != last)
		{
			init = init + *first;
			+first;
		}
		return init;
	}
	//Accumulate - 4 arg version, can plus, minus, multiplies, divides, and modulus from <functional>
	//use: multiplies<double>() or plus<int>()
	//can take functions with two arguments, the first being the initial value, the second being the iterator
	template<class In, class T, class BinOp> T accumulate(In first, In last, T init, BinOp op)
	{
		while (first != last)
		{
			init = op(init, *first);
			+first;
		}
		return init;
	}

	/*	inner_product()

		takes two sequences, multiplies the pairs of elements, adds the sums
	*/
	template<class In, class In2, class T> T inner_product(In first, In last, In2 first2, T init)
	{
		while (first != last)
		{
			init = init + (*first) * (*first2);
			++first;
			++first2;
		}
		return init;
	}

	/*	map
	
		ordered sequence of (key,value) pairs, like a phone_book["Nicholas"] would return the phone number for Nicholas
		left->first < first && first < right->first
		maps organize by building a tree from the middle allowing for faster search
		unordered_map is optimized for keys that are strings, and do not go in order

		aka-> associative arrays, hash tables, red-black trees
	*/
	void map_test()
	{
		map<string, int> words;

		string s;
		while (cin >> s) ++words[s];

		typedef map<string, int>::const_iterator Iter;
		for (Iter p = words.begin(); p != words.end(); ++p)
			cout << p->first << ": " << p->second << endl;
	}

	/*	set
		it is a map without the value
		has to use insert and erase since the set/map decides where the data goes, not the programmer
	*/	
	
	//copy is as simple as find(), but copies the data into another sequence
	//types can be different, since it iterates through pointers
	//check output size before trying to stuff something too large into it
	template<class In, class Out> Out copy(In first, In last, Out res)
	{
		while (first != last)
		{
			*res = *first; //copy element
			++res;
			++first;
		}
		return res;
	}

	//can be used to copy to input and output
	/*
	ostream_iterator<string> oo(cout);	//assigning to *oo is writing to cout

	*oo = "Hello, ";	//same as: cout << "Hello, "
	++oo;				//get ready for the next output operation (so another <<)
	*oo = "World!\n";	//same as cout << "World!\n"
	*/

	/*
	istream_iterator<string> ii(cin);	//reading *ii reads a string from cin

	string s1 = *ii;	//same as cin >> s1;
	++ii;				//next >>
	string s2 = *ii;	//same as cin >> s2;
	*/

	void copy_files()
	{
		string from, to;						//get source and target file names
		cout << "Enter input file name, then output file name: ";
		cin >> from >> to;

		ifstream is(from.c_str());				//open input stream with file name as a c string
		ofstream os(to.c_str());

		istream_iterator<string> ii(is);		//make input iterator for istream
		istream_iterator<string> eos;			//input end of file
		ostream_iterator<string> oo(os, "\n");	//make output iterator, "\n" makes a new line after each word, " " would separate by space

		vector<string> b(ii, eos);				//b is vector from ii to eos, same as [ii:eos)
		sort(b.begin(), b.end());				//sort the buffer
		std::copy(b.begin(), b.end(), oo);		//copy buffer to output, unique_copy would cut duplicate words out
	}

	/*
		copy_if() similar to find_if, copies only if a predicate is true
	*/

	template<class In, class Out, class Pred> Out copy_if(In first, In last, Out res, Pred p)
	{
		while (first != last)
		{
			if (p(*first)) *res++ = *first;	//checks predicate true, sets *first to *res, then increments res - predicate like the Larger_than one from above
			++first;
		}
		return res;
	}

	//a binary search can only be performed on sorted data, since it assumes it is sorted.
	//sort can have or not have a comparison case
	//binary_search needs begin, end, and the value we are searching for
}

namespace try_
{
	struct Record
	{
		Record(double up, int un) : unit_price(up), units(un) {}
		double unit_price;
		int units;
	};

	struct Profit
	{
		double operator()(double v, const Record& r) { return v + r.units * r.unit_price; }
	};

	void f(const vector<Record>& vr)
	{
		double total = accumulate(vr.begin(), vr.end(), 0.0, Profit());
		cout << "Total is $" << total << endl;
	}

	void this1()
	{
		Record rec1 = Record(10.9, 15);
		Record rec2 = Record(25.5, 3);
		Record rec3 = Record(101, 75);
		Record rec4 = Record(5.33, 27);
		vector<Record> vr;
		vr.push_back(rec1);
		vr.push_back(rec2);
		vr.push_back(rec3);
		vr.push_back(rec4);
		f(vr);
	}

	double weighted_value(const pair<string, double>& a, const pair<string, double>& b)
	{
		return a.second*b.second;
	}

	void this2()
	{
		map<string, double> dow_price;
		dow_price["MMM"] = 81.86;
		dow_price["AA"] = 34.69;
		dow_price["MO"] = 54.45;
		dow_price["AXP"] = 90.44;
		dow_price["T"] = 32.67;
		dow_price["BA"] = 125.06;
		dow_price["CAT"] = 89.75;
		dow_price["CVX"] = 106.02;

		//alternate way to create a map
		map<string, double> dow_weight;
		dow_weight.insert(make_pair("MMM", 5.8549));
		dow_weight.insert(make_pair("AA", 2.4808));
		dow_weight.insert(make_pair("MO", 3.8940));
		dow_weight.insert(make_pair("AXP", 3.35));
		dow_weight.insert(make_pair("T", 1.21));
		dow_weight.insert(make_pair("BA", 4.63));
		dow_weight.insert(make_pair("CAT", 3.32));
		dow_weight.insert(make_pair("CVX", 3.92));

		map<string, string> dow_name;
		dow_name["MMM"] = "3M Co.";
		dow_name["AA"] = "Alcoa Inc.";
		dow_name["MO"] = "Altria Group Inc.";
		dow_name["AXP"] = "American Express";
		dow_name["T"] = "AT&T";
		dow_name["BA"] = "Boeing";
		dow_name["CAT"] = "Caterpillar";
		dow_name["CVX"] = "Chevron";

		double alcoa_price = dow_price["AA"];

		//to find something in the dow
		if (dow_price.find("MO") != dow_price.end()) cout << "Altria is in the Dow" << endl;

		//iterator through a map with key = first, and the value = second
		typedef map<string, double>::const_iterator Dow_iterator;

		//write price for each company
		for (Dow_iterator p = dow_price.begin(); p != dow_price.end(); ++p)
		{
			const string& symbol = p->first;
			const double& price = p->second;
			cout << symbol << '\t' << price << '\t' << dow_name[symbol] << endl;
		}

		double dji_index = inner_product(dow_price.begin(), dow_price.end(), dow_weight.begin(), 0.0, plus<double>(), weighted_value);

		cout << "\nDJI index is " << dji_index << "\n";
	}

	//unordered map builds a hash table and throws all the values together, not ordered, runs faster 
	void this3()
	{
		unordered_map<string, double> dow_price;
		dow_price["MMM"] = 81.86;
		dow_price["AA"] = 34.69;
		dow_price["MO"] = 54.45;
		dow_price["AXP"] = 90.44;
		dow_price["T"] = 32.67;
		dow_price["BA"] = 125.06;
		dow_price["CAT"] = 89.75;
		dow_price["CVX"] = 106.02;

		//alternate way to create a map
		unordered_map<string, double> dow_weight;
		dow_weight.insert(make_pair("MMM", 5.8549));
		dow_weight.insert(make_pair("AA", 2.4808));
		dow_weight.insert(make_pair("MO", 3.8940));
		dow_weight.insert(make_pair("AXP", 3.35));
		dow_weight.insert(make_pair("T", 1.21));
		dow_weight.insert(make_pair("BA", 4.63));
		dow_weight.insert(make_pair("CAT", 3.32));
		dow_weight.insert(make_pair("CVX", 3.92));

		unordered_map<string, string> dow_name;
		dow_name["MMM"] = "3M Co.";
		dow_name["AA"] = "Alcoa Inc.";
		dow_name["MO"] = "Altria Group Inc.";
		dow_name["AXP"] = "American Express";
		dow_name["T"] = "AT&T";
		dow_name["BA"] = "Boeing";
		dow_name["CAT"] = "Caterpillar";
		dow_name["CVX"] = "Chevron";

		//iterator through a map with key = first, and the value = second
		typedef unordered_map<string, double>::const_iterator Dow_iterator;

		//write price for each company
		for (Dow_iterator p = dow_price.begin(); p != dow_price.end(); ++p)
		{
			const string& symbol = p->first;
			const double& price = p->second;
			cout << symbol << '\t' << price << '\t' << dow_name[symbol] << endl;
		}

		double dji_index = inner_product(dow_price.begin(), dow_price.end(), dow_weight.begin(), 0.0, plus<double>(), weighted_value);

		cout << "\nDJI index is " << dji_index << "\n";
	}

	void this_set()
	{
		string from, to;						//get source and target file names
		cout << "Enter input file name, then output file name: ";
		cin >> from >> to;

		ifstream is(from.c_str());				//open input stream with file name as a c string
		ofstream os(to.c_str());

		istream_iterator<string> ii(is);		//make input iterator for istream
		istream_iterator<string> eos;			//input end of file
		ostream_iterator<string> oo(os, "\n");	//make output iterator, "\n" makes a new line after each word, " " would separate by space

		std::set<string> b(ii, eos);				//b is vector from ii to eos, same as [ii:eos)
		std::copy(b.begin(), b.end(), oo);		//copy buffer to output, unique_copy would cut duplicate words out
	}
}

struct item
{
	string name;
	int iid;
	double value;
	item() : name(), iid(0), value(0.0)	{}
	item(string n, int i, double v) : name(n), iid(i), value(v)	{}
};

istream& operator >> (istream& is, item& it)
{
	string name;
	int iid;
	double value;
	is >> name >> iid >> value;
	if (!is) return is;
	it = item(name, iid, value);
	return is;
}

ostream& operator << (ostream& os, item& it)
{
	return os << it.name << '\t' << it.iid << '\t' << it.value;
}

struct cmp_by_name
{
	bool operator()(const item& a, const item& b) const
	{
		return a.name < b.name;
	}
};

struct cmp_by_iid
{
	bool operator()(const item& a, const item& b)
	{
		return a.iid < b.iid;
	}
};

bool cmp_by_value(const item& a, const item& b)
{
	return a.value < b.value;
}

class find_by_name
{
	string name;
public:
	find_by_name(const string& s) : name(s)	{}
	bool operator()(const item& it) const { return it.name == name; }
};

class find_by_iid
{
	int iid;
public:
	find_by_iid(int i) : iid(i) {}
	bool operator()(const item& it) const { return it.iid == iid; }
};

template<class iter> void print(iter first, iter last)
{
	while (first != last)
	{
		cout << *first << '\n';
		++first;
	}
}

//2.5
void read_pair(map<string, int>& msi)
{
	string s;
	int i;
	cin >> s >> i;
	if (!cin) error("Problem reading from cin");
	msi[s] = i;
}

template<class T, class U> ostream& operator << (ostream& os, const pair<T, U>& p)
{
	os << setw(12) << left << p.first << '\t' << p.second;
	return os;
}

template<class T> struct Map_add
{
	T operator()(T v, const pair<string, T>& p) { return v + p.second; }
};

template<class T> class less_than
{
	T v;
public:
	less_than(T val) : v(val)	{}
	bool operator()(T x) const { return x < v; }
};

void drill_vector()
{
	cout << "Vector Drill:\n";
	vector<item> vi;
	const string ifname = "items.txt";

	//1.1
	cout << "1.1 fill with ten items from file\n";
	{
		ifstream ifs(ifname.c_str());
		if (!ifs) error("cant open ", ifname);
		item i;
		while (ifs >> i) vi.insert(vi.end(), i);
	}
	print(vi.begin(), vi.end());

	//1.2 - sort by name
	cout << "\n1.2 sort by name\n";
	sort(vi.begin(), vi.end(), cmp_by_name());
	print(vi.begin(), vi.end());

	//1.3 - sort by iid
	cout << "\n1.3 sort by iid\n";
	sort(vi.begin(), vi.end(), cmp_by_iid());
	print(vi.begin(), vi.end());

	//1.4 - sort by value
	cout << "\n1.4 sort by value - largest on top\n";
	sort(vi.begin(), vi.end(), cmp_by_value);
	reverse(vi.begin(), vi.end());
	print(vi.begin(), vi.end());

	//1.5 - insert two items
	cout << "\n1.5 insert two items\n";
	vi.insert(vi.end(), item("HorseSh", 99, 12.34));
	vi.insert(vi.end(), item("C S400", 9988, 499.95));
	sort(vi.begin(), vi.end(), cmp_by_value);
	reverse(vi.begin(), vi.end());
	print(vi.begin(), vi.end());

	//1.6 - erase two items by name
	cout << "\n1.6 erase two items by name\n";
	vector<item>::iterator iter = find_if(vi.begin(), vi.end(), find_by_name("Xbox"));
	vi.erase(iter);
	iter = find_if(vi.begin(), vi.end(), find_by_name("GoPro"));
	vi.erase(iter);
	print(vi.begin(), vi.end());

	//1.7 - erase two items by iid
	cout << "\n1.7 erase two items by iid\n";
	iter = find_if(vi.begin(), vi.end(), find_by_iid(14910));
	vi.erase(iter);
	iter = find_if(vi.begin(), vi.end(), find_by_iid(754));
	vi.erase(iter);
	print(vi.begin(), vi.end());

}

void drill_list()
{
	cout << "List Drill:\n";
	list<item> li;
	const string ifname = "items.txt";

	//1.8.1
	cout << "1.8.1 fill with ten items from file\n";
	{
		ifstream ifs(ifname.c_str());
		if (!ifs) error("cant open ", ifname);
		item i;
		while (ifs >> i) li.insert(li.end(), i);
	}
	print(li.begin(), li.end());

	//1.8.2 - sort by name
	cout << "\n1.8.2 sort by name\n";
	li.sort(cmp_by_name());
	print(li.begin(), li.end());

	//1.8.3 - sort by iid
	cout << "\n1.8.3 sort by iid\n";
	li.sort(cmp_by_iid());
	print(li.begin(), li.end());

	//1.8.4 - sort by value
	cout << "\n1.8.4 sort by value - largest on top\n";
	li.sort(cmp_by_value);
	reverse(li.begin(), li.end());
	print(li.begin(), li.end());

	//1.8.5 - insert two items
	cout << "\n1.8.5 insert two items\n";
	li.insert(li.end(), item("HorseSh", 99, 12.34));
	li.insert(li.end(), item("C S400", 9988, 499.95));
	li.sort(cmp_by_value);
	reverse(li.begin(), li.end());
	print(li.begin(), li.end());

	//1.8.6 - erase two items by name
	cout << "\n1.8.6 erase two items by name\n";
	list<item>::iterator iter = find_if(li.begin(), li.end(), find_by_name("Xbox"));
	li.erase(iter);
	iter = find_if(li.begin(), li.end(), find_by_name("GoPro"));
	li.erase(iter);
	print(li.begin(), li.end());

	//1.8.7 - erase two items by iid
	cout << "\n1.8.7 erase two items by iid\n";
	iter = find_if(li.begin(), li.end(), find_by_iid(14910));
	li.erase(iter);
	iter = find_if(li.begin(), li.end(), find_by_iid(754));
	li.erase(iter);
	print(li.begin(), li.end());
}

void drill_map()
{
	//2.1
	cout << "\nMap test time\n";
	map<string, int> msi;

	//2.2
	msi["lecture"] = 21;
	msi["university"] = 35;
	msi["education"] = 15;
	msi["school"] = 99;
	msi["kindergarten"] = 105;
	msi["river"] = 5;
	msi["city"] = 10;
	msi["capital"] = 70;
	msi["software"] = 88;
	msi["hardware"] = 43;

	//2.3
	cout << "\n2.3 print values\n";
	print(msi.begin(), msi.end());

	//2.4
	cout << "\n2.4 erase a name\n";
	typedef map<string, int>::const_iterator MI;
	MI p = msi.begin();
	while (p != msi.end()) p = msi.erase(p);
	cout << "size of map after deleting: " << msi.size() << endl;

	//2.6 read input
	cout << "\n2.5 read in pairs\n";
	cout << "Enter 10 (string,int) pairs, separated by space:\n";
	for (int i = 0; i < 10; ++i) read_pair(msi);

	//2.7
	cout << "\nThe pairs entered:\n";
	print(msi.begin(), msi.end());

	//2.8
	int msi_sum = 0;
	msi_sum = accumulate(msi.begin(), msi.end(), msi_sum, Map_add<int>());
	cout << "\nSum of all ints in msi: " << msi_sum << endl;

	//2.9
	map<int, string> mis;

	//2.10
	for (p = msi.begin(); p != msi.end(); ++p) mis[p->second] = p->first;

	//2.11
	cout << "\n2.11 Contents of mis:\n";
	print(mis.begin(), mis.end());
}

void drill_vector_again()
{
	cout << "3. Vector floating point values\n";
	vector<double> vd;
	const string ifname = "values.txt";

	//3.1 read values into vd from a file
	ifstream ifs(ifname.c_str());
	if (!ifs) error("cant open ", ifname);
	double d;
	while (ifs >> d) vd.push_back(d);

	//3.2
	cout << "vd:\n";
	print(vd.begin(), vd.end());

	//3.3
	vector<int> vi(vd.size());
	copy(vd.begin(), vd.end(), vi.begin());

	//3.4
	cout << "\n(vd,vi) pairs:\n";
	for (int i = 0; i < vd.size(); ++i) cout << '(' << vd[i] << ',' << vi[i] << ")\n";
	
	//3.5
	double sum = 0;
	sum = accumulate(vd.begin(), vd.end(), sum);
	cout << "\nSum of the elements of vd: " << sum << endl;

	//3.6
	int sum_vi = 0;
	sum_vi = accumulate(vi.begin(), vi.end(), sum_vi);
	cout << "\nDifference of sum of vd and sum_vi: " << sum - sum_vi << endl;

	//3.7
	reverse(vd.begin(), vd.end());
	cout << "\nvd after reverse:\n";
	print(vd.begin(), vd.end());

	//3.8
	double vd_mean = sum / vd.size();
	cout << "\nmean of vd: " << vd_mean << endl;

	//3.9
	vector<double> vd2(count_if(vd.begin(), vd.end(), less_than<double>(vd_mean)));
	copy_if(vd.begin(), vd.end(), vd2.begin(), less_than<double>(vd_mean));
	cout << "\nvd2:\n";
	print(vd2.begin(), vd2.end());

	//3.10
	sort(vd.begin(), vd.end());
	cout << "\nvd:\n";
	print(vd.begin(), vd.end());
}


int main()
{
	try
	{
		drill_vector();

		drill_list();

		drill_map();

		drill_vector_again();

		keep_window_open();
		return 0;
	}
	catch (Range_error& re)
	{
		cerr << "Error: " << re.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		keep_window_open("~~");
		return 2;
	}
	catch (...)
	{
		cerr << "Error unknown" << endl;
		keep_window_open("~~");
		return 3;
	}
}