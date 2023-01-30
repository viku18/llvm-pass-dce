# llvm-pass-dce
Instruction to execute the pass :

Build:
1) Go to directory containing all these files
2) mkdir build
3) cd build
4) cmake ..
5) make


Run:
1) To run the pass on any llvm-ir files go to the directory
2) clang -O0 -emit-llvm -S prgm_name.c -o prgm_name.ll
3) opt -load build/libDeadCodeElimination.so -dead-code-elimination prgm_name.ll
