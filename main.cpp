// Name : Parminder Singh
// Professor: Dr. Ray
// Assignment: Una Shell
#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include "sys/wait.h"
#include <stdlib.h>
#include <unistd.h>
using namespace std;
string readLine();
char **tokenize(string);
void printTest(char **);
bool execute(char **);
int main() {
   bool flag = 1;
   string line;
   char **argList;
   while (flag)
   {
      cout << "csis> ";
      line = readLine();
      argList = tokenize(line);
      // IMPORTANT: comment the next line out when done testing tokenize().
      // printTest(argList);
      //***
      flag = execute(argList);
} }
/*
char** tokenize(string)
   This function is responsible for accepting the command string as a parameter.
   It returns a char** pointer.  The function dynamically allocates an array of
   char* pointers equal to the number of (space delimited) words in the command
string.
   Each char* pointer is dynamically allocated to exactly store one word from the
command. M
   ke the string pointed to by each char* pointer is NULL terminated (C-strings).
   Make sure the array of char* pointers pointed to by the char** pointer is NULL
terminated.
   (This is what will be expected by the execvp function.)
*/
char **tokenize(string line)
{
   // PART 2 here
   stringstream sen(line);
   string word;
   int count = 0;
vector<string> v1;
while (sen >> word)
   {
count++;
      v1.push_back(word);
   }
   char **arr = new char *[count];
   vector<string>::iterator it;
   int i = 0;
   for (it = v1.begin(); it != v1.end(); it++)
   {
      int word_len = (*it).size() + 1;
      arr[i] = new char[word_len];
      strlcpy(arr[i++], (*it).c_str(), word_len);
}
return arr; }
/*
bool execute(char** args)
   This function accepts the char** that points to the array of pointers to C-
strings.
   This function uses the fork() command to fork a brand new copy of itself.
   Then, for the child process, it makes use of execvp() to overwrite itself
   with a new program.  Call execvp properly making use of the char**.
   For the parent process (still running the shell program), it waits until
   the child process is terminated.  Make use of waitpid for this.
*/
bool execute(char **args)
{
   if (args[0] == NULL || args[0][0] == '\0')
   {
      return true;
   }
   pid_t pid = fork();
   bool check = true;
if (pid < 0)
   {
      perror("Fork Error");
exit(-1); }
   else if (pid == 0)
   {
      if (execvp(args[0], args) == -1)
{
exit(-1);
} }
   else if (strcmp(args[0], "exit") == 0)
   {
exit(0); }
else
{
      int value = 0;
      if (waitpid(pid, &value, 0) == -1)
      {
exit(-1); }
      if (WIFEXITED(value) == 1)
      {
         check = true;
} else
      {
         check = false;
} }
   return check;
}
string readLine()
{
   string line;
   getline(cin, line);
   return line;
}
void printTest(char **temp)
{
   int counter = 0;
   while (temp[counter] != nullptr)
   {
      cout << temp[counter] << endl;
counter++; }
}