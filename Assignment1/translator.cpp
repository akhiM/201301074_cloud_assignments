#include<iostream>
#include<sstream>
#include<fstream>

using namespace std;

int main()
{
	ifstream file("32_bit.asm");
	ofstream myfile;
	myfile.open("64bit.asm");
	string line;
	int flag = 0;
	while(getline(file, line))   
    {
    	istringstream iss(line);
    	string result;
    	while(getline(iss, result , '\t'))
        {	
        	if(result == "dd")
        		myfile << " dq" ;
        	else if(result == "resd")
        		myfile << " resq";
        	else
        		myfile << " " << result;
        	if(result == "main:")
        	{
        		myfile << endl << " push rbp ;";
        		flag = 1;
        		break;
        	}
        }
        if(flag == 1)
        	break;
        myfile << endl;
    }
    while(getline(file, line))   
    {
    	istringstream iss(line);
    	string result;
    	int c = 0;
        while(getline(iss, result, ' '))
        {
        	c = 1;
        	myfile << result << " ";
        	string token;
        	flag = 0;
        	while(getline(iss, token, ','))
        	{
        		flag++;
        		if(token == "eax")
        			if(flag == 1)
        				myfile << " rax,";
        			else
        				myfile << "rax";
        		else
        			if(flag == 1)
        				myfile << " " << token << ',';
        			else
        				myfile << " " << token;
        	}
        }
        if(c==0)
        	myfile << "pop rbp" << endl;
        myfile << endl;
    }
    myfile.close();
	return 0;
}
