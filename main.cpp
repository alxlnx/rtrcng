#include <bits/stdc++.h>
#include <stdlib.h>

void f(void)
{
    int* x = (int*) calloc(10, sizeof(int));  // === malloc(10 * sizeof(int))
    x[11] = 0;         // problem 1: heap block overrun
    std::cout << "in f(): leaking?";
}                      // problem 2: memory leak -- x not freed

int main() {
    freopen("input.txt", "r", stdin);
    // Valgrind:
    // doesn't detect static/stack array errors
    // add -g to add debug info, if you don't see specific line nums, this might be why 
    // Unfortunately, Memcheck doesn't do bounds checking on global or stack arrays. We'd like to, but it's just not possible to do in a reasonable way that fits with how Memcheck works. Sorry.
    // You only need to read the documentation for the core and for the tool(s) you actually use
    // why does not broken lcs.cpp show specific lines?
    // Try -Og 
    // a reasonable compromise is to use -O = -O1.
    // -Og should be the optimization level of choice for the standard edit-compile-debug cycle,
    // offering a reasonable level of optimization while maintaining fast compilation and a good debugging experience.  It is a
    // better choice than -O0 (that's the default) for producing debuggable code because some compiler passes that collect debug information are
    // disabled at -O0.
    // Hmm, -Og disabled errors in this code. Same for -O, only -O0 works.
    // --log-file=filename 
    // It is important to understand that your program can copy around junk (uninitialised) data as much as it likes. Memcheck observes this and keeps track of the data, but does not complain. A complaint is issued only when your program attempts to make use of uninitialised data in a way that might affect your program's externally-visible behaviour. 

    f();
    std::cout << "sd";


    std::cout << '\n';
    return 0;
}