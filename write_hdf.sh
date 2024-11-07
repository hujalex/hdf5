g++ -std=c++20 -I/usr/include/hdf5/serial -L/usr/lib/x86_64-linux-gnu/hdf5/serial -o hdf52 hdf52.cpp -lhdf5 -lhdf5_cpp
    # rm example*
#for i in {1..10000}; do
    ./hdf52
# done