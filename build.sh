g++ -g -mavx get_cycles.c -I. main.cpp bench.cpp -o default
g++ -g -mavx -O0 get_cycles.c -I. main.cpp bench.cpp -o o0
g++ -g -mavx -O1 get_cycles.c -I. main.cpp bench.cpp -o o1
g++ -g -mavx -O2 get_cycles.c -I. main.cpp bench.cpp -o o2
g++ -g -mavx -O3 get_cycles.c -I. main.cpp bench.cpp -o o3
g++ -g -mavx -O3  -ftree-vectorize get_cycles.c -I. main.cpp bench.cpp -o o3_vec
g++ -g -mavx -Ofast -ftree-vectorize get_cycles.c -I. main.cpp bench.cpp -o ofast_vec
g++ -g -mavx -O3 -funroll-loops get_cycles.c -I. main.cpp bench.cpp -o o3_unroll
g++ -g -mavx -O3 -funroll-loops get_cycles.c -I. test.cpp bench.cpp -o test
