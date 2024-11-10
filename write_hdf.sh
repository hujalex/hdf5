g++ -std=c++20 -I/usr/include/hdf5/serial -L/usr/lib/x86_64-linux-gnu/hdf5/serial -o hdf53 hdf53.cpp -lhdf5 -lhdf5_cpp
    # rm example*
# for i in {1..1000}; do
    ./hdf53

# done
python3 hdf52.py
