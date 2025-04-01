#include <iostream>
#include "SyntaxAnalyzer.h"

int main() {
    ifstream lexemes("lexemes.txt");
    // ofstream sourcelexemes("sourcelexemes.txt");
    SyntaxAnalyzer SyntaxAnalyzer(lexemes);
    return 0;
}
