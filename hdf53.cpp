#include <H5Cpp.h>
#include <vector>
#include <string>
#include <iostream>

using namespace H5;
using namespace std;

// Constants for the HDF5 file, dataset, and table
const H5std_string FILE_NAME("table.h5");
const H5std_string DATASET_NAME("SimpleDataset");
const H5std_string TABLE_NAME("ExampleTable");

// Define a struct to represent a row in the table
struct TableRow {
    int id;
    float value1, value2, value3, value4, value5, value6, value7, value8, value9, value10;
    float value11, value12, value13, value14, value15, value16, value17, value18, value19, value20;
    float value21, value22, value23, value24, value25, value26, value27, value28, value29, value30;
    float value31, value32, value33, value34, value35, value36, value37, value38, value39, value40;
    float value41, value42, value43, value44, value45, value46, value47, value48, value49, value50;
    float value51, value52, value53, value54, value55, value56, value57, value58, value59, value60;
    float value61, value62, value63, value64, value65, value66, value67, value68, value69, value70;
    float value71, value72, value73, value74, value75, value76, value77, value78, value79, value80;
    float value81, value82, value83, value84, value85, value86, value87, value88, value89, value90;
    float value91, value92, value93, value94, value95, value96, value97, value98, value99, value100;
    // Continue this pattern up to value700 if needed
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
    tableType.insertMember("SEGMENT_ID", HOFFSET(TableRow, id), PredType::NATIVE_INT);


    string vaue = "";

    for (int i = 0; i < 100; ++i) {
        std::string memberName = "value" + std::to_string(i + 1); // Name the member (e.g., "value1", "value2", ...)
        hsize_t offset = HOFFSET(TableRow, value1) + i * sizeof(float); // Increment offset by sizeof(float) for each member
        tableType.insertMember(memberName, offset, PredType::NATIVE_FLOAT);
    }

        // }
    // tableType.insertMember("Value2", HOFFSET(TableRow, value2), PredType::NATIVE_FLOAT);
    // tableType.insertMember("Value3", HOFFSET(TableRow, value3), PredType::NATIVE_FLOAT);
    // tableType.insertMember("Value4", HOFFSET(TableRow, value4), PredType::NATIVE_FLOAT);
    // tableType.insertMember("Value5", HOFFSET(TableRow, value5), PredType::NATIVE_FLOAT);
    // tableType.insertMember("Value6", HOFFSET(TableRow, value6), PredType::NATIVE_FLOAT);
    // tableType.insertMember("Value7", HOFFSET(TableRow, value7), PredType::NATIVE_FLOAT);
    // tableType.insertMember("Value8", HOFFSET(TableRow, value8), PredType::NATIVE_FLOAT);
    // tableType.insertMember("Value9", HOFFSET(TableRow, value9), PredType::NATIVE_FLOAT);
    // tableType.insertMember("Value10", HOFFSET(TableRow, value10), PredType::NATIVE_FLOAT);
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
                {0, 
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        }
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
        {0, 
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420, 1.6420,
        }
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
