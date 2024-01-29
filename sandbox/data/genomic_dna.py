# pip install numpy
# pip install pandas
# run this in nfs/user/data/genomic_dna

import numpy as np
import pandas as pd
import os

# generate a large set of genomic sequences

def generate(num_files=30, min_sequences=80, max_sequences=120, dir='.', sequence_length=50):
    dna = ['A', 'C', 'G', 'T']
    dna = np.array(dna)

    for t in range(num_files):
        sequences = []
        for i in range(np.random.randint(min_sequences, max_sequences)):
            seq = np.random.choice(dna, size=sequence_length)
            seq = ''.join(seq)
            sequences.append(seq)

        sequences = np.array(sequences)
        df = pd.DataFrame(sequences, columns=['sequence'])
        
        file_path = os.path.join(dir, f'sequences_{t}.csv')
        df.to_csv(file_path, index=False)
        # print(f"Wrote {file_path}")

        del sequences, df

if __name__ == "__main__":
    generate(min_sequences=80000,max_sequences=120000,sequence_length=1000)
