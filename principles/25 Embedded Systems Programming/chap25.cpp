#include <vector>
#include <iostream>
#include <fstream>
#include<iomanip>
#include<bitset>
using namespace std;


namespace trythis1
{
	struct Message {
		int a;
		int b;
		int c;
	};

	// somewhat smaller type, but not half as small as a Message
	struct Node {
		int a;
		int b;
	};

	void frag()
	{
		Message* p = new Message();
		Node* n1 = new Node();
		delete p;
		Node* n2 = new Node();
		Message* pp = 0;
		Node* nn1 = 0;
		Node* nn2 = 0;
		for (int i = 0; i<100; ++i) {
			pp = new Message();
			nn1 = new Node();
			delete pp;
			nn2 = new Node();
		}
		std::cout << "Difference with fragmentation: " << nn2 - n1 << '\n';
	}


	void non_frag()
	{
		Node* n1 = new Node();
		Node* n2 = new Node();
		Message* p = new Message();
		delete p;
		Message* pp = 0;
		Node* nn1 = 0;
		Node* nn2 = 0;
		for (int i = 0; i<100; ++i) {
			nn1 = new Node();
			nn2 = new Node();
			pp = new Message();
			delete pp;
		}
		std::cout << "Difference without fragmentation: " << nn2 - n1 << '\n';
	}

	void test()
	{
		std::cout << "sizeof(Message): " << sizeof(Message) << '\n';
		std::cout << "sizeof(Node): " << sizeof(Node) << '\n';
		frag();
		non_frag();
	}
}

void trythis2()
{

	int i;
	while (cin >> i)
		cout << dec << i << " == "
		<< hex << "0x" << setw(8) << setfill('0') << i << " == "
		<< bitset<8 * sizeof(int)>(i) << '\n';


}

namespace encryption
{
	void decipher(const unsigned long *const v,
		unsigned long *const w,
		const unsigned long *const k)
	{
		unsigned long y = v[0];
		unsigned long z = v[1];
		unsigned long sum = 0xC6EF3720;
		unsigned long delta = 0x9E3779B9;
		unsigned long n = 32;

		while (n-- > 0) {
			z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
			sum -= delta;
			y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
		}
		w[0] = y;
		w[1] = z;
	}

	void decrypt()
	{
		const int nchar = 2 * sizeof(long);   // 64 bits
		const int kchar = 2 * nchar;          // 128 bits
		const string ifname = "encrypt.txt";
		const string ofname = "decrypt.txt";

		string key = "bs";
		while (key.size() < kchar) key += '0';  // pad key

		ifstream inf(ifname.c_str());
		ofstream outf(ofname.c_str());
		if (!inf || !outf) throw runtime_error("can't open file");

		const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());

		unsigned long inptr[2];
		char outbuf[nchar + 1];
		outbuf[nchar] = 0;  // terminator
		unsigned long* outptr = reinterpret_cast<unsigned long*>(outbuf);
		inf.setf(ios_base::hex, ios_base::basefield);

		while (inf >> inptr[0] >> inptr[1]) {
			decipher(inptr, outptr, k);
			outf << outbuf;
		}
	}
}

namespace notes
{
	/*	Memory safety
		Pools and stacks can be used to prevent memory leaks
		Pool - all objects are the same size, can hold a certain number of objects
		Stack - all objects can only be added to the top, and removed from the top
	*/

	//pool example
	template<class T, int N>class Pool	//pool of N objects of type T
	{
	public:
		Pool();					//make a pool of N Ts
		T* get();				//get a T from the pool; return 0 if no free Ts
		void free(T*);			//return a T given out by get() to the pool
		int available() const;	//number of free Ts
	private:
		//space for T[N] and data to keep track of which Ts are allocated and which are not
	};
	/*
	Pool<Small_buffer, 10> sb_pool;
	Pool<Status_indicator, 200> indicator_pool;

	Small_buffer* p = sb_pool.get();
	sb_pool.free(p);

	*/

	//Stack example
	template<int N>class Stack	//stack of N bytes
	{
	public:
		Stack();				//make an N-byte stack
		void* get(int n);		//allocate n bytes from the stack;
								//return 0 if no free space
		void free();			//return the last value return by get() to the stack
		int available() const;	//number of available bytes
	private:
		//space for char[N] and data to keep track of what is allocated and what is not, eg. a top-of-stack pointer
	};
	/*	
	Stack<50*1024> my_free_store;	//50K woth of storage to be used as a stack

	void* pv1 = my_free_store.get(1024);	//void* is unknown type pointer to memory, gathers 1K for pv1
	int* buffer = static_cast<int*>(pv1);	//converts pv1 into int*

	void* pv2 = my_free_store.get(sizeof(Connection));	//gathers the size needed for the Connection object
	Connection* pconn = new(pv2) Connection(incoming, outgoing,buffer);	//creates the object in the pv2 location
	*/

	//To solve the memory issue, another path is to build a class similiar to vector that uses 
	//references instead of creating new objects
	//this Array_ref does not own its own values, it instead points to existing arrays, vectors 

	//25.4.3
	template<class T> class Array_ref
	{
		T* p;
		int sz;
	public:
		Array_ref(T* pp, int s) : p(pp), sz(s){}

		T& operator[](int n) { return p[n]; }
		const T& operator[](int n) const { return p[n]; }

		bool assign(Array_ref a)
		{
			if (a.sz != a) return false;
			for (int i = 0; i < sz; ++i) { p[i] = a.p[i]; }
		}

		void reset(Array_ref a) { reset(a.p, a.sz); }
		void reset(T* pp, int s) { p = pp; sz = s; }

		int size() const { return sz; }

		//default copy operations:
		//	Array_ref does not own and resources
		//	Array_ref has reference semantics

		//can convert types, cannot be used on classes with multiple inheritence
		template<class Q> operator const Array_ref<const Q>()
		{
			//check implicit conversion of elements
			static_cast<Q>(*static_cast<T*>(0));
			//cast Array_ref:
			return Array_ref<const Q>(reinterpret_cast<Q*>(p), sz);
		}
	};
	//helper functions for array_ref creation
	//handle array_ref creation with or without size
	template<class T> Array_ref<T> make_ref(T* pp, int s)
	{
		return (pp) ? Array_ref<T>(pp, s) : Array_ref<T>(0, 0);
	}
	//handle vector array_ref creation with or without size
	template<class T> Array_ref<T> make_ref(std::vector<T>& v)
	{
		return (v.size()) ? Array_ref(&v[0], v.size()) : Array_ref(0, 0);
	}
	//handle array to array_ref creation
	template<class T,int s> Array_ref<T> make_ref(T(&pp)[s])	//takes a reference to an array of s elements, compiler remembers the size
	{
		return Array_ref<T>(pp, s);
	}

	/*
		To implement a vector of circle* into shape*, they have to be constant 
		since inheritence does not work with containers of objects
		
		Example to allow it:
		void better2(const Array_ref<Shape* const> a)	//the pointers are constant
		{
			for(int i =0; i < a.size(); ++i)
			{
				if(a[i])					//checks if there is a value, checks for null pointers
					a[i]->draw();			//draws the value without making changes, using the -> for pointers
			}
		}
	*/
}

namespace drill
{
	void ex1()
	{
		int v = 1;
		for (int i = 0; i<sizeof(v) * 8; ++i) {
			cout << v << '\n';
			v <<= 1;
		}
	}

	void ex2()
	{
		unsigned int v = 1;
		for (int i = 0; i<sizeof(v) * 8; ++i) {
			cout << v << '\n';
			v <<= 1;
		}
	}

	void print(short unsigned int sui)
	{
		cout << dec << setw(5) << sui << ' ' << hex << setw(4) << sui << ' ' <<
			bitset<16>(sui) << '\n';
	}

	void ex3()
	{
		short unsigned int sui = 0xffff;    // every bit set
		print(sui);
		sui = 0x0001;   // lowest bit set
		print(sui);
		sui = 0x8000;   // highest bit set
		print(sui);
		sui = 0x00ff;   // lowest byte set
		print(sui);
		sui = 0xff00;   // highest byte set
		print(sui);
		sui = 0x5555;   // every second bit set, lowest bit 1
		print(sui);
		sui = 0xaaaa;   // every second bit set, lowest bit 0
		print(sui);
	}

	void ex5()
	{
		short unsigned int sui = 0;

		sui = ~0;       // set every bit
		print(sui);
		sui = 1;        // set lowest bit
		print(sui);
		sui = 1 << 15;    // set highest bit
		print(sui);
		sui = (1 | 1 << 1);   // set lowest byte
		sui |= sui << 2;
		sui |= sui << 4;
		print(sui);
		sui = ~sui;     // set highest byte
		print(sui);
		sui = 1;
		sui |= sui << 2;  // set every second bit, lowest bit 1
		sui |= sui << 4;
		sui |= sui << 8;
		print(sui);
		sui = ~sui;     // set every second bit, lowest bit 0
		print(sui);
	}

	void run_it()
	{
		//ex1();
		//ex2();
		//ex3();
		ex5();
	}
}

void keep_open()
{
	std::cout << "Press a key to exit\n";
	std::cin.clear();
	char ch;
	std::cin >> ch;
}
int main()
{
	try
	{
		drill::run_it();

		keep_open();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		keep_open();
		return 2;
	}
	catch (...)
	{
		std::cerr << "Error unknown" << std::endl;
		keep_open();
		return 3;
	}
}