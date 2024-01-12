# pip install lorem
# run this in nfs/user/data/lorem/

import lorem

num_files = 10
num_sentences_per_file = 30

for i in range(num_files):
    with open(f"{i}.txt", "w") as f:
        for _ in range(num_sentences_per_file):
            f.write(lorem.sentence() + "\n")
