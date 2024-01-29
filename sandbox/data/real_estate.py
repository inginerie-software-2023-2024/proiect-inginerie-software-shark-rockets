# pip install lorem
# run this in nfs/user/data/real_estate/

import lorem
import os
import random

def generate(num_files=5, num_entries_per_file=10, dir='.'):
    for i in range(num_files):
        with open(os.path.join(dir, f"{i}.txt"), "w") as f:
            for _ in range(num_entries_per_file):
                # format: address,num_bedrooms,price
                f.write(
                    lorem.text().split()[0]
                    + ","
                    + str(random.randint(1, 5))
                    + ","
                    + str(random.randint(30000, 60000))
                    + "\n"
                )

if __name__ == "__main__":
    generate()
