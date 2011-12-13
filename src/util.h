#include<string>
#include<vector>
#include<fstream>

using namespace std;

void readInp(vector<string>&stateAbbr)
{
	// reads input from the states file
	ifstream f1("states.txt");
	string s;
	while(f1>>s)
	{
		stateAbbr.push_back(s);
	}
	return ;
}

string deleteSp(string s)
{
	// this utility function deletes the front spaces or tabs !
	int index = 0;
	for(int i=0;i<(int)s.length();i++)
	{
		if(s[i] != ' ' && s[i]!='\t')
		{
			index = i;
			break;
		}
	}

	return s.substr(index,(int)s.length()-index);
}

string toLower(string& s)
{
	string ret;

	// lowers every character of string

	for(int i=0;i<(int)s.length();i++)
	{
		ret+=tolower(s[i]);
	}
	return ret;
}