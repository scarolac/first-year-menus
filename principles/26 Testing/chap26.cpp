#include <std_lib_facilities.h>


namespace test
{	
	template<class T> string my_search(vector<T>& vect, T value)
	{
		if (!vect.size()) return "Empty Vector";	
		int begin = 0;
		int end = vect.size();
		int mid = (begin + end) / 2;
		int pos = mid;

		while (vect[pos] != value)
		{
			if (vect[pos] < value)
			{
				mid = (pos + end) / 2;	//move the halfway point to the right
				begin = pos;			//move the beginning to the old mid point
			}
			else if (vect[pos] > value)
			{
				mid = (pos + begin) / 2;
				end = pos;
			}

			if (mid != pos)			//if the iterator does not change, exit, no more things to search
				pos = mid;			//start searching again in the middle
			else return "Not found";
		}
		if (vect[pos] == value)
			return to_string(pos);
		else
			return "Not found";	
	}

	template<class Iter> void print(Iter f, Iter e, const string& s)
	{
		cout << s << " : { ";
		while (f != e)
		{
			cout << *f << ' ';
			++f;
		}
		cout << "}\n";

	}

	void my_test()
	{
		vector<int> v;
		for (int i = 200; i < 600; ++i)
		{
			v.push_back(i);
		}
		print(v.begin(), v.end(), "v("+to_string(v.size())+")");


		int find;
		cout << "Input number to find: ";
		while (cin >> find)
		{
			cout << "Binary search - my_search found " << find << " at index: " << my_search(v, find) << endl;
			cout << "Input number to find: ";
		}
	}	
}

namespace notes
{
	int rand_int(int max) { return max == 0 ? 0 : rand() % max; }

	int rand_int(int min, int max) { return randint(max - min) + min; }	

	template<class T> struct Test
	{
		string label;
		T val;
		vector<T> seq;
		bool res;
	};

	template<class T> istream& operator >> (istream& is, Test<T>& t)
	{
		//temp values
		string label;
		int val;
		vector<T> seq;
		bool res;
		char ch1, ch2, ch3, ch4;

		//input up to the vector, check correct input style
		is >> ch1 >> label >> val >> ch2;
		if (!is) return is;
		if(ch1 != '{' || ch2 != '{')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		//handle the vector
		T i;
		while (is >> i)
		{
			seq.push_back(i);
		}

		//clear the input stream and start from the char to continue input, checking style
		is.clear();
		is >> ch3 >> res >> ch4;
		if (!is) return is;
		if (ch3 != '}' || ch4 != '}')
		{
			is.clear(ios_base::failbit);
			return is;
		}

		//set values
		t.label = label;
		t.val = val;
		t.seq = seq;
		t.res = res;
		return is;
	}

	template<class T> int test_all(istream& is)
	{
		int error_count = 0;
		Test<T> t;
		while (is >> t)
		{
			if (!is) throw runtime_error("problem reading from test file");
			bool r = binary_search(t.seq.begin(), t.seq.end(), t.val);
			if (r != t.res)
			{
				cout << "Failure: test " << t.label << " binary_search: " << t.seq.size()
					<< " elements, val == " << t.val << " -> " << t.res << '\n';
				++error_count;
			}
		}
		return error_count;
	}

	ostream& make_test(const string& lab, int n, int base, int spread, ostream& os)
	{
		os << "{ " << lab << " ";
		vector<int> v;
		int elem = base;
		for (int i = 0; i < n; ++i)					//make elements
		{
			elem += rand_int(spread);
			v.push_back(elem);
		}

		int val = base + rand_int(elem - base);		//make search value
		os << val << " { ";
		bool found = false;
		for (int i = 0; i < n; ++i)					//print elements and see if val is found
		{
			if (v[i] == val) found = true;
			os << v[i] << " ";
		}
		os << "} " << found << " }\n";
		return os;
	}

	void first_test_set()
	{
		string ifname1 = "drillone.txt";
		ifstream ifs1(ifname1);
		if (!ifs1) throw runtime_error("cant open " + ifname1);

		int errors = test_all<int>(ifs1);
		cout << "number of errors: " << errors << endl;

	}

	void second_test_set()
	{
		string ofname1 = "drillout.txt";
		ofstream ofs1(ofname1);
		if (!ofs1) throw runtime_error("cant open " + ofname1);

		//large sequence
		make_test("9", 10000, 0, 3, ofs1);
		ofs1.close();

		ofs1 = ofstream(ofname1, ios_base::app);
		//10 sequences with random number of elements
		for (int i = 0; i < 10; ++i)
			make_test("10." + to_string(i + 1), rand_int(50), 0, 5, ofs1);

		//10 sequences with 0-9 random elements
		for (int i = 0; i < 10; ++i)
			make_test("11." + to_string(i + 1), i, 0, 10, ofs1);

		ofs1.close();

		//test the sequences
		ifstream ifs2(ofname1);
		if (!ifs2) throw runtime_error("cant open " + ofname1);
		int errors = 0;
		errors = test_all<int>(ifs2);
		cout << "number of errors in " << ofname1 << ": " << errors << '\n';

		//test strings
		string ifname2 = "drilltwo.txt";
		ifstream ifs3(ifname2);
		if (!ifs3) throw runtime_error("cant open " + ifname2);
		errors = test_all<string>(ifs3);
		cout << "number of errors in " << ifname2 << ": " << errors << '\n';
		
	}

}

int main()
{
	try
	{
		
		notes::second_test_set();

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