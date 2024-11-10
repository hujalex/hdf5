import h5py
import pandas as pd

# Open the file using h5py and read the table data
with h5py.File("table.h5", "r") as f:
    # Read the "ExampleTable" data

    print(f.keys())

    table_data = f["ExampleTable"][:]
    # Convert to DataFrame
    df = pd.DataFrame(table_data)

    # Optionally, load the "SimpleDataset" as well
    simple_data = f["SimpleDataset"][:]
    simple_df = pd.DataFrame(simple_data, columns=["SimpleDataset"])

# Display the DataFrame
print("Table Data:")
df.to_csv('csv_table.csv', index = False)

print(df)

print(simple_df)
# print("\nSimple Dataset Data:")
# simple_df.to_csv('SimpleDataset.csv', index = False)
