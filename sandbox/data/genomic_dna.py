# pip install numpy
# pip install pandas
# run this in nfs/user/data/genomic_dna

import numpy as np
import pandas as pd

# generate a large set of genomic sequences

dna = ['A', 'C', 'G', 'T']
dna = np.array(dna)
for t in range(30):
    sequences = []
    for i in range(np.random.randint(80000, 120000)):
        seq = np.random.choice(dna, size=1000)
        seq = ''.join(seq)
        sequences.append(seq)

    sequences = np.array(sequences)
    df = pd.DataFrame(sequences, columns=['sequence'])
    df.to_csv(f'sequences_{t}.csv', index=False)
    print(f"wrote sequences_{t}.csv")
    # free up memory
    del sequences
    del df
