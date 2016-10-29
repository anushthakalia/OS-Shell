#include <iostream>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <time.h>
#include <dirent.h>


using namespace std;



#define FALSE 0
#define TRUE !FALSE

 
extern  int alphasort();

string arr[8] = {"curtime","ls","cd","refile","delfile","deldir","grep","exit"};

void change_directory(string directory)
{

    int a = chdir(directory.c_str());        
}

void ls_command()
{

	int count,i;
	struct direct **files;
	int file_select();                
	char cwd[1024];
    getcwd(cwd, sizeof(cwd));// to get the current working directory
    if(cwd !=NULL)
    {              
    	cout<<"Current Working Directory = "<<endl<<cwd<<endl;		
		count =scandir(cwd, &files, file_select, alphasort);		 
		if(count>0)
		{			
			cout<<"Number of files = "<<count;
			for (i=1;i<count+1;++i)
			cout<<files[i-1]->d_name<<endl;			
			
		}
		else cout<<"No files found"<<endl;											
	}
	else cout<<"Error:cant find the directory"<<endl;
}
// file_select is for ls_command
int file_select(struct direct *entry)
 
		if ((strcmp(entry->d_name, ".") == 0)||(strcmp(entry->d_name, "..") == 0))
			return (FALSE);
		else return (TRUE);		

// time
void curtime()
{
 time_t rawtime;
 struct tm * timeinfo;
 time ( &rawtime );
 timeinfo = localtime ( &rawtime );
 cout<<"Current time and date: "<< asctime (timeinfo)<<endl ; // asctime() converts tm structure to string format
}
// rename file and folders
void mv_command()
{
    char oldname[100];
    char newname[100];
    cout<<"Enter old filename: "<<endl;
    cin>>oldname;
    cout<<"Enter new filename: "<<endl;
    cin>>newname;
    int ret;    
   ret = rename(oldname, newname);	
   if(ret == 0) 
   {
      printf("File renamed successfully\n");
   }
   else 
   {
      printf("Error: unable to rename the file\n");
   }

}
// remove directory
void remove_dir()
{
	char str[100];
    printf("Enter the directory to delete");
    scanf("%s",str);
    DIR *theFolder = opendir(str);
    struct dirent *next_file;
    char filepath[256];
    while ( (next_file = readdir(theFolder)) != NULL )
    {        
        sprintf(filepath, "%s/%s", str, next_file->d_name);
        remove(filepath);              
    }
    rmdir(str);
    printf(" Folder deleted");
    closedir(theFolder);
}
// remove file
void remove_file()
{
	int ret;   
    char filename[100];
    printf("Enter filename to delete: ");
    scanf("%s", filename);     
    ret = remove(filename);
    if(ret == 0) 
    {
     	 printf("File deleted successfully\n");
    }
    else 
    {
    	  printf("Error: unable to delete the file\n");
    }
}

vector<string> tokenizer(string sentence)
{
	int p;
	sentence = strtrim(sentence);	
	vector<string> tokens (10);		
	vector<int> index_vector = get_white_spaces(sentence);	
	int pre,post,length,i;
	i= 0;
	length = 0;
	string temp;
	while(i < index_vector.size())
	{
		if((i ==0)||(index_vector.at(i) !=0))
		{
			temp.clear();
			pre = index_vector.at(i);
			post = index_vector.at(i+1);			
			for(int j = pre;j<=post;j++)
			{
				temp = temp + sentence[j];
			}			
			tokens.at(length) = temp;
			length++;		
		}

		i = i+2;
	}	
	return tokens;
}
vector<int> get_white_spaces(string sentence)
{	
	vector<int> space_index(20);
	char x;
	int i = 0;
	int j,k;
	k = 0;
	int diff = 0;	
	space_index.at(k) = 0;
	k++;
	while(i<sentence.size())
	{		
		if(sentence[i] == ' ')
		{
			space_index.at(k) = i-1;
			k++;
			j = i;
			while(j<sentence.size()-1)
			{				
				if((sentence[j]==' ')&&(sentence[j+1]!=' ')) 
				{			
					space_index.at(k) = j+1;
					k++;
					break;
				}
				else j++;
			}						
			diff = j-i;
			i = j+1;			
		}	
		else i++;			
		 
	}
	space_index.at(k) = sentence.size()-1;	
	return space_index;
}

string strtrim(string sentence)
{	
	int i = 0;
	sentence = sentence.c_str();
	int j = sentence.size()-1;	
	char x;		
	while(i < j)
	{
		if(sentence[0] != ' ') 
		{
				i = 0;
				break;
		}
		else if((sentence[i] == ' ') && (sentence[i+1] != ' ')) 
		{
				i = i+1;
				break;
		}
		else
		{
			i++;			
		}
	}	
	while(j>0)
	{
		if(sentence[sentence.size()-1] != ' ') break;		
		else if((sentence[j] == ' ') && (sentence[j-1]!=' ')) 
		{	
			j = j-1;
			break;
		}
		else j--;
	}
	string trm_str;
	trm_str.clear();	

	for(int k = i; k<=j; k++)
	{
		x = sentence[k];
		trm_str = trm_str + x;		
	}	
	return trm_str;

}


vector<int> KMP_implementation(string text_string, string pattern_string)   //This is implementation of KMP algorithm
{	vector<int> v;
	v = search_substring(text_string, pattern_string);
	return v;
}

vector<int> search_substring(string text_string, string pattern_string)
{
	vector<int> index_vector;
	index_vector.push_back(0);
	int pattern_len, text_len, j, i,count;
	count  = 0;
	pattern_len = pattern_string.length();
	text_len = text_string.length();
	int pmt[pattern_len];
	j = 0;
	get_partial_match_table(pattern_string, pattern_len, pmt);
	i = 0;
	while (i < text_len)
	{
		if (pattern_string[j] == text_string[i])
		{
			j = j+1;
			i = i+1;
		}
		if (pattern_len == j)
		{			
			index_vector.push_back(i-j-1);
			index_vector.push_back(i-j+1);
			count = count +1;
			j = pmt[j-1];
		}
		else if ((i < text_len)&&(pattern_string[j] != text_string[i]))
		{
			if ( 0 != j)
			{
				j = pmt[j-1];
			}
			else
			{
				i = i + 1;
			}
		}
	}
	return index_vector;   //returns no of times a pattern is contained in it.
}

void get_partial_match_table(string pattern_string, int pattern_len, int pmt[])
{
	int j = 0;
	int i = 1;
	pmt[0] = 0;
	while (i < pattern_len)
	{
		if (pattern_string[i] == pattern_string[j])
		{
			pmt[i] = j+1;
			j++;
			i++;
		}
		else
		{
			if (0 != j)
			{
				j = pmt[j - 1];
			}
			else
			{
				pmt[i] = 0;
				i++;
			}
		
		}
	}
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
		temp = minimum_edit_distance(input, arr[i]);		
		if(min>temp) 
		{
			min = temp;
			index = i;
		}			
	}
	cout<<min<<" "<<index<<endl;

	if ((min <= 3)&&(min>=1)) 
	{
		cout<<"Do you mean '"<<arr[index]<<"'"<<endl;
	}
	else cout<<"NO command found"<<endl;	
	cout<<endl;
}

int main()
{
	int i;
	
	// sanjeev you have to add functions of cd and grep 
	
	//cout<<"Available Commands"<<endl;
	//for(i=0;i<8;i++) printf("%s\n",(*ptr)[i]);   
	while(1)
	{
		cout<<"sanjeev@sanjeev-HP-ProBook-445-G1";
		cout<<">>";
		string command_line;	
		cin>>command;
		vector<string> tokens = tokenizer(command_line);

		int command=0;
		for(i=0;i<8;i++)
		{
				int ret=strcmp(tokens[0],arr[i]);
				if(ret==0)
				{			
					command=i;
					break;
				}
				else
				{
					suggest_command(tokens[0]);
				}			
		}
		switch(command)
		{
		case 1: curtime();
		break;
		case 2:ls_command();
		break;
		case 3:change_directory();
		break;
		case 4:mv_command();
		break;
		case 5:remove_file();
		break;
		case 6:remove_dir();
		break;
		case 7://grep function
		break;
		case 8: //exit(0);		
		break;

		}

	}

}