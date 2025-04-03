#include "SyntaxAnalyzer.h"
#include <istream>
#include <unordered_set>

// erika
// VDEC   var  VARS  [VARS]m | Ө
bool SyntaxAnalyzer::vdec(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    if (tokitr != tok.end()) {
        // if they didnt choose to delcare variables it returns true
        if (*tokitr != "t_var") {
            return true;

        }
        while ( *tokitr == "t_var"){
            tokitr++; lexitr++;
            if (!vars(tok, lex, tokitr, lexitr)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
// evan
int SyntaxAnalyzer::vars(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    cout << "INSIDE VARS" << endl;
    if(tokitr != tok.end()) {
        if(*tokitr == "t_string" ||*tokitr == "t_integer") {
            tokitr++; lexitr++;
            if (tokitr != tok.end() && *tokitr == "t_id")  {

                tokitr++; lexitr++;
                while (tokitr != tok.end() && *tokitr == "s_comma") {
                    tokitr++; lexitr++;
                    if (tokitr != tok.end() && *tokitr == "t_id") {
                        tokitr++; lexitr++;
                    } else {
                        return 0;
                    }
                }
                if (tokitr != tok.end() && *tokitr == "s_semi") {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// erika
bool SyntaxAnalyzer::stmtlist(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    //This will loop until it gets returned 0,2, stmt will handle if its null
    while (tokitr != tok.end()) {
        int stmtResult = stmt(tok,lex,tokitr,lexitr);
        //0 -> Stmt error (bad stmt format)
        if (stmtResult == 0) {
            return false;
        }
        //2 -> no statement
        else if (stmtResult == 2) {
            return true;
        }

    }
    //Was able to successfully go through all statments
    return true;
}
// mark
int SyntaxAnalyzer::stmt(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    unordered_set<string> statTokens = {"t_if","t_while", "t_assign", "t_input", "t_output"};
    if (tokitr != tok.end() && statTokens.contains(*tokitr)) {
        if (ifstmt(tok,lex, tokitr,lexitr) || whilestmt(tok,lex, tokitr,lexitr) ||
        assignstmt(tok,lex, tokitr,lexitr) || inputstmt(tok,lex, tokitr,lexitr) || (outputstmt(tok,lex, tokitr,lexitr))){
            tokitr++; lexitr++;
            return 1;
        }
        else {return 0;}
    }
    //No statement (null)
    return 2;

}
// mark
bool SyntaxAnalyzer::ifstmt(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    if (tokitr != tok.end()) {
        if (*tokitr == "t_if") {
            tokitr++;lexitr++;
            if (tokitr != tok.end() && *tokitr != "s_lparen") {
                tokitr++;lexitr++;
                if (expr(tok,lex, tokitr, lexitr)) {
                    tokitr++;lexitr++;
                    if (tokitr != tok.end() && *tokitr != "s_rparen") {
                        tokitr++;lexitr++;
                        if (tokitr != tok.end() && *tokitr != "s_lbrace") {
                            tokitr++;lexitr++;
                            if (stmtlist(tok,lex, tokitr, lexitr)) {
                                if (tokitr != tok.end() && *tokitr != "s_rbrace") {
                                    tokitr++;lexitr++;
                                    elsepart(tok,lex, tokitr, lexitr);
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
// erika
bool SyntaxAnalyzer::elsepart(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    if (tokitr != tok.end()) {
        if (*tokitr != "t_else") {
            tokitr++; lexitr++;
            return true;
        }
        if (*tokitr == "t_else") {
            tokitr++; lexitr++;
            if (tokitr != tok.end() && *tokitr == "s_lbrace"){
                tokitr++; lexitr++;
                if (stmtlist(tok, lex, tokitr, lexitr)) {
                    if(tokitr != tok.end() && *tokitr == "s_rbrace" ) {
                        tokitr++; lexitr++;
                        return true;
                    }
                    return false;
                }
                return false;
            }
            return false;
        }
    }
}

// evan
bool SyntaxAnalyzer::whilestmt(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    cout << "INSIDE WHILE" << endl;
    if (tokitr != tok.end()) {
        if (tokitr != tok.end() && *tokitr == "t_while") {
            tokitr++; lexitr++;
            if (tokitr != tok.end() && *tokitr == "s_lparen") {
                tokitr++; lexitr++;
                if (tokitr != tok.end()) {
                    if (expr(tok, lex, tokitr, lexitr)) {
                        tokitr++; lexitr++;
                        if (tokitr != tok.end() && *tokitr == "s_rparen") {
                            tokitr++; lexitr++;
                            if (tokitr != tok.end() && *tokitr == "s_lbrace") {
                                tokitr++; lexitr++;
                                if (stmtlist(tok,lex, tokitr, lexitr)) {
                                    tokitr++; lexitr++;
                                    if (tokitr != tok.end() && *tokitr == "s_rbrace") {
                                        return true;
                                    }
                                }
                            }
                        }
                    }

                }
            }
        } else
            return false;
    }
}
// evan
bool SyntaxAnalyzer::assignstmt(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    cout << "INSIDE ASSIGN" << endl;
    if (tokitr != tok.end()) {
        if (*tokitr == "t_id" && symboltable.contains(*lexitr)) {
            tokitr++; lexitr++;
            if (tokitr != tok.end() && *tokitr == "s_assign") {
                tokitr++; lexitr++;
                if (tokitr != tok.end() && expr(tok, lex, tokitr, lexitr)) {
                    return true;
                }
            }
        }
    } else
        return false;
}
//erika
bool SyntaxAnalyzer::inputstmt(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    if (tokitr != tok.end()) {
        if (*tokitr == "t_input") {
            tokitr++; lexitr++;
            if (*tokitr == "s_rparen") {
                tokitr++; lexitr++;
                if (*tokitr == "t_id") {
                    tokitr++; lexitr++;
                    if (*tokitr == "s_rparen") {
                        tokitr++; lexitr++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
// mark
bool SyntaxAnalyzer::outputstmt(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    if (tokitr != tok.end()) {
        if (*tokitr == "t_output") {
            tokitr++;lexitr++;
            if (tokitr != tok.end() && *tokitr != "s_lparen") {
                tokitr++;lexitr++;
                if (tokitr != tok.end()) {
                    //check both cases (EXPR) or (text)
                    if (expr(tok,lex, tokitr, lexitr) || *tokitr == "t_text") {
                        tokitr++;lexitr++;
                        if (tokitr != tok.end()) {
                            if (*tokitr == "s_rparen") {
                                //Iterate???
                                tokitr++;lexitr++;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
// evan
bool SyntaxAnalyzer::expr(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    cout << "INSIDE EXPR" << endl;
    if (tokitr != tok.end()) {
        if (simpleexpr(tok, lex, tokitr, lexitr)) {
            tokitr++; lexitr++;
            if (tokitr != tok.end() && logicop(tok, lex, tokitr, lexitr)) {
                return true;
            } else if (simpleexpr(tok, lex, tokitr, lexitr)){
                return true;
            }
        } else {
            return false;
        }
    } else
        return false;

} 
//mark
bool SyntaxAnalyzer::simpleexpr(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    if (tokitr != tok.end()) {
        if (term(tok,lex,tokitr,lexitr)) {
            if (arithop(tok,lex,tokitr,lexitr)) {
                //case 1 term arith term
                if (term(tok,lex,tokitr,lexitr)) {
                    return true;
                }
            }
            else if (relop(tok,lex,tokitr,lexitr)) {
                //case 2 term relop term
                if (term(tok,lex,tokitr,lexitr)) {
                    return true;
                }
            }
            //if its just a term
            tokitr++; lexitr++;
            return true;
        }
        return false;
    }
}  

//  erika
// TERM    number | text |  id  | (EXPR)
bool SyntaxAnalyzer::term(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    if (tokitr != tok.end()) {
        if ( *tokitr == "t_id" || *tokitr == "t_number" || *tokitr == "t_text" ) {
            tokitr++; lexitr++;
            return true;
        }
        if (expr(tok, lex, tokitr, lexitr)) {
            return true;
        }
    }
    return false;
}
//mark
bool SyntaxAnalyzer::logicop(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    if (tokitr != tok.end()) {
        if (*tokitr == "and" || *tokitr == "or") {
            //Should I iterate or should it be assumed before the next call its iterated
            tokitr++;lexitr++;
            return true;
        }
    }
    return false;
}

// evan
bool SyntaxAnalyzer::arithop(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr){
    cout << "INSIDE ARITH" << endl;
    if (tokitr != tok.end()) {
        if (*tokitr == "s_plus" || *tokitr == "s_minus" ||  *tokitr == "s_div") {
            return true;
        }
    } else
        return false;
}

// erika
// relop will check if the current token is a relational operator and moves the tokitr along adn returns true if it is
// otherwise it returns false
bool SyntaxAnalyzer::relop(vector<string>& tok, vector<string>& lex, vector<string>::iterator& tokitr, vector<string>::iterator& lexitr) {
    if (tokitr != tok.end()) {
        if ( *tokitr == "s_lt" || *tokitr == "s_gt" || *tokitr == "s_eq" || *tokitr == "s_ne" ) {
            tokitr++; lexitr++;
            return true;
        }
    }
    return false;
}


// pre: 1st parameter consists of an open file containing a source code's
//	valid scanner/lexical analyzer output.  This data must be in the form: token : lexeme
// post: the vectors have been populated
SyntaxAnalyzer::SyntaxAnalyzer(istream& infile) {
    string line;
    getline(infile, line);
    while(!infile.eof()){
        // find the first space and split it
        int pos = line.find(" ");
        tokens.push_back(line.substr(0,pos));
        lexemes.push_back(line.substr(pos+1, line.length()));
        getline(infile, line);
    }

}

// pre: none
// post: The lexemes/tokens have been parsed.
// If an error occurs, a message prints indicating the token/lexeme pair
// that caused the error.
// If no error, vectors contain syntactically correct source code
bool SyntaxAnalyzer::parse() {
    if (tokitr != tokens.end()) {
        if(vdec(tokens, lexemes, tokitr, lexitr)){
            if (tokitr != tokens.end() && *tokitr == "t_main"){
                tokitr++; lexitr++;
                if(tokitr != tokens.end() && *tokitr == "s_lbrace"){
                        tokitr++; lexitr++;
                        if(stmtlist(tokens, lexemes, tokitr, lexitr)){
                            if(tokitr != tokens.end() && *tokitr == "s_rbrace"){
                                return true;
                        }
                    }
                }
            }
        }
    } else{
        cout << "Error reading file at:" << *tokitr << endl;
        return false;
    }
}
