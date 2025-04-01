#include <iostream>
#include "SyntaxAnalyzer.h"

int main() {
    ifstream lexemes("sourcelexemes.txt");
    SyntaxAnalyzer SyntaxAnalyzer(lexemes);
    SyntaxAnalyzer.parse();
    return 0;
}
