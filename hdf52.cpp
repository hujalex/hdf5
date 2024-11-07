#include <H5Cpp.h>
#include <vector>
#include <string>
#include <iostream>

using namespace H5;

// Constants for the HDF5 file, dataset, and table
const H5std_string FILE_NAME("example.h5");
const H5std_string DATASET_NAME("SimpleDataset");
const H5std_string TABLE_NAME("ExampleTable");

// Define a struct to represent a row in the table
struct TableRow {
    int id;
    float value;
    char name[16]; // Fixed-size character array for the name
};

// Function to create and write a dataset
void createDataset(H5File &file) {
    const hsize_t datasetSize[1] = {10}; // Size of the dataset
    DataSpace dataspace(1, datasetSize); // 1-dimensional dataspace

    // Define some data to write to the dataset
    std::vector<int> data(datasetSize[0]);
    for (int i = 0; i < datasetSize[0]; ++i) {
        data[i] = i * 2; // Example data
    }

    // Create the dataset and write the data
    DataSet dataset = file.createDataSet(DATASET_NAME, PredType::NATIVE_INT, dataspace);
    dataset.write(data.data(), PredType::NATIVE_INT);
    std::cout << "Dataset created and data written successfully.\n";
}

// Function to create and write a table (compound data type)
void createTable(H5File &file) {
    // Define the compound datatype for the table
    CompType tableType(sizeof(TableRow));
    tableType.insertMember("ID", HOFFSET(TableRow, id), PredType::NATIVE_INT);
    tableType.insertMember("Value", HOFFSET(TableRow, value), PredType::NATIVE_FLOAT);
    tableType.insertMember("Name", HOFFSET(TableRow, name), StrType(PredType::C_S1, 16));

    // Define the dataspace for the table (unlimited in one dimension)
    const hsize_t initialTableSize[1] = {5};
    const hsize_t maxTableSize[1] = {H5S_UNLIMITED};
    const hsize_t chunkSize[1] = {5}; // Chunk size for extensibility
    DataSpace tableSpace(1, initialTableSize, maxTableSize);

    // Set up chunked dataset creation property for the table
    DSetCreatPropList propList;
    propList.setChunk(1, chunkSize);

    // Create the dataset for the table
    DataSet tableDataset = file.createDataSet(TABLE_NAME, tableType, tableSpace, propList);

    // Create some example data for the table
    std::vector<TableRow> tableData = {
        {1, 3.14f, "Row1"},
        {2, 2.71f, "Row2"},
        {3, 1.61f, "Row3"},
        {4, 0.57f, "Row4"},
        {5, 1.41f, "Row5"}
    };

    // Write the initial data to the table dataset
    tableDataset.write(tableData.data(), tableType);
    std::cout << "Table created and data written successfully.\n";
}
void appendDataToFile(H5File &file, const std::vector<TableRow> &data) {
    // Open the existing dataset for the table
    DataSet tableDataset = file.openDataSet(TABLE_NAME);

    // Get the current dataspace of the dataset
    DataSpace fileSpace = tableDataset.getSpace();

    // Get the current size of the dataset (number of rows)
    hsize_t currentSize[1];
    fileSpace.getSimpleExtentDims(currentSize, NULL);

    // Calculate new size based on the data to append
    hsize_t newSize[1] = {currentSize[0] + data.size()};  // Add the new data to the current size

    // Extend the dataset to the new size before setting up the hyperslab
    tableDataset.extend(newSize);

    // Refresh fileSpace to match the newly extended size
    fileSpace = tableDataset.getSpace();

    // Define memory and file dataspaces for the write operation
    hsize_t count[1] = {data.size()};
    DataSpace memSpace(1, count);

    // Set the offset where the new data will be written
    hsize_t offset[1] = {currentSize[0]};  // Start at the end of the current data

    // Select the hyperslab in the file where the new data will be written
    fileSpace.selectHyperslab(H5S_SELECT_SET, count, offset);

    // Write the data to the extended region
    tableDataset.write(data.data(), tableDataset.getDataType(), memSpace, fileSpace);

    std::cout << "Data successfully appended to the table.\n";
}


int main() {
    try {
        // Create an HDF5 file
        // H5File file(FILE_NAME, H5F_ACC_TRUNC);
        H5File file(FILE_NAME, H5F_ACC_RDWR);

        

        // // Create a simple dataset and a table in the file
        // createDataset(file);
        // createTable(file);
// Data to append
        std::vector<TableRow> new_data = {
            {9, 9.99f, "Row7"},
            {8, 8.88f, "Row8"},
            {9, 9.99f, "Row9"},
            {8, 8.88f, "Row10"},
            
        };

        // Append new data to the table
        appendDataToFile(file,new_data);

        std::cout << "File created with dataset and table.\n";
    } catch (FileIException &error) {
        error.printErrorStack();
        return -1;
    } catch (DataSetIException &error) {
        error.printErrorStack();
        return -1;
    } catch (DataSpaceIException &error) {
        error.printErrorStack();
        return -1;
    }

    return 0;
}
