import pandas as pd
import matplotlib.pyplot as plt

data1 = pd.read_csv('askdmaskd_results.csv')
data2 = pd.read_csv('wnjrjqrjqk_results.csv')
data3 = pd.read_csv('_results.csv')

datasets = [data1, data2, data3]
messages = ["askdmaskd", "wnjrjqrjqk", ""]

for i, data in enumerate(datasets):
    plt.figure(figsize=(10, 6))  
    plt.plot(data['N'], data['AveragePreimageComplexity'], label=f'Средняя сложность второго прообраза ({messages[i]})')
    plt.plot(data['N'], data['AverageCollisionComplexity'], label=f'Средняя сложность коллизии ({messages[i]})')
    plt.xlabel('Количество бит')
    plt.ylabel('Сложность')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'plot_{messages[i]}.png') 
    plt.close()  