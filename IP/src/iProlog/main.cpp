/*
==============================================================================================
Author: Ram Aakarsh Iruvanti.
Modifications and Enhancements: Karthik Venkataramana Pemmaraju.
Compilation:g++ main.cpp -std=c++11  
Written on 12/11/2017
===============================================================================================
*/

#include "Engine.h"
#include "Prog.h"
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>

using namespace std; 
#ifndef MAIN
#define MAIN
namespace iProlog
{
    class MainClass 
    {  
        public:  
            static void println(void *const o){   
                    cout << (char *)o << endl;
            }

            static void pp(void *const o){
                    cout << (char *)o << endl;
            }
            
            static void run(const std::string& fname){
                std::chrono::high_resolution_clock::time_point start, end; 
                bool p = true;
                string fname0 = fname+".nl";
                std::cout << fname0 <<endl;
                Engine *E;
                Prog *P;
                P = new Prog(fname0);
                P -> ppCode();
                E = new Engine(fname0);
                pp((void*)"RUNNING");   
                start = std::chrono::high_resolution_clock::now(); // start the clock().
                E->run();
                end = std::chrono::high_resolution_clock::now(); // End of our timer
                std::chrono::duration<double> diff = end-start;
                cout << "TIME TAKEN TO RUN =" << diff.count ()/ 100000.0 << " SECONDS " << endl;   
            }  
    };
}

int main(int argc, char* argv[]) {
    iProlog::MainClass::run(argv[1]);
    return 0;  
}  

#endif