///////////////////////////////////////////////////////////////////
//  Str.cpp   -  implementation file for string class            //
//  ver 2.1                                                      //
//                                                               //
//  Language:     Visual C++, ver 12.0                           //
//  Platform:     Dell XPS 2720, Win 8.0                         //
//  Application:  ADT example, CSE687 - Object Oriented Design   //
//  Author:       Jim Fawcett                                    //
//                Syracuse University, CST 4-187                 //
//                fawcett@ecs.syr.edu, (315) 443-3948            //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstring>
#include <stdexcept>
#include "Str.h"
using namespace std;

//----< sized constructor >------------------------------------

Str::Str(int n) : array(new char[n]), max(n), len(0) 
{
  array[0] = '\0';
}

//----<copy constructor >--------------------------------------

Str::Str(const Str& s) : array(new char[s.max]), max(s.max), len(s.len)
{
  for (int i = 0; i <= len; i++)
    array[i] = s.array[i];
};

//----<move constructor >--------------------------------------

Str::Str(Str&& s) : array(s.array), max(s.max), len(s.len)
{
  s.array = nullptr;  // must do this to avoid delete in s dtor
};

//----< promotion constructor >--------------------------------

Str::Str(const char* s) : len(static_cast<int>(strlen(s)))
{
  max = len+1;
  array = new char[len+1];
  for(int i=0; i<=len; i++)
    array[i] = s[i];
}

//----< destructor >-------------------------------------------

Str::~Str()
{
  delete [] array;
  max = len = 0;
}

//----< copy assignment operator >-----------------------------

Str& Str::operator=(const Str& s) {

  if (this == &s) return *this;
  if (max >= s.len + 1) {
    len = s.len;
    int i;
    for (i = 0; i <= len; i++)
      array[i] = s.array[i];
    return *this;
  }
  delete[] array;
  array = new char[max = s.max + 10];
  int i;
  len = s.len;
  for (i = 0; i <= len; i++)
    array[i] = s.array[i];
  return *this;
}

//----< move assignment operator >-----------------------------

Str& Str::operator=(Str&& s) {

  if (this == &s) return *this;
  max = s.max;
  len = s.len;
  array = s.array;
  s.array = nullptr;
  return *this;
}

//---< index operator >----------------------------------------

char& Str::operator[](int n) {

  if(n<0 || len<=n)
    throw invalid_argument("index out of bounds in operator[]");
  return array[n];
}

//----< index operator for const str >-------------------------

char Str::operator[](int n) const {

  if(n<0 || len<=n)
    throw invalid_argument("index out of bounds in operator[])");
  return array[n];
}

//

//----< append char to string >--------------------------------

Str& Str::operator+=(char ch) {

  if(len < max-1) {
    array[len] = ch;
    array[len+1] = '\0';
    len++;
  }
  else {
    max *= 2;   // multiply by 2
    char *temp = new char[max];
    int i;
    for(i=0; i<len; i++)
      temp[i] = array[i];
    temp[len] = ch;
    temp[len+1] = '\0';
    len++;
    delete [] array;
    array = temp;
  }
  return *this;
}

//----< append string to string >------------------------------

Str& Str::operator+=(const Str& s) {

  if(len < max-s.size()) {
    int i;
    for(i=0; i<=s.len; i++)
      array[len+i] = s.array[i];
    len += s.size();
  }
  else {
    max += max + s.size();
    char *temp = new char[max];
    for(int i=0; i<len; i++)
      temp[i] = array[i];
    for(int i=0; i<s.size(); i++)
      temp[len+i] = s.array[i];
    temp[len+s.size()] = '\0';
    len += s.size();
    delete [] array;
    array = temp;
  }
  return *this;
}

//----< addition operator >------------------------------------

Str Str::operator+(const Str& s)
{
  Str temp = *this;
  temp += s;
  return temp;
}
//
//----< insertion operator >-----------------------------------

ostream& operator<<(ostream& out, const Str& s) {

  int i;
  for(i=0; i<s.size(); i++)
    out << s[i];
  return out;
}

//----< extraction operator >----------------------------------

istream& operator>>(istream& in, Str& s) {

  char ch;
  s.flush();
  in >> ch;
  while((ch != '\n') && in.good()) {
    s += ch;
    in.get(ch);
  }
  return in;
}

//

//----< test stub >--------------------------------------------

#ifdef TEST_STR

#include <fstream>

Str testFunction()    // note return by value
{
  Str s("string created in testFunction");
  return s;
}

int main(int argc, char* argv[]) 
{

  cout << "\n  Testing Str class "
       << "\n ===================\n";

  try
  {
    cout << "\n  testing promotion constructor "
         << "\n -------------------------------\n";

    Str s1 = Str("this is a string");
    cout << "  new Str object: " << s1 << endl;

    cout << "\n  testing copy constructor "
         << "\n --------------------------\n";

    Str s2 = s1;                   // calls Str(const Str &s)
    cout << "  copy of original:    " << s2 << endl;

    cout << "\n  testing move constructor "
         << "\n --------------------------\n";

    Str s2move = testFunction();
    cout << "  " << s2move << endl;

    cout << "\n  testing index operator "
         << "\n ------------------------\n";

    const Str s3 = s1;
    char ch = s3[1];
    cout << "  second character is: " << ch << endl;

    s2[3] = 'x';
    cout << "  modifying fourth character: " << s2 << endl;

    cout << "\n  testing appends "
         << "\n -----------------\n";

    cout << "  appending vowel characters:\n";
    s1 += 'a';
    cout << "  " << s1 << endl;
    s1 += 'e';
    cout << "  " << s1 << endl;
    s1 += 'i';
    cout << "  " << s1 << endl;
    s1 += 'o';
    cout << "  " << s1 << endl;
    s1 += 'u';
    cout << "  " << s1 << endl;
    cout << "  size of Str object is " << s1.size() << endl;
  
    cout << "\n  appending string \"yyy\": ";
    s1 += Str("yyy");
    cout << s1 << endl;
    cout << "  size of Str object is now " << s1.size() << endl; 

    cout << "  appending a long string to Str object:\n  ";
    s1 += Str(" and the rain in Spain falls mainly on the plain");
    cout << s1 << endl;
    cout << "  size of Str object is now " << s1.size() << endl;

    cout << "\n  testing addition operator "
         << "\n -----------------------------\n";

    Str orig = Str("  Original string");
    Str sum = orig + Str(" - this is a concatenated part");
    cout << sum << endl;

    cout << "\n  testing copy assignment operator "
         << "\n ----------------------------------\n";

    cout << "  assigning the original's copy to this string: ";
    s1 = s2;
    cout << s2 << endl;
    cout << "  size of Str object is now " << s1.size() << endl;

    cout << "\n  testing move assignment operator "
         << "\n ----------------------------------\n";

    s2move = s1 + Str(" ") + s1;
    cout << " sum of two strings is: "
         << s2move << endl;

    cout << "\n  testing memory resizing by multiple appends "
         << "\n ---------------------------------------------\n";  
    cout << "  appending \"C++ is great!!! \" several times to this string:\n\n";
    int i;
    for(i=0; i<5; i++) {
      s1 += Str("C++ is great!!! ");
      s2 = s1;
      cout << "  " << s2 << endl;
      cout << "  size of Str object is now " << s2.size() << endl;
    }

    cout << "\n  testing insertion and extraction operators "
         << "\n --------------------------------------------\n";

    ofstream out("test.dat");
    if(!out.good()) {
      cout << "\n  can't open file for writing strings\n\n";
      return 1;
    }
    Str insert1 = Str("Now is the time for all good men ");
    insert1 += Str("to come to the aid of their country");
    out << insert1 << endl;

    Str insert2 = Str("The rain in Spain falls mainly on the plain");
    out << insert2 << endl;

    Str insert3 = Str("This is the last line");
    out << insert3 << endl;

    out.close();
    ifstream in("test.dat");
    if(!in.good()) {
      cout << "\n  can't open file test.dat for input\n\n";
      return 1;
    }

    Str extract;
    while(in.good()) {
      in >> extract;
      cout << "  " << extract << endl;
    }

    cout << "\n  testing cast operator "
         << "\n --------------------------------------------\n";

    const char* ccs = static_cast<const char*>(extract);

    cout << "  The string below is a const char*"
         << " holding address of last Str's character memory:\n\n  "
         << ccs << endl;

    cout << "\n  testing index operator "
         << "\n --------------------------------------------\n";

    Str indexTest = Str("012345");
    cout << "  " << indexTest << " - ";
    for(int i=0; i<7; ++i)
      cout << indexTest[i] << " ";
    cout << endl;
  }
  catch(exception& e)
  {
    cout << "\n  " << e.what() << endl << endl;
    return 1;
  }
  return 0;
}

#endif
