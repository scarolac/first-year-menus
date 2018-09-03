#include <std_lib_facilities.h>

class Punct_stream	//like istream but user can add to whitespace character list
{
public:
	Punct_stream(istream& is)
		: source(is), sensitive(true)
	{}

	void whitespace(const string& s) { white = s; }		//make the whitespace set

	void add_white(char c) { white += c; }				//is c in the whitespace set

	bool is_whitespace(char c);

	void case_sensitive(bool b) { sensitive = b; }

	bool is_case_sensitive() { return sensitive; }

	Punct_stream& operator >> (string& s);

	operator bool();

private:
	istream& source;		//character source
	istringstream buffer;	//we let buffer do our formatting
	string white;			//characters considered "whitespace"
	bool sensitive;			//is the stream case-sensitive?
};
