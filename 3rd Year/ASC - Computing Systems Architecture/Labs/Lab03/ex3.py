import random
from concurrent.futures import ThreadPoolExecutor

random.seed(0)

dna_samples = [[random.choice('ATGC') for _ in range(10000)] for _ in range(100)]

dna_sequence = ['C', 'C', 'A', 'G', 'C', 'C', 'G', 'C', 'G', 'T', 'T', 'G']

def f_executor(index):
    sample = dna_samples[index]
    i = 0
    
    for c in sample:
        if dna_sequence[i] == c:
            i += 1
            if i == len(dna_sequence):
                return f"DNA Sequence found in sample {index}"
        else:
            i = 0
    
    return f"DNA Sequence not found in sample {index}"


if __name__ ==  "__main__":
    thread_pool_executor = ThreadPoolExecutor(30)

    results = []

    with thread_pool_executor:
        for i in range(len(dna_samples)):
            results.append(thread_pool_executor.submit(f_executor, i))
        
        for r in results:
            print(r.result())