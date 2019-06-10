#include <iostream>
#include <regex>

#include "Parser.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {
    Parser *p = nullptr;
    std::string code;

    std::printf("=====================\nRobot Compiler (%d.%d)\n=====================\n", _VERSION_MAJOR,
                _VERSION_MINOR);
    std::printf("Type (Quit or quit) to quit\n");

    std::regex regex("(([Q]|[q])uit)");

    while (!std::regex_match(code, regex)) {
        while (code.empty()) {
            std::printf("\n>>> ");
#ifndef _TESTING
            std::getline(std::cin, code);
#else
            code = "let var t: int in t := t + 1";
//            code = "if(true*true) then x:=x+1 else z:=z+2";
#endif
        }

        if (_VERBOSITY >= 1)
            fprintf(stdout, ANSI_COLOR_BLUE "Compiling, please wait...\n" ANSI_COLOR_RESET);
        p = new Parser(code);
        int i = p->compile();
//        int ii = p->checkContext();
        code.clear();
        if (i == 0) {
            if (_VERBOSITY >= 1)
                fprintf(stderr, ANSI_COLOR_GREEN "\nSuccess!\n" ANSI_COLOR_RESET);
        } else {
            if (_VERBOSITY >= 1)
                fprintf(stderr, ANSI_COLOR_RED "\nFailed!\n" ANSI_COLOR_RESET);
        }
        code.clear();
#ifdef _TESTING
        exit(0);
#endif
    }

    return 0;
}