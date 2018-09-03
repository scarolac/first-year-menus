#include <std_lib_facilities.h>

namespace trythis7
{
	void ch_func(const char ac[])
	{
		//get length
		cout << "Length of ch[]: " << strlen(ac) << endl;

		//compare to Hello
		if (strcmp(ac, "Hello") == 0) cout << "ch == \"Hello\"" << endl;

		//compare to Howdy
		int comp = strcmp(ac, "Howdy");
		switch (comp)
		{
		case -1:
			cout << "ch < \"Howdy\"" << endl;
			break;
		case 0:
			cout << "ch == \"Howdy\"" << endl;
			break;
		case 1:
			cout << "ch > \"Howdy\"" << endl;
			break;
		default:
			error("Illegal value");
		}

		//copy into another
		char ac_cp[6];
		for (int i = 0; i < strlen(ac); ++i)
		{
			ac_cp[i] = ac[i];
		}
		cout << "Copy is now " << ac_cp << endl;
	}

	template<class T> int cmp_to_str(const T& lhs, const string& rhs)	//compares any type to a string
	{
		int i = 0;

		if (lhs.size() < rhs.size()) return -1;
		if (lhs.size() > rhs.size()) return 1;

		for (typename T::const_iterator p = lhs.begin(); p != lhs.end() && i < rhs.size(); ++p)
		{
			if (*p < rhs[i]) return -1;
			if (*p > rhs[i]) return 1;
			++i;
		}
		return 0;
	}

	void vch_func(const vector<char>& vc)
	{
		//get length
		cout << "Length of vch: " << vc.size() << endl;

		//compare to "Hello"
		if (cmp_to_str(vc, "Hello") == 0) cout << "vch == \"Hello\"" << endl;

		//compare to "Howdy"
		int comp = cmp_to_str(vc, "Howdy");
		switch (comp)
		{
		case -1:
			cout << "vch < \"Howdy\"" << endl;
			break;
		case 0:
			cout << "vch == \"Howdy\"" << endl;
			break;
		case 1:
			cout << "vch > \"Howdy\"" << endl;
			break;
		default:
			error("Illegal value");
		}

		//copy to another
		vector<char> vc_cp = vc;
	}

	void lc_func(const list<char>& lc)
	{
		cout << "Length of lc: " << lc.size() << "\n";

		if (cmp_to_str(lc, "Hello") == 0) cout << "lc == \"Hello\"\n";

		int comp = cmp_to_str(lc, "Howdy");
		switch (comp) {
		case -1:
			cout << "lc < \"Howdy\"\n";
			break;
		case 0:
			cout << "lc == \"Howdy\"\n";
			break;
		case 1:
			cout << "lc > \"Howdy\"\n";
			break;
		default:
			error("Illegal value");
		}

		list<char> lc_cp = lc;
	}

	void sc_func(const string& sc)
	{
		cout << "Length of sc: " << sc.size() << "\n";
		if (sc == "Hello") cout << "sc == \"Hello\"\n";
		if (sc<"Howdy") cout << "sc < \"Howdy\"\n";
		string sc_cp = sc;
	}

	void try_this()
	{
		//make a char, vectro<char> list<char> and string of "Hello"
		//send to a function that:
		//	write out the number of characters
		//	compare to "Hello" to verify correctness
		//	compare to "Howdy" for abc order
		//	copy into another variable of the same type

		char ch[] = "Hello";
		ch_func(ch);
		cout << endl;

		vector<char> vch;
		vch.push_back('H');
		vch.push_back('e');
		vch.push_back('l');
		vch.push_back('l');
		vch.push_back('o');
		vch_func(vch);

		list<char> lch;
		lch.push_back('H');
		lch.push_back('e');
		lch.push_back('l');
		lch.push_back('l');
		lch.push_back('o');
		lc_func(lch);

		string strch = "Hello";
		sc_func(strch);


	}
}

namespace trythis8
{
	void ai_func(const int ai[], int sz)
	{
		cout << "Number of elements in ai: " << sz << "\n";
	}

	void vi_func(const vector<int>& vi)
	{
		cout << "Number of elements in vi: " << vi.size() << "\n";
	}

	void li_func(const list<int>& li)
	{
		cout << "Number of elements in li: " << li.size() << "\n";
	}

	void try_this()
	{
		int ai[] = { 1, 2, 3, 4, 5 };
		ai_func(ai, sizeof(ai) / sizeof(*ai));

		vector<int> vi;
		for (int i = 1; i<6; ++i) vi.push_back(i);
		vi_func(vi);

		list<int> li;
		for (int i = 1; i<6; ++i) li.push_back(i);
		li_func(li);
	}
}

template<class T, int N> struct new_array
{
	typedef T value_type;
	typedef T* iterator;
	typedef T* const_iterator;
	typedef unsigned int size_type;

	T elems[N];

	iterator begin() { return elems; }
	const_iterator begin() const { return elems; }
	iterator end() { return elems + N; }
	const_iterator end() const { return elems + N; }

	size_type size() const { return N; }

	T& operator[](int n) { return elems[n]; }
	const T& operator[](int n) const { return elems[n]; }

	const T& at(int n) const;	//range checked access
	T& at(int n);

	T* data() { return elems; }
	const T* data() const { return elems; }
};

template<class Iter1, class Iter2> void my_copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	if (f1 == e1) return;
	while (f1 != e1)
	{
		*f2 = *f1;
		++f1;
		++f2;
	}
}

template<class Iter> void print(Iter f, Iter e, const string& s)
{
	cout << s << ": { ";
	while (f != e)
	{
		cout << *f << ' ';
		++f;
	}
	cout << "}\n";
}

void drill()
{
	//1
	const int sz = 10;
	new_array<int, sz> ai;
	for (int i = 0; i < ai.size(); ++i) ai[i] = i;
	print(ai.begin(), ai.end(), "ai");

	//2
	vector<int> vi;
	for (int i = 0; i < sz; ++i) vi.push_back(i);
	print(vi.begin(), vi.end(), "vi");

	//3
	list<int> li;
	for (int i = 0; i < sz; ++i) li.push_back(i);
	print(li.begin(), li.end(), "li");

	//4
	new_array<int, sz> ai_copy = ai;
	print(ai_copy.begin(), ai_copy.end(), "ai_copy");
	vector<int> vi_copy = vi;
	print(vi_copy.begin(), vi_copy.end(), "vi_copy");
	list<int> li_copy = li;
	print(li_copy.begin(), li_copy.end(), "li_copy");

	//5
	for (new_array<int, sz>::iterator p = ai.begin(); p != ai.end(); ++p) *p += 2;
	print(ai.begin(), ai.end(), "ai += 2");
	for (vector<int>::iterator p = vi.begin(); p != vi.end(); ++p) *p += 3;
	print(vi.begin(), vi.end(), "vi += 3");
	for (list<int>::iterator p = li.begin(); p != li.end(); ++p) *p += 5;
	print(li.begin(), li.end(), "li += 5");

	//7
	my_copy(ai.begin(), ai.end(), vi.begin());
	print(vi.begin(), vi.end(), "vi copied from ai");
	my_copy(li.begin(), li.end(), ai.begin());
	print(ai.begin(), ai.end(), "ai copied from li");
	print(li.begin(), li.end(), "li");

	//8
	vector<int>::iterator v_it =find(vi.begin(), vi.end(), 3);
	if (v_it != vi.end()) cout << "In vi, 3 has index " << v_it - vi.begin() << endl;

	list<int>::iterator li_it = find(li.begin(), li.end(), 27);
	if (li_it != li.end())
	{
		int index = 0;
		for (list<int>::iterator p = li.begin(); p != li.end(); ++p)
			++index;
		cout << "In li, 27 has index " << index << endl;
	}
	else
		cout << "27 is not in li" << endl;
}

int main()
{
	try
	{
		drill();

		keep_window_open();
		return 0;
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (...)
	{
		cerr << "Error unknown" << endl;
		keep_window_open("~~");
		return 2;
	}
}