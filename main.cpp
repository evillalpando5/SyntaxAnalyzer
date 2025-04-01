#include <iostream>
#include "SyntaxAnalyzer.h"

int main() {
    ifstream lexemes("sourcelexemes.txt");
    SyntaxAnalyzer SyntaxAnalyzer(lexemes);
    return 0;
}
