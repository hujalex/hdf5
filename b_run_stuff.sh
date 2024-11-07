g++ -std=c++20 -I/usr/include/hdf5/serial -L/usr/lib/x86_64-linux-gnu/hdf5/serial -o hdf52 hdf52.cpp -lhdf5 -lhdf5_cpp
# rm example*
./hdf52

# python3 hdf5.py 
