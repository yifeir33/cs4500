import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import glob

path = os.getcwd()

fig = plt.figure(figsize=(10,50), dpi= 100)
# allFiles = glob.glob(path + "/*.csv")
# frame = pd.DataFrame()
# list_ = []
# for file_ in allFiles:
#     df = pd.read_csv(file_, header =0, index_col= None)
#     list_.append(df)
# data = pd.concat(list_)

data = pd.read_csv(path + "/data1.csv", header =0)
print(data)


header_name = data.columns.values.tolist()
header_name = header_name[1:]
row_name = data.index
command_name = data['Command']
print(header_name)

ypos = np.arange(len(header_name))
for i in range(len(data)):
    ax = plt.subplot(len(data),1, i+1)
    select_row_data = data.loc[i,header_name]
    new_array = np.zeros(len(header_name), np.float)
    for i in range(len(select_row_data)):
        try:
            k = float(select_row_data[i])
        except ValueError:
            new_array[i] = np.nan
        else:
            new_array[i] = k
    print(new_array)
    ax.bar(ypos,new_array, label = "seconds")
    ax.set_xticklabels(header_name)
    ax.set_xlabel("Group Name" )
    ax.set_ylabel("Performance Speed")
    ax.set_title(command_name[i])

    ax.legend(loc = 'best')

plt.savefig('performance_compare.png')






plt.show()









