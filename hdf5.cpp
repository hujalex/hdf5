// #include <H5Cpp.h>

// int main() {
//     // Create an HDF5 file
//     H5::H5File file("data.h5", H5F_ACC_TRUNC);

//     // Create a group
//     H5::Group group = file.createGroup("myGroup");

//     // Create a dataset
//     hsize_t dims[2] = {10, 10}; // Dimensions of the dataset
//     H5::DataSet dataset = group.createDataSet("myDataset", H5::DataType(H5::PredType::STD_I32BE), H5::DataSpace(2, dims));

//     // Write data to the dataset
//     int data[10][10];
//     for (int i = 0; i < 10; i++) {
//         for (int j = 0; j < 10; j++) {
//             data[i][j] = i * j;
//         }
//     }
//     dataset.write(data, H5::DataType(H5::PredType::STD_I32BE));

//     // Create a table
//     H5::CompType tableType(sizeof(int) + sizeof(float) + sizeof(char));
//     tableType.insertMember("id", 0, H5::PredType::STD_I32BE);
//     tableType.insertMember("value", sizeof(int), H5::PredType::IEEE_F32BE);
//     tableType.insertMember("name", sizeof(int) + sizeof(float), H5::StrType(H5::PredType::C_S1, 10));

//     hsize_t tableDims[1] = {5}; // Dimensions of the table
//     H5::DataSet table = group.createDataSet("myTable", tableType, H5::DataSpace(1, tableDims));

//     // Write data to the table
//     struct {
//         int id;
//         float value;
//         char name[10];
//     } tableData[5] = {
//         {1, 1.0f, "one"},
//         {2, 2.0f, "two"},
//         {3, 3.0f, "three"},
//         {4, 4.0f, "four"},
//         {5, 5.0f, "five"}
//     };
//     table.write(tableData, tableType);

//     return 0;
// }
#include <H5Cpp.h>
#include <vector>
#include <stdio.h>
#include <iostream>

using namespace H5;

// Constants for dataset
const H5std_string FILE_NAME("data.h5");
const H5std_string DATASET_NAME("incremental_data");

int main() {
    // Open or create the HDF5 file
    H5File file(FILE_NAME, H5F_ACC_TRUNC);

    // Define dataset dimensions
    const hsize_t initialSize[1] = {10};      // Initial size
    const hsize_t maxSize[1] = {H5S_UNLIMITED}; // Unlimited expansion
    const hsize_t chunkSize[1] = {5};         // Chunk size

    // Create dataspace with initial and maximum sizes
    DataSpace dataspace(1, initialSize, maxSize);

    // Set up chunked dataset creation property
    DSetCreatPropList propList;
    propList.setChunk(1, chunkSize);

    // Create the dataset
    DataSet dataset = file.createDataSet(DATASET_NAME, PredType::NATIVE_INT, dataspace, propList);

    // Incrementally write data in chunks
    std::vector<int> data = {0, 1, 2, 3, 4};
    std::vector<int> data2 = {0, 1, 2, 3, 4};
    hsize_t offset[1] = {0};  // Where the new data will be written
    hsize_t count[1] = {data.size()};

    // Write the initial chunk of data
    dataset.extend(initialSize);  // Extend dataset to initial size if needed
    DataSpace fileSpace = dataset.getSpace();
    fileSpace.selectHyperslab(H5S_SELECT_SET, count, offset);
    DataSpace memSpace(1, count);
    dataset.write(data.data(), PredType::NATIVE_INT, memSpace, fileSpace);

    // To write additional chunks, update offset and repeat
    
    offset[0] += count[0];
    data = {5, 6, 7, 8, 9};  // New data to write
    data2 = {10,11,12,13,14};
    hsize_t newSize[2] = {offset[0] + data.size(), offset[0] + data.size()};
    dataset.extend(newSize);  // Extend dataset for new data
    fileSpace = dataset.getSpace();  // Refresh fileSpace for new extents
    fileSpace.selectHyperslab(H5S_SELECT_SET, count, offset);
    
    dataset.write(data.data(), PredType::NATIVE_INT, memSpace, fileSpace);
    std::cout << "Program ran to completion\n";
    
    return 0;
}
