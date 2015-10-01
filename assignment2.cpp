#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include "bintree.h"

using namespace std;

class word
{
   private:
   string aWord;
   int count;
   public:

   word(string str, int num): aWord(str), count(num)
   {
   }

   bool operator == (const word &str) const
   {
      return aWord == str.aWord;
   }

   bool operator < (const word &str) const
   {
      if(str.aWord.compare(aWord) < 0)
         return false;
      return true;
   }
   int getCount() const { return count; }
   string getString() const { return aWord; }

   string toString() const
   {
      stringstream ss;

      if(count < 10)
         ss << "   " << count << "  | " << aWord;
      else
         ss << "  " << count << "  | " << aWord;
      return ss.str();
   }
};

void openFile(char *argv[], bintree<word> &words, int &count);
void validateChar(bintree<word> &words, string &line, int &count);
void insertWord(bintree<word> &words, word aWord, int &count);
void print(bintree<word> &words, char *argv[], int &count);

int main(int argc, char *argv[])
{
   string str;
   int count = 0;
   bintree<word> words;

   openFile(argv, words, count);
   print(words, argv, count);

   return 0;
}

void openFile(char *argv[], bintree<word> &words, int &count)
{
   ifstream fin;
   string line;

   fin.open(argv[1]);

   if(!fin)
   {
      cout << "\nERROR - Unable to access " << argv[1] <<"\n";
      exit(0);
   }

   cout << "\nfilename : " << argv[1] <<"\n";

   while(!fin.eof())
   {
      getline(fin, line);

      if(line.size() != 0)
      {
         validateChar(words, line, count);
      }
   }
   fin.close();
}

void validateChar(bintree<word> &words, string &line, int &count)
{
   int index = 0;
   string str;
   char ch;

   while(index < (int)line.size())
   {
      ch = line.at(index);

      if(isalpha(ch) || isdigit(ch))
         str.push_back(ch);
      else if(ch == '.')
      {
         if(index == 0)
         {
            if(isdigit(line.at(index + 1)))
               str.push_back(ch);
         }
         else
         {
            char pre = line.at(index - 1);

            if((pre == ' ' || pre == '\t' || isdigit(pre))
               && isdigit(line.at(index + 1)))
                  str.push_back(ch);

            else
            {
               if(index != 0 && str != "")
               {
                  word aWord(str, 1);
                  insertWord(words, aWord, count);
                  str.clear();
               }
            }
         }
      }
      else if(ch == '\'')
         str.push_back(ch);
      else
      {
         if(index != 0 && str != "")
         {
            word aWord(str, 1);
            insertWord(words, aWord, count);
            str.clear();
         }
      }
      index++;
   }

   if(str != "")
   {
      word aWord(str, 1);
      insertWord(words, aWord, count);
      str.clear();
   }
}

void insertWord(bintree<word> &words, word aWord, int &count)
{
   int num;
   string str;

   if(words.find(aWord) != NULL)
   {
      num = words.find(aWord)->getCount() + 1;
      str = aWord.getString();
      words.erase(aWord);
      word newWord = word(str, num);
      words.insert(newWord);
      count++;
   }
   else
      words.insert(aWord);
}

void print(bintree<word> &words, char *argv[], int &count)
{
   int total = words.size() + count;

   cout << "\nCOUNT | WORD\n------+------\n";
   words.print();
   cout <<"\nNumber of unique words in "<<argv[1]<<" is "<<words.size();
   cout<<"\nTotal number of words in "<<argv[1]<<" is "<<total<<"\n";
}
