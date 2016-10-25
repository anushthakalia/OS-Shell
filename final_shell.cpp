#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include <fstream>
using namespace std;
extern int alphasort();
#define FALSE 0
#define TRUE !FALSE
int minimum_edit_distance(string alpha, string beeta);
void get_partial_match_table(string pattern_string, int pattern_len, int pmt[]);
void suggest_command(string input);
void curtime();
void remove_file(string name_file);
void remove_dir(string dir_name);
void ls();
int file_select(struct dirent *entry);
void rename_file(string oldi, string newi);
vector<string> tokenizer(string sentence);
vector<int> get_white_spaces(string sentence);
void get_current_directory();
string strtrim(string sentence);
vector<int> search_substring(string text_string, string pattern_string);
string get_data_string(string file_name);
vector<int> KMP_implementation(string text_string, string pattern_string);
void change_directory(string directory);
void grep(string text, string file_name);
string arr[9] = {"curtime","whereami","ls","cd","refile","delfile","deldir","grep","exit"};
char pathname[MAXPATHLEN];
int main()
{
string command_line;
int a = 1;
cout<<"Available commands are:"<<endl;
cout<<"--------"<<endl;
cout<<"curtime -> To display the current time"<<endl;
cout<<"--------"<<endl;
cout<<"whereami -> To display the current directory"<<endl;
cout<<"--------"<<endl;
cout<<"ls -> To list out all files in the current directory"<<endl;
cout<<"--------"<<endl;
cout<<"cd dir_name -> To go into a directory"<<endl;
cout<<"--------"<<endl;
cout<<"refile old_name new_name -> To rename a file or directory"<<endl;
cout<<"--------"<<endl;
cout<<"delfile file_name -> To delete a file"<<endl;
cout<<"--------"<<endl;
cout<<"deldir dir_name -> To delete a directory"<<endl;
cout<<"--------"<<endl;
cout<<"grep text file_name -> To find a substring in a file"<<endl;
cout<<"--------"<<endl;
cout<<"exit -> for exiting the shell"<<endl;
cout<<"--------"<<endl;
while(a == 1)
{


cout<<"sanjeev@sanjeev-HP-ProBook-445-G1";
cout<<">>";
getline(cin, command_line);
vector<string> tokens = tokenizer(command_line);
suggest_command(tokens[0]);
int command=-1;
for(int i=0;i<9;i++)
{
if(tokens[0] == arr[i])
{
command=i;
break;
}
}
switch(command)
{
case 0: curtime(); //curtime
break;
case 1: get_current_directory(); //whereami
break;
case 2: ls(); //ls
break;
case 3: change_directory(tokens[1]); // cd folder
break;
case 4: rename_file(tokens[1], tokens[2]); //refile oldname newname
break;
case 5: remove_file(tokens[1]); //delfile filename
break;
case 6:  remove_dir(tokens[1]);
break;
case 7: grep(tokens[1],tokens[2]); // grep keysearch testfile.txt
break;
case 8: a=9;exit(0); 
break;//exit
default: cout<<"Command not Found! Try again.";
break;
}
}
cout<<"BYE"<<endl;
}
void grep(string text, string file_name)
{
string data = get_data_string(file_name);
cout<<data;
vector<int> count = KMP_implementation(data, text);
for(int i = 0;i<count.size();i++)
{
if((i!=0)&&(count.at(i)==0)) break;
cout<<text<<" occurred at: "	<<count.at(i)<<endl;cout<<endl;
}
}
string get_data_string(string file_name)
{
ifstream file(file_name.c_str());
string word;
char x ;
word.clear();
int count = 0;
while ((x = file.get())!= EOF)
{
word = word + x;
}
file.close();
return word;
}
void remove_file(string name_file)
{
int ret;
const char* filename = name_file.c_str();
ret = remove(filename);
if(ret == 0)
{
cout<<"File deleted successfully"<<endl;cout<<endl;
}
else
{
cout<<"Error: unable to delete the file"<<endl;cout<<endl;
}
}
void remove_dir(string dir_name)
{
//char dir_name[100];
const char* directory = dir_name.c_str();
DIR *theFolder = opendir(directory);
struct dirent *next_file;
char filepath[256];
getcwd(filepath, sizeof(filepath));
while ( (next_file = readdir(theFolder)) != NULL )
{  sprintf(filepath, "%s/%s", directory, next_file->d_name);
remove(filepath);
}
rmdir(directory);
cout<<" Folder deleted"<<endl;
cout<<endl;
closedir(theFolder);
}
void rename_file(string oldi, string newi)
{
const char* oldname;
const char* newname;
oldname = oldi.c_str();
newname = newi.c_str();
int ret;
ret = rename(oldname, newname);
if(ret == 0)
{
cout<<"File renamed succesfully"<<endl;cout<<endl;
}
else
{
cout<<"Error renaming the file"<<endl;cout<<endl;
}
}
void get_current_directory()
{
char buff [1024];
if (getcwd(buff,sizeof(buff))!=NULL) {cout<<"Current directory is: "<<buff<<endl;cout<<endl;}
else cout<<"ERROR, getting directory"<<endl;
}
void ls()
{
int count,i;
struct dirent **files;
int file_select(const struct dirent*);
char pathname[MAXPATHLEN];
if (getcwd(pathname, sizeof(pathname)) == NULL)
{
cout<<"Error getting path"<<endl;
}
count = scandir(pathname, &files, file_select, alphasort);
if (count <= 0)
{
cout<<"No files in this directory"<<endl;
}
else
{
for (i=1;i<count+1;++i)
{
cout<<files[i-1]->d_name<<" ";
}
}
cout<<endl;cout<<endl;
}
int file_select(const struct dirent *entry)
{
if ((entry->d_name == ".") ||(entry->d_name == ".."))
return (FALSE);
else
return (TRUE);
}
void curtime()
{
time_t rawtime;
struct tm * timeinfo;
time ( &rawtime );
timeinfo = localtime ( &rawtime );
cout<<"Current time and date: "<< asctime (timeinfo)<<endl ; // asctime() converts tm structure to string format
}
void change_directory(string path)
{
int a;
string my_path = path;
const char * directory = my_path.c_str();
a = chdir(directory);
if (a==0) {cout<<"Directory changed successful"<<endl;cout<<endl;}
else {cout<<"ERROR: No such directory found"<<endl;cout<<endl;}
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
vector<int> KMP_implementation(string text_string, string pattern_string) //This is implementation of KMP algorithm
{ vector<int> v;
v = search_substring(text_string, pattern_string);
return v;
}
vector<int> search_substring(string text_string, string pattern_string)
{
vector<int> index_vector;
index_vector.push_back(0);
int pattern_len, text_len, j, i,count;
count = 0;
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
return index_vector; //returns no of times a pattern is contained in it.
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
int min (int a, int b, int c)
{
int min;
if(a<b) min = a;
else min = b;
if(min<c) return min;
else return c;
}
void suggest_command(string input)
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
if ((min <= 3)&&(min>=1))
{
cout<<"Do you mean '"<<arr[index]<<"'"<<endl;
}
else if(min!=0) cout<<"NO command found"<<endl;
cout<<endl;
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