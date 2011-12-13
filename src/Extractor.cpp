#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>

#include "zipcode.h"
#include "util.h"

using namespace std;

string findAddress(string& s, int index)
{
	// be on the look out backwards till you find a numerical char string of 3 lengths isolated !

	string retVal;
	for(int i=index;i>=0;i--)
	{
		if(s[i]==' ')
		{
			if(i-3>=0)
			{
				// get back till another space is found
				string streetNum;
				int finalIndex = i-1;
				for(int j=i-1;j>=0;j--)
				{
					if(!isdigit(s[j]) || (int)streetNum.length()>=5)
						break;
					streetNum = s[j] + streetNum;
					finalIndex = j;
				}
				if(streetNum.length()>=3 && streetNum.length()<=5)
				{
					// we have a match here check if it's the last char or the previous char is a space
					if(finalIndex==0 || (finalIndex-1>=0 && s[finalIndex-1]==' '))
					{
						return streetNum + " " + retVal;
					}
				}
			}
		}
		retVal = s[i] + retVal;
	}

	return "";
}

void processInlineAddress(string& current, int index, vector<string>&textLines)
{
	// find in current string if you can locate a "street tag name" by "street" or "st"
	string lowerCurrent = toLower(current);

	// check for street first
	size_t finder = lowerCurrent.find("street");
	
	string address;
	if(finder != string::npos)
	{
		address = findAddress(current,finder-1);
		if( finder-1>=0 && current[finder-1]==' ' && (int)address.length()>0)
		{
			cout<<(address + current.substr(finder,6))<<endl<<endl;
		}
	}

	finder = lowerCurrent.find("st");

	if(finder != string::npos)
	{
		address = findAddress(current,finder-1);
		if(finder-1>=0 && current[finder-1]==' ' && (int)address.length()>0)
		{
			cout<<(address + current.substr(finder,2))<<endl<<endl;
		}
	}

}

void processZipCodeAddress(string& current, int index, vector<string>& textLines)
{
	// find an index on the string current which has a zip code, a pair with the start and end indexes
	zipcode zip = findZipCode(current);

	if(zip.start == -1)
			return;


	// Let's try to handle case 1 here , go on backwards from start index till you find a street number, also look out for some alpha chars in middle !
	string address = findAddress(current,zip.start-1);
	if((address.length()>0))
	{
		cout<<(address+" " +zip.val)<<endl<<endl;
		return;
	}

	// Case 2 assuming address returned a empty value, let's try to look up value in i-1,i-2 indices for possibe matches
		
	string addressLast;

	if(index-1>=0)
			addressLast = findAddress(textLines[index-1],(int)textLines[index-1].length()-1);

	if(addressLast.length()>0)
	{
		cout<<(addressLast+ "\n" + deleteSp(current))<<endl<<endl;
		return;
	}

	string addressLastLast;

	if(index-2>=0)
		addressLastLast = findAddress(textLines[index-1],(int)textLines[index-2].length()-1);

	if(addressLastLast.length()>0)
	{
		cout<<(addressLastLast + "\n" + deleteSp(textLines[index-1]) + "\n" + deleteSp(current))<<endl<<endl;
	}

}

int main()
{
	vector<string>stateAbbr;
	readInp(stateAbbr);

	// we will pick up and read all lines from our file and store it as one big string

	string text; // stores the entire text in memory

	vector<string>textLines; // also store everything of a string line by line, will help us in resolving penske addresses
	string s;

	while(getline(cin,s))
	{
		text += s;
		textLines.push_back(s);
	}

	/* let's try to umcomplicate things, we divide our case into 2 halfs
		1. let's focus on the easier part, the whole address is on a single line, what you do is just first find
		the zip address, then move back till you get a address number which should be 3 or 4 characters long.
		Also check you saw sufficient non-alphabetic characters on the way to be sure its an address.
		2. The harder one's when address is line by line, well the logic is simple, the line you find your zip code
		move on the back line, then on the back line and so on, go on till last 3 lines. if you don't find a house
		number , you are done or just output the address.
		3. A city name should be there inside your parsed address !
	*/
	
	/* Then the harder cases follow 
		like 148 20th street
	*/

	for(int i=0;i<(int)textLines.size();i++)
	{
		string current = textLines[i];


		// this function handles the non-trivial cases where zip code is not there ala inline-formats.txt types 

		processInlineAddress(current,i,textLines);

		processZipCodeAddress(current,i,textLines);
		
	}


	return 0;
}
