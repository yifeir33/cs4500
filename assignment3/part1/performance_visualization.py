import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import glob

path = os.getcwd()

fig = plt.figure(figsize=(10,5), dpi= 100)
allFiles = glob.glob(path + "/*.csv")
frame = pd.DataFrame()
list_ = []
for file_ in allFiles:
    df = pd.read_csv(file_, header =0, index_col= None)
    # df[' CS4500_Assn1_Part1'] =pd.to_numeric(df[' CS4500_Assn1_Part1'], errors='coerce')
    list_.append(df[[' a1p1', ' A3_a1_p1', ' CS4500A1P1', ' CS4500_Assn1_Part1',
       ' sorer', ' swd_assignment_3']])
    # print(df[' CS4500_Assn1_Part1'])




data = pd.concat(list_).groupby(level=0).mean()

print(len(data))
print(data.columns.values)
data1 = pd.read_csv(path + "/data1.csv", header =0)
# data2 = pd.read_csv(path + "/data2.csv", header =0)
# data3 = pd.read_csv(path + "/data3.csv", header =0)
# data4 = pd.read_csv(path + "/data4.csv", header =0)
# data5 = pd.read_csv(path + "/data5.csv", header =0)
# data6 = pd.read_csv(path + "/data6.csv", header =0)
# data7 = pd.read_csv(path + "/data7.csv", header =0)
# data8 = pd.read_csv(path + "/data8.csv", header =0)
# data9 = pd.read_csv(path + "/data9.csv", header =0)
# data10 = pd.read_csv(path + "/data10.csv", header =0)
#
# list_of_data = [data1,data2,data3,data4,data5,data6,data7,data8,data9,data10]




header_name = data.columns.values.tolist()
# header_name = header_name.remove(' CS4500_Assn1_Part1')
print(header_name)
row_name = data1.index
command_name = data1['Command']

ypos = np.arange(0,len(header_name))
for i in range(len(data)):
    # ax = plt.subplot(len(data),1, i+1)
    select_row_data = data.loc[i,header_name]

    new_array = np.zeros(len(header_name), np.float)
    for j in range(len(select_row_data)):
        try:
            k = float(select_row_data[j])
        except ValueError:
            new_array[j] = np.nan
        else:
            new_array[j] = k

    # if np.isnan(new_array).any():
    #     place =  np.argwhere(np.isnan(new_array))
    #     # print('here')
    #     # print(place[0,0])
    #     del header_name[place[0,0]]
    #     new_array = np.delete(new_array, place[0,0])
    #     ypos = np.arange(0,len(header_name))

    # print("ypos",len(ypos))
    # print(len(new_array))
    plt.bar(ypos,new_array, align ='center', label = "seconds")
    plt.xticks(ypos,header_name)
    plt.xlabel("Group Name" )
    plt.ylabel("Performance Speed")
    plt.title(command_name[i])

    plt.legend(loc = 'best')
    header_name = data.columns.values.tolist()

    ypos = np.arange(0, len(header_name))
    plt.savefig('performance_compare'+ str(i) + '.png')
    plt.clf()

# plt.tight_layout()

# plt.show()









