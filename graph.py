#!/usr/bin/python3

import pandas as pd
import matplotlib.pyplot as plt
import csv

# ##########################
# df1 = pd.read_csv('seq.csv')

# # plt.figure(figsize=(6.8, 4.2))
# x_seq = df1['n']

# y_seq = df2['sec']
# y_seq *= 1000000

# ##########################
# df2 = pd.read_csv('par.csv')

# # plt.figure(figsize=(6.8, 4.2))
# x_par = df2['n']

# y_par = df2['sec']
# y_par *= 1000000


# a = []
# temp = 0
# for i in range(0, len(y)):
#     temp += y[i]
#     if (i%50 == 0):
#         a.append(temp/50)
#         temp = 0
    

# # df.plot(x=c, y='sec')
# plt.plot(x_seq, [y_seq, y_par])
# plt.show()
# # plt.scatter(x, y)
# # plt.xticks(x, data['month'])
# # plt.xlabel('number of elements')
# plt.ylabel('seconds [ms]')
# plt.show()


import os

### Set your path to the folder containing the .csv files
PATH = './' # Use your path

### Fetch all files in path
fileNames = os.listdir(PATH)

### Filter file name list for files ending with .csv
fileNames = [file for file in fileNames if '.csv' in file]

### Loop over all files
for file in fileNames:

    ### Read .csv file and append to list
    df = pd.read_csv(PATH + file, index_col = 0)
    
    ### Create line for every file
    plt.plot(df, label=['par','seq'])
    plt.xlabel("number of elements")
    plt.ylabel("time [ms]")
    plt.legend(loc='upper left')
### Generate the plot

plt.show()