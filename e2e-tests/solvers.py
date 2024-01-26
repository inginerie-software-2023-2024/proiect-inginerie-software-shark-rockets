from collections import Counter

def sample(words):
    word_lengths = [len(word) for word in words]
    frequencies = Counter(word_lengths)
    return frequencies
