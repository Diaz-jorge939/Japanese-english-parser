#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: Nam Cuong Tran, Jorge Diaz, Corbin Thaete 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Nam Cuong Tran
// RE:  (vowel | vowel n | consonant vowel | consonant vowel n |consonant-pair vowel | consonant-pair vowel n)^+ 
bool word (string s)
{
  vector<char> vowel = {'a','i','u','e','o', 'I', 'E'};
  vector <char> consonant_only= {'d', 'j', 'w', 'y', 'z'};
  vector <char> consonant_pair_y = {'b', 'g', 'h', 'k', 'm', 'n', 'p', 'r'};
  //bool n_check = false;
  //bool vowel_check = false;
  //bool consonant_check = false;
  //consonant_pair_check = false;
  int state = 0;
  int charpos = 0;
  while (s[charpos] != '\0') 
    {
      if(state == 0 && count(vowel.begin(), vowel.end(), s[charpos]))
      {
          state = 6;
      }
      else if(state == 6 && s[charpos] == 'n')
      {
          state = 7;
      }
      else if(state == 0 && count(consonant_only.begin(), consonant_only.end(), s[charpos]))
      {
          state = 5;
      }
      else if(state == 5 && count(vowel.begin(), vowel.end(), s[charpos]))
      {
          state = 6;
      }
      else if(state == 0 && count(consonant_pair_y.begin(), consonant_pair_y.end(), s[charpos]))
      {
          state = 1;
      }
      else if (state == 1 && s[charpos] == 'y')
      {
          state = 5;
      }
      else if (state == 1 && count(vowel.begin(), vowel.end(), s[charpos]))
      {
          state = 6;
      }
      else if( state == 0 && s[charpos] == 't')
      {
          state = 2;
      }
      else if(state == 2 && s[charpos] == 's')
      {
          state = 5;
      }
      else if(state == 2 && count(vowel.begin(), vowel.end(), s[charpos]))
      {
          state = 6;
      }
      else if( state == 0 && s[charpos] == 's')
      {
          state = 2;
      }
      else if(state == 2 && s[charpos] == 'h')
      {
          state = 5;
      }
      else if(state == 2 && count(vowel.begin(), vowel.end(), s[charpos]))
      {
          state = 6;
      }
      else if(state == 0 && s[charpos] == 's')
      {
          state = 3;
      }
      else if(state == 3 && s[charpos] == 'h')
      {
          state = 5;
      }
      else if(state == 3 && count(vowel.begin(), vowel.end(), s[charpos]))
      {
          state = 6;
      }
      else if(state == 0 && s[charpos] == 'c')
      {
          state = 4;
      }
      else if(state == 4 && s[charpos] == 'h')
      {
          state = 5;
      }
      else if(state == 6 && count(vowel.begin(), vowel.end(), s[charpos]))
      {
          state = 6;
      }
      else if(state == 6 && count(consonant_only.begin(), consonant_only.end(), s[charpos]))
      {
          state = 5;
      }
      else if(state == 6 && count(consonant_pair_y.begin(), consonant_pair_y.end(), s[charpos]))
      {
          state = 1;
      }
      else if(state == 6 && s[charpos] == 't')
      {
          state = 2;
      }
      else if(state == 6 && s[charpos] == 's')
      {
          state = 3;
      }
      else if(state == 6 && s[charpos] == 'c')
      {
          state = 4;
      }
      
      else if(state == 7 && count(vowel.begin(), vowel.end(), s[charpos]))
      {
          state = 6;
      }
      else if(state == 7 && count(consonant_only.begin(), consonant_only.end(), s[charpos]))
      {
          state = 5;
      }
      else if(state == 7 && count(consonant_pair_y.begin(), consonant_pair_y.end(), s[charpos]))
      {
          state = 1;
      }
      else if(state == 7 && s[charpos] == 't')
      {
          state = 2;
      }
      else if(state == 7 && s[charpos] == 's')
      {
          state = 3;
      }
      else if(state == 7 && s[charpos] == 'c')
      {
          state = 4;
      }
      else
	      return(false);
	  //cout << "Char: " << s[charpos] << endl; 
	  //cout << "State: " << state << endl;
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 6 || state == 7) return(true);  // end in a final state
   else return(false);
}

// PERIOD DFA 
// Done by: Nam Cuong Tran
bool period (string s)
{  // complete this **
  if(s == ".")
    return true;
  return false;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Nam Cuong Tran

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR};

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
string reverved_words_map(string word)
{
    string type;
    map<string, string> reservedwords_table;
    reservedwords_table.insert(pair<string, string>("masu", "VERB"));
    reservedwords_table.insert(pair<string, string>("masen", "VERBNEG"));   
    reservedwords_table.insert(pair<string, string>("mashita", "VERBPAST"));
    reservedwords_table.insert(pair<string, string>("masendeshita", "VERBPASTNEG"));
    reservedwords_table.insert(pair<string, string>("desu", "IS"));
    reservedwords_table.insert(pair<string, string>("deshita", "WAS"));
    reservedwords_table.insert(pair<string, string>("o", "OBJECT"));
    reservedwords_table.insert(pair<string, string>("wa", "SUBJECT"));
    reservedwords_table.insert(pair<string, string>("ni", "DESTINATION"));
    reservedwords_table.insert(pair<string, string>("watashi", "PRONOUN"));
    reservedwords_table.insert(pair<string, string>("anata", "PRONOUN"));
    reservedwords_table.insert(pair<string, string>("kare", "PRONOUN"));
    reservedwords_table.insert(pair<string, string>("kanojo", "PRONOUN"));
    reservedwords_table.insert(pair<string, string>("sore", "PRONOUN"));
    reservedwords_table.insert(pair<string, string>("mata", "CONNECTOR"));
    reservedwords_table.insert(pair<string, string>("soshite", "CONNECTOR"));
    reservedwords_table.insert(pair<string, string>("shikashi", "CONNECTOR"));
    reservedwords_table.insert(pair<string, string>("dakara", "CONNECTOR"));

    for(int i = 0; i < reservedwords_table.size(); i++)
    {
        if(reservedwords_table[word] != "")
        {
            type = reservedwords_table[word];
            return type;
        }
    }
    return "none";
}

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file
// For the display names of tokens - must be in the same order as the tokentype.
string tokenName[16] = {"ERROR", "WORD1", "WORD2", "PERIOD", "EOFM", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR"}; 
// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// Done by: Jorge Diaz
int scanner(tokentype& tt, string& w)
{
    // Grab the next word from the file via fin
    cout << ".....Scanner was called..." << endl;
    fin >> w;  // grab next word from the file via fin
    cout << ">>>>>       Word is:" << w << endl;   

    if( w == "eofm")
    return EOFM;

    // passing token w into word DFA
    if(word(w)){
        // checks if token w is a reserved word
        if(reverved_words_map(w) == "none")
        {
            // checks if last character is uppercase
            if(isupper(w.back()))
                tt = WORD2; // ends in E or I
            else
                tt = WORD1;
        }
        else{
            string type = reverved_words_map(w);
            if (type == "VERB")
                tt = VERB;
            else if(type == "VERBNEG")
                tt = VERBNEG;
            else if(type == "VERBPAST")
                tt = VERBPAST;
            else if(type == "VERBPASTNEG")
                tt = VERBPASTNEG;
            else if(type == "IS")
                tt = IS;
            else if(type == "WAS")
                tt = WAS;
            else if(type == "OBJECT")
                tt = OBJECT;
            else if(type == "SUBJECT")
                tt = SUBJECT;
            else if(type == "DESTINATION")
                tt = DESTINATION;
            else if(type == "PRONOUN")
                tt = PRONOUN;
            else if(type == "CONNECTOR")
                tt = CONNECTOR;
        }
    }
    // passes token w into PERIOD DFA
    else if(period(w))
    {
        tt = PERIOD;
    }
    // if token doesnt finish in a final state then lexical error 
    else{
        cout << ">>>>>Lexical Error: The string is not in my language" << endl;
        tt = ERROR;
    }
    // returns the type 
    return tt;
}//the end of scanner


// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis
int main()
{
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str(), fstream::in);

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl; 
       cout << endl;  
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end

