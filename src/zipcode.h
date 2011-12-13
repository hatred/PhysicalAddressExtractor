#include<string>

using namespace std;

struct zipcode
{
    int start;
	int end;
	string val;
};

bool good(string& s)
{
	// verifies if the string has only numeric characters

	for(int i=0;i<(int)s.length();i++)
	{
		if(!isdigit(s[i]))
			return false;
	}

	return true;
}

zipcode make_zipCode(int st,int end,string& val)
{
	zipcode zip;
	zip.start = st;
	zip.end = end;
	zip.val = val;

	return zip;
}

zipcode findZipCode(string& s)
{
	// this method finds if a zip code is present inside the actual string !
	for(int i=0;i<(int)s.length();i++)
	{
		if(isdigit(s[i]) && i+4<(int)s.length())
		{
			string m = s.substr(i,5);
			if(!good(m))
				continue;
			// check for a '-'
			if(i+5<(int)s.length() && s[i+5]=='-')
			{
				if(i+9<(int)s.length())
				{
					string rest = s.substr(i+6,4);
					if(good(rest))
					{
						string finalCode = m + "-" + rest;
						return make_zipCode(i,i+9,finalCode);
					}
				}
			}
			return make_zipCode(i,i+4,m);
		}
	}

	string dummy;
	// make a dummy -1 index
	return make_zipCode(-1,-1,dummy);
}
