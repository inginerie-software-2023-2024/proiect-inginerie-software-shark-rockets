from collections import Counter
import re


def sample(words):
    word_lengths = [len(word) for word in words]
    frequencies = Counter(word_lengths)
    frequencies = {str(k): str(v) for k, v in frequencies.items()}
    return frequencies

def word_counter(sentences):
    words = [word for sentence in sentences for word in sentence.strip('.').split()]
    frequencies = Counter(words)
    frequencies = {str(k): str(v) for k, v in frequencies.items()}
    return frequencies

def real_estate(csv_lines):
    good_deals = set()

    for line in csv_lines:
        parts = line.split(',')
        num_bedrooms = int(parts[1])
        price = int(parts[2])
        if num_bedrooms * 20000 > price:
            good_deals.add(line)

    return good_deals



def genomic_sample(genomic_samples):
    PATTERN="ATC"
    ans = 0
    for sample in genomic_samples:
        count = len(re.findall(PATTERN,sample))
        ans += count
    
    return {f"Occurences[{PATTERN}]":str(ans)}

