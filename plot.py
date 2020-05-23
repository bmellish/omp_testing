import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv('/home/bmellish/omp_testing/build/omp.csv', sep=',', header=None, index_col=0)

#data.plot(kind='bar')
#plt.ylabel('Frequency')
#plt.xlabel('Nanoseconds')
plt.hist(data, bins=25, range=[82000, 84000])
plt.title('Title')

plt.show()