#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;
// Erika Mark Evan
// coding skills
   // evan - 2 , mark -3 erika - 2
// procrastination
   // erika - 3 mark - 2 evan 4
// communication
 //   erika - 4 mark - 4 evan - 5

class SyntaxAnalyzer{
private:
    vector<string> lexemes;
    vector<string> tokens;
    vector<string>::iterator lexitr;
    vector<string>::iterator tokitr;
    // map of variables and their datatype
    // i.e. sum t_integer
    map<string, string> symboltable;
    // other private methods
    bool addSymbol(string& value, string& lexeme);
    bool vdec(); // erika
    int vars(); // evan
    bool stmtlist(); // erika
    int stmt(); // mark
    bool ifstmt(); // mark
    bool elsepart(); // erika
    bool whilestmt(); // evan
    bool assignstmt(); // evan
    bool inputstmt(); // erika
    bool outputstmt(); // mark
    bool expr(); // evan
    bool simpleexpr();  // mark
    bool term(); //  erika
    bool logicop(); // mark
    bool arithop(); // evan
    bool relop(); // erika

public:
    SyntaxAnalyzer(istream& infile);
    // pre: 1st parameter consists of an open file containing a source code's
    //	valid scanner/lexical analyzer output.  This data must be in the form: token : lexeme
    // post: the vectors have been populated

    bool parse();
    // pre: none
    // post: The lexemes/tokens have been parsed.
    // If an error occurs, a message prints indicating the token/lexeme pair
    // that caused the error.
    // If no error, vectors contain syntactically correct source code
};

#endif
