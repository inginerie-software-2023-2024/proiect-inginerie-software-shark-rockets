# pip install lorem
# run this in nfs/user/data/lorem/

import lorem
import os

def generate(num_files=10,num_sentences_per_file=30,dir='.'):
    for i in range(num_files):
        with open(f"{dir}/{i}.txt", "w") as f:
            for _ in range(num_sentences_per_file):
                f.write(lorem.sentence() + "\n")

if __name__ == "__main__":
    generate()
