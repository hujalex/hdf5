import pandas as pd
import h5py

df = pd.read_csv("astrum-wsc_44_publish.csv")

print(len(df.columns))

df2 = pd.read_csv('csv_table.csv');
print(df2)