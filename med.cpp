#include<iostream>
#include<string.h>
using namespace std;

int minimum_edit_distance(string alpha, string beeta);
string suggest_command(string input);
int min (int a, int b, int c);
string my_commands [] = {"curtime","ls","cd","refile","delfile","deldir","grep","exit"};

int main()
{	
	string alpha, beeta;
	cout<<"enter the command"<<endl;
	getline(cin, alpha);
	suggest_command(alpha);		
}
int minimum_edit_distance(string alpha, string beeta)
{
	alpha = '#' + alpha;
	beeta = "#" + beeta;
	int alpha_size = alpha.size();
	int beeta_size = beeta.size();
	char alpha_array[alpha_size+1];
	char beeta_array[beeta_size+1];		
	strcpy(alpha_array, alpha.c_str());		
	strcpy(beeta_array, beeta.c_str());		
	int distance_table[alpha_size+1][beeta_size+1];	

	for(int i = 0;i<=alpha_size;i++)
	{
		distance_table[i][0] = i;
	}

	for(int i = 0;i<=beeta_size;i++)
	{
		distance_table[0][i] = i;
	}

	for(int i = 1;i<alpha_size;i++)
	{
		for(int j = 1;j<beeta_size;j++)
		{
			if(alpha_array[i] == beeta_array[j])
			{
				distance_table[i][j] = min((distance_table[i-1][j]+1),(distance_table[i][j-1]+1),(distance_table[i-1][j-1]));				
			}
			else
			{
				distance_table[i][j] = min((distance_table[i-1][j]+1),(distance_table[i][j-1]+1),(distance_table[i-1][j-1]+2));					
			}
		}
	}

	return distance_table[alpha.size()-1][beeta.size()-1];
	
}

int min (int a, int b, int c)
{
	int min;
	if(a<b) min = a;
	else min = b;
	if(min<c)	 return min;		 
	else return c;
}

string suggest_command(string input)
{	
	int index, min, temp;
	index = 0; min= 1000;
	for(int i = 0;i<7;i++)
	{
		temp = minimum_edit_distance(input, my_commands[i]);		
		if(min>temp) 
		{
			min = temp;
			index = i;
		}			
	}
	cout<<min<<" "<<index<<endl;

	if ((min <= 3)&&(min>=1)) 
	{
		cout<<"Do you mean '"<<my_commands[index]<<"'"<<endl;
	}	
	else if(min!=0) cout<<"NO command found"<<endl;	
	cout<<endl;
}
