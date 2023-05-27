#include<iostream>
#include<fstream>
#include<string>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

// global variable
// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR, WORD1, WORD2, PERIOD, EOFM, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR};
string saved_lexeme;
tokentype  saved_token;
bool token_available = false; 
// function declaration
void story();
void s();
void after_subject();
void after_noun();
void after_object();
void noun();
void verb();
void be();
void tense();
//=====================================================
// File scanner.cpp written by: Group Number: Nam Cuong Tran, Jorge Diaz, Corbin Thaete 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Nam Cuong Tran
// RE:  (vowel | vowel n | consonant vowel | consonant vowel n |consonant-pair vowel | consonant-pair vowel n)^+ 
bool word (string s)
{
  // vector to store vowel and consonant as well as pair 
  vector<char> vowel = {'a','i','u','e','o', 'I', 'E'};
  vector <char> consonant_only= {'d', 'j', 'w', 'y', 'z'};
  vector <char> consonant_pair_y = {'b', 'g', 'h', 'k', 'm', 'n', 'p', 'r'};
  int state = 0;
  int charpos = 0;
  // loop through char in string 
  while (s[charpos] != '\0') 
    {
      // follow the logic of DFA
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
      // if not in logic then return false
      else
	      return(false);
	  //cout << "Char: " << s[charpos] << endl; 
	  //cout << "State: " << state << endl;
      charpos++;
    }//end of while

  // end in state 6 or state 7
  if (state == 6 || state == 7) return(true);  // end in a final state
   else return(false);
}

// PERIOD DFA 
// Done by: Nam Cuong Tran
bool period (string s)
{  // complete this **
  // return true if it is a .
  if(s == ".")
    return true;
  return false;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Nam Cuong Tran



// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
// fucntion to check if word in the reversed lsit
string reverved_words_map(string word)
{
    string type;
    // hard code the map
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
    // go through map and check if the word in the list or not 
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
    cout << ">>>>>Word is:" << w << endl;   
    // if reach end of file
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
        // take the type inside the map
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


//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: match fails
// Done by: Jorge Diaz 
// Expect token was missing type or got inserted before the expected token
void syntaxerror1(string saved_t, tokentype tt){    
    cout << "SYNTAX ERROR: expected " << tokenName[tt] << " but found " << saved_t << endl;
    exit(1);
}

//tokens, there is no way to choose a path.
// So exit the program as soon as this type of syntax error is found
// Type of error: switch case default error - if we do not see any of the expected
// Done by: Jorge Diaz 
void syntaxerror2(string parserFunction, string saved_lex) {    
    cout << "SYNTAX ERROR: unexpected " << saved_lex << " found in " << parserFunction << endl;
    exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: See the next token without eat it
// Done by: Nam Cuong Tran
tokentype next_token()
{
    // if reach end of file exit
   if(saved_lexeme == "eofm") exit(0);
   if (!token_available)   // if there is no saved token yet
   { 
       scanner(saved_token, saved_lexeme);  // call scanner to grab a new token
                                            // saved_token is the token type and 
                                            // saved_lexeme is the word that is read in
       token_available = true; // mark that fact that you have saved it
   }
   return saved_token;    // return the saved token
}

// Purpose: Eat up the token and release the flag
// Done by: Nam Cuong Tran
bool match(tokentype expected)
{
    // call the function
   tokentype guess = next_token();
   // if reach end of file then exit
   if(guess == EOFM) exit(0);
   if (guess != expected)   // mismatch has occurred with the next token
   {
        // calls a syntax error function here to generate a syntax error message here and do recovery
        syntaxerror1(saved_lexeme, expected);    
   }
   else  // match has occurred
   {
        token_available = false;   // eat up the token
        cout << "Matched " << tokenName[expected] << endl; // print the the token type
        return true;                        // say there was a match
   }
   return false;
}

// ----- RDP functions - one per non-term -------------------
// Done by: Nam Cuong Tran
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function
// story to start the bnf
void story()
{
   cout << "Processing <story>" << endl;
   // call s()
   s();
}
// s to start bnf
void s()
{
   cout << "Processing <s>" << endl;
    // if connector is next token then match since it is optional
    if(next_token() == CONNECTOR){
        match(CONNECTOR);
    }
    // call noun
    noun();
    // match subject
    match(SUBJECT);
    // call after subject
    after_subject();
}
// after subject non ter
void after_subject()
{
   cout << "Processing <after_subject>" << endl;
   switch(next_token())
   {
        // case verb then call verb tense and match period
      case WORD2:
         verb();
         tense();
         match(PERIOD);
         break;
        // case noun then call noun and after_noun functuon
      case WORD1: case PRONOUN: 
         noun();
         after_noun();
         break;
         // otherwise generate syntax error
      default:
         syntaxerror2("after_subject", saved_lexeme);
         break;
   }
}
void after_noun()
{
   cout << "Processing <after_noun>" << endl;
   switch (next_token())
   {
        // case be then call be and match period
      case IS: case WAS:
         be();
         match(PERIOD);
         break;
         // case destination then match it and call after_subject
      case DESTINATION:
         match(DESTINATION);
         after_subject();
         break;
         // case object then match it then call after_object
      case OBJECT:
         match(OBJECT);
         after_object();
         break;
        // otherwise generate error
      default:
         syntaxerror2("after_noun", saved_lexeme);
         break;
   }
}
void after_object()
{
   cout << "Processing <after_object>" << endl;
   switch (next_token())
   {
    // case verb then call verb tense and period
    case WORD2:
      verb();
      tense();
      if(next_token() == PERIOD) match(PERIOD);
      break;
      // case noun then call noun match(destination) verb tense and period
    case WORD1: case PRONOUN:
      noun();
      match(DESTINATION);
      verb();
      tense();
      if(next_token() == PERIOD) match(PERIOD);
      break;
      // otherwise generate error
    default:
      syntaxerror2("after_object", saved_lexeme);
      break;
   }
}
void noun()
{
   cout << "Processing <noun>" << endl;
   switch (next_token())
   {
    // word1 then match with word1
    case WORD1:
      match(WORD1);
      break;
    // pronoun then match with pronoun
    case PRONOUN:
      match(PRONOUN);
      break;
      // otherwise generate error
    default:
      syntaxerror2("noun", saved_lexeme);
      break;
   }
}
void verb()
{
    // if token is word2 then match it
   cout << "Processing <verb>" << endl;
   if(next_token() == WORD2) match(WORD2);
}
void be()
{
   cout << "Processing <be>" << endl;
   switch (next_token())
   {
    // match IS in case IS
   case IS:
      match(IS);
      break;
    // match WAS in case WAS
   case WAS:
      match(WAS);
      break;
      // otherwise generate error
   default:
      syntaxerror2("be", saved_lexeme);
      break;
   }
}
void tense()
{
    // tense include <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
   cout << "Processing <tense>" << endl;
   switch (next_token())
   {
   case VERBPAST:
      match(VERBPAST);
      break;
   case VERBPASTNEG:
      match(VERBPASTNEG);
      break;
   case VERB:
      match(VERB);
      break;
   case VERBNEG:
      match(VERBNEG);
      break;
      // if not in tense then generate error
   default:
      syntaxerror2("tense", saved_lexeme);
      break;
   }
}



string filename;

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  **
int main()
{
    // take in file name
   cout << "Enter the input file name: ";
   cin >> filename;
   fin.open(filename.c_str(),  fstream::in);
   while(true)
   {
       // calls the <story> to start parsing
      story();
      // if reach endof file then break
      if(saved_lexeme == "eofm") break;
   }
  //** closes the input file 
   fin.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
