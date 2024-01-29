import lorem
import os

def generate(num_files=10, num_sentences=30, dir='.'):
    for i in range(num_files):
        with open(f"{dir}/{i}.txt", "w") as f:
            for _ in range(num_sentences):
                sentence = lorem.sentence()
                words = sentence.split()
                for word in words:
                    f.write(word + "\n")

if __name__ == "__main__":
    generate()
