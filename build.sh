g++  -g -mavx get_cycles.c -I. main.cpp -o no_opt
g++ -g -mavx get_cycles.c -I. main.cpp -o default
g++ -g -mavx -O get_cycles.c -I. main.cpp -o o
g++ -g -mavx -O1 get_cycles.c -I. main.cpp -o o1
g++ -g -mavx -O2 get_cycles.c -I. main.cpp -o o2
g++ -g -mavx -O3 get_cycles.c -I. main.cpp -o o3
g++ -g -mavx -O3 -funroll-loops get_cycles.c -I. main.cpp -o o3_unroll
