#include "punctstream.h"

Punct_stream& Punct_stream::operator >> (string& s) //pulls one input at a time, if the word called in
{
	//while loop should fail the first time because buffer is empty
	//after one time through it takes the input source and checks, removes until it is a word with whitespace
	//the second time through, buffer will have the word
	//now it can put the word into the string
	//then return the punct_stream with *this
	//similar to return is; at the end of istream operators >>
	while (!(buffer >> s))	//try to read from buffer, if succeeds, return punct_stream
	{	
		if (buffer.bad() || !source.good()) { return *this; }	//similar to return is when istream operators >> fail
		buffer.clear();		//clears the previous buffer

		string line;
		getline(source, line);

		//do a character replacemnt as needed
		for (size_t i = 0; i < line.size(); ++i)
		{
			if (is_whitespace(line[i]))
				line[i] = ' ';				//to space
			else if (!sensitive)
				line[i] = tolower(line[i]);	//to lower case
		}
		buffer.str(line);					//put string into stream
	}
	return *this;
}

bool Punct_stream::is_whitespace(char c)
{
	for (size_t i = 0; i < white.size(); ++i)
	{
		if (c == white[i]) return true;
	}
	return false;
}

Punct_stream::operator bool()
{
	return !(source.fail() || source.bad()) && source.good();
}