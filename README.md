
 Hashing and hash functions1
This repository contains my solution for the implementing a hashmap to store and manage bank account information using various collision resolution strategies3.
Problem Statement
The problem statement can be found in the files. It describes the scenario, the data structures, the functions, and the strategies to be implemented. It also provides the evaluation guidelines, the submission instructions, and the points to note.
Solution Overview
My solution consists of the following files:
BaseClass.h: This file contains the declaration of the BankData class and the Account struct. It also defines some constants and helper functions.
Chaining.h, LinearProbing.h, QuadraticProbing.h, CubicProbing.h, Comp.h: These files contain the declaration of the derived classes that inherit from the BankData class and implement the respective collision resolution strategies.
Chaining.cpp, LinearProbing.cpp, QuadraticProbing.cpp, CubicProbing.cpp, Comp.cpp: These files contain the definition of the functions of the derived classes.
main.cpp: This file contains the main function that tests the functionality of the hashmap and the strategies.
How to Run
To compile and run the code, use the following commands:
g++ -std=c++11 main.cpp Chaining.cpp LinearProbing.cpp QuadraticProbing.cpp CubicProbing.cpp Comp.cpp -o main
./main
The code will prompt for the input file name and the output file name. The input file should contain the test cases in the format specified in the problem statement. The output file will contain the results of the test cases.
Competitive Part
For the competitive part, I have implemented a custom hash function and a double hashing strategy. The hash function is based on the FNV-1 algorithm, which is a fast and simple hashing function that produces a good distribution of hash values. The double hashing strategy uses a secondary hash function to compute the probe increment. The secondary hash function is also based on the FNV-1 algorithm and uses a smaller prime number as the base. The details of the hash function and the strategy are explained in the comments of the Comp.h and Comp.cpp 
