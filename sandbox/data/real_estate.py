# pip install lorem
# pip install numpy
# run this in nfs/user/data/real_estate/

import lorem
import numpy as np

num_files = 5
num_entries_per_file = 10

for i in range(num_files):
    with open(f"{i}.txt", "w") as f:
        for _ in range(num_entries_per_file):
            # format: address,num_bedrooms,price
            f.write(
                lorem.text().split()[0]
                + ","
                + str(np.random.randint(1, 5 + 1))
                + ","
                + str(np.random.randint(30000, 60000 + 1))
                + "\n"
            )
