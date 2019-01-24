echo "----> NO optimisation <-------"
./default
echo " "
echo "----> g++ -O1 optimisation <-------"
./o1
echo " "
echo "----> g++ -O2 optimisation <-------"
./o2
echo " "
echo "----> g++ -O3 optimisation <-------"
./o3
echo " "
echo "----> g++ --funroll-loops optimisation <-------"
./o3_unroll
echo " "
echo "----> g++ --ftree_vectorize  optimisation <-------"
./o3_vec
echo " "
echo "----> g++ --ftree_vectorize --ofast  optimisation <-------"
./ofast_vec

