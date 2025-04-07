#include "SyntaxAnalyzer.h"
#include <istream>
#include <unordered_set>

// erika
// VDEC   var  VARS  [VARS]m | Ө
bool SyntaxAnalyzer::vdec() { // GOOD
    cout << "in vdec" << endl;
    if (tokitr != tokens.end()) {
        // if they didnt choose to delcare variables it returns true
        if (*tokitr != "t_var") {
            cout << "returning true from vdec" << endl;
            return true;
        }
        while ( *tokitr == "t_var"){
            cout << "in while loop" << endl;
            tokitr++; lexitr++;
            if (!vars()) {
                cout << "returning false from vdec" << endl;
                return false;
            }
        }
        cout << "returning true from vdec1" << endl;
        return true;
    }
    cout << "returning false from vdec1" << endl;
    return false;
}
// evan
int SyntaxAnalyzer::vars() { // GOOD
    cout << "INSIDE VARS" << endl;
    if(tokitr != tokens.end()) {
        if (*tokitr != "t_string" && *tokitr != "t_integer") {
            cout << "returning 2 from vdec" << endl;
            return 2;
        }
        cout << *tokitr << endl;
        if(*tokitr == "t_string" ||*tokitr == "t_integer") {
            string value = *lexitr;//used later for symbol table
            tokitr++; lexitr++;
            if (tokitr != tokens.end() && *tokitr == "t_id")  {
                symboltable[*lexitr] = value; //adds to symbol table
                tokitr++;lexitr++;
                while (tokitr != tokens.end() && *tokitr == "s_comma") {
                    cout << "in while loop found more than one id" << endl;
                    tokitr++; lexitr++;
                    if (tokitr != tokens.end() && *tokitr == "t_id") {
                        tokitr++; lexitr++;
                    } else {
                        cout << "error in declaring" << endl;
                        return 0;
                    }
                }
                if (tokitr != tokens.end() && *tokitr == "s_semi") {
                    tokitr++ ; lexitr++;
                    cout << "correct delcaration " << endl;
                    return 1;
                }
            }
        }
    }
    cout << "idk what error" << endl;
    return 0;
}
// erika
bool SyntaxAnalyzer::stmtlist() { // GOOD
    //This will loop until it gets returned 0,2, stmt will handle if its null
    // while (tokitr != tokens.end()) {
    //     int stmtResult = stmt();
    //     //0 -> Stmt error (bad stmt format)
    //     if (stmtResult == 0) {
    //         return false;
    //     }
    //     //2 -> no statement
    //     if (stmtResult == 2) {
    //         return true;
    //     }
    // }
    // //Was able to successfully go through a statments
    // return true;
    if (tokitr != tokens.end()) {
        int stmtResult = stmt();
        while(stmtResult == 1) {
            stmtResult= stmt();
            cout << "stmt parsing while code :" << stmtResult << endl;
        }
        if (stmtResult == 2 || stmtResult == 1) {
            cout <<" stmt processed code: "  << stmtResult << endl;
            return true;
        }
        if (stmtResult == 0) {
            cout <<" error stmt parsing" << endl;
        }
    }
}
// mark
int SyntaxAnalyzer::stmt() { // GOOD
    cout << "IN STMT" << endl;
    // unordered_set<string> statTokens = {"t_if","t_while", "t_id", "t_input", "t_output"};
    // if (tokitr != tokens.end() && statTokens.contains(*tokitr)) {
    //     if (ifstmt() || whilestmt() ||
    //     assignstmt() || inputstmt() ||
    //     (outputstmt())){
    //         return 1;
    //     }
    //     else {return 0;}
    // }
    // //No statement (null)
    // return 2;
    if (tokitr != tokens.end() ){
        cout << "checking statement type" << endl;
        if (*tokitr != "t_while" && *tokitr != "t_if" && *tokitr != "t_output" && *tokitr != "t_input" && (*tokitr != "t_id" && symboltable.contains(*lexitr) )) {
            // no statement selected
            cout << " no statement selected" << endl;
            return 2;
        }
        if (whilestmt() || ifstmt() || outputstmt() || inputstmt() || assignstmt()) {
            cout << "successful statement" << endl;
            return 1;
        }
        cout << "error with a statement "<< endl;
        return 0;
    }
}
// mark
bool SyntaxAnalyzer::ifstmt() { //GOOD
    if (tokitr != tokens.end()) {
        if (*tokitr == "t_if") {
            tokitr++;lexitr++;
            if (tokitr != tokens.end() && *tokitr == "s_lparen") {
                tokitr++;lexitr++;
                if (expr()) {
                    if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                        tokitr++;lexitr++;
                        if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
                            tokitr++;lexitr++;
                            if (stmtlist()) {
                                if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                                    cout << "second rbrace"<< endl;
                                    tokitr++;lexitr++;
                                    elsepart();
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
bool SyntaxAnalyzer::elsepart() { // GOOD
    if (tokitr != tokens.end()) {
        if (*tokitr != "t_else") {
            return true;
        }
        if (*tokitr == "t_else") {
            tokitr++; lexitr++;
            if (tokitr != tokens.end() && *tokitr == "s_lbrace"){
                tokitr++; lexitr++;
                if (stmtlist()) {
                    if(tokitr != tokens.end() && *tokitr == "s_rbrace" ) {
                        tokitr++; lexitr++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// evan
bool SyntaxAnalyzer::whilestmt() {
    cout << "INSIDE WHILE" << endl;
    if (tokitr != tokens.end()) {
        if (tokitr != tokens.end() && *tokitr == "t_while") {
            tokitr++; lexitr++;
            if (tokitr != tokens.end() && *tokitr == "s_lparen") {
                tokitr++; lexitr++;
                if (tokitr != tokens.end()) {
                    if (expr()) {
                        cout << "valid expr found in while loop" << endl;
                        if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                            cout << "valid rparen" << endl;
                            tokitr++; lexitr++;
                            if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
                                cout << "valid lparen" << endl;
                                tokitr++; lexitr++;
                                if (stmtlist()) {
                                    if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                                        tokitr++; lexitr++;
                                        cout << "valid whilestmt found" << endl;
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "false while loop" << endl;
    return false;
}
// evan
bool SyntaxAnalyzer::assignstmt() {
    cout << "INSIDE ASSIGN" << endl;
    if (tokitr != tokens.end()) {
        cout << "going to check assign : " << *lexitr << endl;
        if (*tokitr == "t_id" && symboltable.contains(*lexitr)) {
            cout << "valid ID" << endl;
            tokitr++; lexitr++;
            if (tokitr != tokens.end() && *tokitr == "s_assign") {
                tokitr++; lexitr++;
                cout << "going to check expr : " << *lexitr << endl;
                if (tokitr != tokens.end() && expr()) {
                    cout << "valid expr" << endl;
                    if (tokitr != tokens.end() && *tokitr == "s_semi") {
                        tokitr++;lexitr++;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
//erika
bool SyntaxAnalyzer::inputstmt() { // GOOD
    if (tokitr != tokens.end()) {
        if (*tokitr == "t_input") {
            tokitr++; lexitr++;
            if (*tokitr == "s_lparen") {
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
bool SyntaxAnalyzer::outputstmt() { // GOOD
    if (tokitr != tokens.end()) {
        if (*tokitr == "t_output") {
            cout << "printing to console" << endl;
            tokitr++;lexitr++;
            if (tokitr != tokens.end() && *tokitr == "s_lparen") {
                tokitr++;lexitr++;
                if (tokitr != tokens.end()) {
                    //check both cases (EXPR) or (text)
                    if (*tokitr == "t_text") {
                        tokitr++;lexitr++;
                        if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                                tokitr++;lexitr++;
                                return true;
                            }
                        }
                    else if (expr()){
                        cout << "in output expr" << endl;
                        if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                            tokitr++;lexitr++;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
// evan
bool SyntaxAnalyzer::expr() {
    cout << "INSIDE EXPR : " << *lexitr << endl;
    // if (tokitr != tokens.end()) {
    //     if (simpleexpr()) {
    //         cout << "simple epxr found " << endl;
    //         if (tokitr!= tokens.end() && !logicop()) {
    //             tokitr--; lexitr--;//decrement because logicop moved it and failed
    //             return true;
    //         }
    //         cout << "logicop found " << endl;
    //         if (tokitr != tokens.end() && simpleexpr()) {
    //             return true;
    //         }
    //         cout << "issue with simpleexpr" << endl;
    //         return false;
    //     }
    // }
    // return false;
    if (tokitr != tokens.end()) {
        if (simpleexpr()) {
            cout << "found simpleexption" << endl;
            if (tokitr!= tokens.end() && !logicop()) {
                cout << "just simpleexption" << endl;
                // tokitr--; lexitr--;//decrement because logicop moved it and failed
                return true;
            }
            if (tokitr != tokens.end() && !simpleexpr()) {
                return false;
            }
            return true;
        }
    }
    return false;
}

//mark
bool SyntaxAnalyzer::simpleexpr() {
    cout << "inside simpleexpr" << endl;
    if (tokitr != tokens.end()) {
        if (term()) {
            if (arithop()) {
                //case 1 term arith term
                if (term()) {
                    return true;
                }
            }
            if (relop( )) {
                //case 2 term relop term
                if (term()) {
                    return true;
                }
            }
            //if its just a term
            // lexitr++, tokitr++;
            return true;
        }
    }
    return false;
}

//  erika
// TERM    number | text |  id  | (EXPR)
bool SyntaxAnalyzer::term() {
    if (tokitr != tokens.end()) {
        if ( *tokitr == "t_id" || *tokitr == "t_number" || *tokitr == "t_text" ) {
            tokitr++; lexitr++;
            return true;
        }
        if (*tokitr == "l_paren") {
            *tokitr++; lexitr++;
            if (expr()) {
                if (*tokitr == "r_paren") {
                    cout << "Correct term : " << *lexitr << endl;
                    *tokitr++; lexitr++;
                    return true;
                }
            }
        }
    }
    cout << "Incorrect term : " << *lexitr << endl;
    return false;
}
//mark
bool SyntaxAnalyzer::logicop() { // GOOD
    if (tokitr != tokens.end()) {
        if (*tokitr == "and" || *tokitr == "or") {
            tokitr++;lexitr++;
            return true;
        }
    }
    cout << "Incorrect logic operator : " << *lexitr << endl;
    return false;
}

// evan
bool SyntaxAnalyzer::arithop(){ // GOOD
    cout << "INSIDE ARITH checking " << endl;
    if (tokitr != tokens.end()) {
        if (*tokitr == "s_plus" || *tokitr == "s_minus" ||  *tokitr == "s_div") {
            tokitr++;lexitr++;
            return true;
        }
    }
    cout << "Incorrect arithmetic operator : " << *lexitr << endl;
    return false;
}

// erika
// relop will check if the current token is a relational operator and moves the tokitr along adn returns true if it is
// otherwise it returns false
bool SyntaxAnalyzer::relop() { // GOOD
    if (tokitr != tokens.end()) {
        if ( *tokitr == "s_lt" || *tokitr == "s_gt" || *tokitr == "s_eq" || *tokitr == "s_ne" ) {
            tokitr++; lexitr++;
            cout << "valid relational operator" << endl;
            return true;
        }
    }
    cout << "Incorrect relational operator : " << *lexitr << endl;
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
        lexemes.push_back(line.substr(pos+3, line.length()));
        getline(infile, line);
    }
    cout << "population successful";

}

// pre: none
// post: The lexemes/tokens have been parsed.
// If an error occurs, a message prints indicating the token/lexeme pair
// that caused the error.
// If no error, vectors contain syntactically correct source code
bool SyntaxAnalyzer::parse() {
    tokitr = tokens.begin();
    lexitr = lexemes.begin();
    if (tokitr != tokens.end()) {
        if(vdec()){
            if (tokitr != tokens.end() && *tokitr == "t_main"){
                cout << "found main" << endl;
                tokitr++; lexitr++;
                if(tokitr != tokens.end() && *tokitr == "s_lbrace"){
                    cout << "found left brace" << endl;
                    tokitr++; lexitr++;
                    if(stmtlist()){
                        cout << *lexitr << " = " <<  "} " << endl;
                        if(tokitr != tokens.end() && *tokitr == "s_rbrace"){
                            cout << "found right brace program was successful" << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }
    if (tokitr == tokens.end() ){
        tokitr--; lexitr--;
    }
    cout << "Error reading file at: " << *lexitr << endl;
    return false;
}
