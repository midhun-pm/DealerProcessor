#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

bool isNum(char ch)
{
return ((ch >= '0' && ch <= '9'));
}

bool isComma(char ch)
{
return ch==',';
}

bool isAlpha(char ch)
{
return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

bool isColon(char ch)
{
return (ch==':');
}

bool isValid(char ch)
{
 return isAlpha(ch) || isColon(ch) || isNum(ch) || isComma(ch) || ch==' ';
}

int main()
{

ifstream infile;
char ch;
infile.open("textcleaner_input");
stringstream leftstr("");
stringstream rightstr("");


bool rightSwitch = false;
bool rightendfound = false;
bool numfound = false;
bool isPrevSpace = false;
bool isPrevColon = false;

while(!(infile.eof()))
{
ch = infile.get();

// cout<<"Processing "<<ch<<" ";

//Remove double spacing, throw out invalids
if(!isValid(ch) || (leftstr.str().length()==0 && ch==' ') )
  continue;

if(ch==' ')
{
	if(isPrevSpace)
	  continue;
	else
	{
		isPrevSpace = true;
	}
}
else
{
	isPrevSpace = false;
}



//Found a number after the colon, we're on the right now.
if(isNum(ch) && isPrevColon)
{
		rightSwitch = true;
    	isPrevColon = false;
        isPrevSpace = false;
}


if(rightSwitch && isNum(ch))
{
	numfound = true;
}

// cout<<"RS: "<<rightSwitch<<" NF: "<< numfound << "isNum "<<isNum(ch)<<" isComma: "<<isComma(ch)<<"\n";
if(rightSwitch && numfound && !(isNum(ch) || isComma(ch)))
{
	cout<<" \u2022 "<<leftstr.str()<<rightstr.str();

	//CLEAR Streams
	leftstr.str(std::string());
	rightstr.str(std::string());

	//Reset flags
	rightSwitch = false;
	numfound = false;
	isPrevSpace = false;
	isPrevColon = false;

	//Add the char back to leftstream
	if(isAlpha(ch))
	leftstr<<ch;
	continue;
}



if(rightSwitch)
{
	rightstr<<ch;
	if(isComma(ch))
	{
		rightstr<<' ';
		isPrevSpace = true;
	}
}
else
{
	if(isColon(ch) && isPrevColon)
		continue;

	//Insert a space before every colon
	if(isColon(ch) && !isPrevSpace)
		leftstr<<' ';

	leftstr<<ch;
	
	if(isComma(ch))
	{
		leftstr<<' ';
		isPrevSpace = true;
	}

	if(isColon(ch))
	{
		leftstr<<' ';
		isPrevSpace = true;
		isPrevColon = true;
	}
}


}
//Flush whatever remains
	cout<<" \u2022 "<<leftstr.str()<<rightstr.str();



}
