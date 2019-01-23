g++ get_cycles.c -I. main.cpp -o no_opt
g++ -g  get_cycles.c -I. main.cpp -o default
g++ -g -O get_cycles.c -I. main.cpp -o o
g++ -g -O1 get_cycles.c -I. main.cpp -o o1
g++ -g -O2 get_cycles.c -I. main.cpp -o o2
g++ -g -O3 get_cycles.c -I. main.cpp -o o3
g++ -g -O3 -funroll-loops get_cycles.c -I. main.cpp -o o3_unroll
