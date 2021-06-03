# ASC - Tema 3 - GPU Hashtable

_Grigore Lucian-Florin - 336CA_

Tema a fost realizata avand ca target GPU Tesla K40. Instalarea suitei de dezvoltare CUDA pe [Windows](https://docs.nvidia.com/cuda/cuda-installation-guide-microsoft-windows/index.html) sau [Linux](https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html).

## Introducere

### Descrierea cerintei

Implementarea unui Hashtable care va retine perechi de tipul <code>\<cheie, valoare></code> si va putea suporta urmatoarele operatii:
- **insert**: insereaza un batch de elemente. Pot exista elemente care exista deja in Hashtable, caz in care se face update cheii existente cu noua valoare. Nu vor exista duplicate in acelasi batch.
- **get**: intoarce valorile corespunzatoare unui batch de chei.
- **reshape**: redimensioneaza Hashtable-ul, pastrand cheile deja existente, mapate la noile locatii, in functie de noua capacitate.

_Cerinta completa se poate gasi [aici](https://ocw.cs.pub.ro/courses/asc/teme/tema3)._

### Descrierea implementarii

O pereche <code>\<cheie, valoare></code> este abstractizata sub forma structurii:
```
struct entry {
	int key;
	int value;
}
```

Hashtable-ul este reprezentat sub forma unui vector alocat dinamic in VRAM de elemente de tip <code>entry</code>, avand o capacitate maxima si o dimensiune actuala (nr. de elemente inserate pana la un moment de timp):
```
class GpuHashTable {
	entry *hashMap;

	int capacity;
	int size;
}
```

Operatiile implementate folosesc tehnica de **linear probing**, care presupune o cautare liniara de la un anumit index (calculat ca hash), atunci cand exista coliziuni. Mai multe detalii [aici](https://en.wikipedia.org/wiki/Linear_probing).

Pentru o **dimensionare optima** a vectorului, am folosit un <code>load factor minim</code> si unul <code>maxim</code>. Daca intr-o inserare s-ar depasi <code>load factor-ul maxim</code>, atunci vectorul se redimensioneaza la o dimensiune care, dupa inserarea curenta, va avea <code>load factor-ul minim</code>. Load factor-ul maxim este 75%, asa cum este indicat [aici](https://docs.oracle.com/javase/6/docs/api/java/util/HashMap.html), iar cel minim este 55%, intrucat ofera indeajuns loc pentru multiple inserari, dar nu "risipeste" loc din vectorul alocat.

Functiile executate de GPU sunt <code>kernel_insert</code>, <code>kernel_get</code> si <code>kernel_reshape</code>. Indexul <code>idx</code> din fiecare thread se calculeaza dupa formula <code>blockIdx.x * blockDim.x + threadIdx.x</code>.

Toate alocarile si dezalocarile de memorie pe GPU sunt realizate prin clasa <code>glbGpuAllocator</code>.

In functia <code>getDeviceParams()</code>, se calculeaza numarul de block-uri si numarul maxim de thread-uri per block.

Vectorul de <code>entry</code> este initializat cu 0.

## Operatii

### insert

Insereaza un batch de elemente in Hashtable, indexul in vectorul de <code>entry-uri</code> fiind calculat in functie de cheie.

Apoi, se apeleaza functia pe GPU <code>kernel_insert</code> cu <code>\<\<\<numar_blockuri, numar_threaduri>>></code>, care calculeaza index-ul pentru fiecare thread si ia un singur element din vectorul de chei de inserat. Calculeaza hash-ul dupa cheie, acesta reprezentand locul din vectorul de <code>entry-uri</code> pe care se va incerca inserarea. Daca acel loc este liber, se adauga perechea <code>\<cheie, valoare></code> in acel slot. Daca cheia existenta in Hashtable este identica cu cea de inserat, se face update la noua valoare. Daca este diferita, se foloseste <code>linear probing</code> pentru a cauta urmatorul index liber din vector. Metoda de <code>linear probing</code> este implementata folosind <code>hash_value = (hash_value + 1) mod capacity</code>.

Se foloseste <code>atomicCas</code> pentru a inlocui cheia existenta, daca aceasta este 0 (neinitializata). Pentru a contoriza numarul de update-uri, se foloseste <code>atomicAdd</code> pe variabila <code>noUpdates</code>.

Noua dimensiune a Hashtable-ului este <code>current_size + dimensiune_insert - numar_update-uri</code>.

### get

Primeste un batch de chei si intoarce un batch de valori corespunzatoare cheilor pasate. Apeleaza <code>kernel_get</code> cu <code>\<\<\<numar_blockuri, numar_threaduri>>></code>. Fiecare thread calculeaza indexul unei chei din vectorul de chei care trebuie cautate in Hashtable, apoi face hash-ul acelei chei si incepe cautarea in vector, folosind <code>linear probing</code>. Cand gaseste valoarea corespunzatoare cheii, o plaseaza in vector-ul care trebuie intors la indicele <code>idx</code>.

### reshape

Redimensionarea Hashtable-ului este realizata ori prin apelul direct al functiei <code>reshape()</code>, ori atunci cand, la o inserare, s-ar depasi <code>load factor maxim</code>.

Se aloca memorie pentru noua dimensiune a vectorului, apoi se apeleaza <code>kernel_reshape</code>. Fiecare thread ia un element de la <code>idx</code> din actualul vector din Hashtable, ii calculeaza hash-ul si incearca sa il insereze, cu <code>linear probing</code>, in noul Hashtable.

In final, vectorul curent este eliberat si inlocuit de cel nou.

## Analiza

### Hashing

Am incercat mai multe functii diferite de hashing, dar, dintre toate, cea mai eficienta (ca numar de coliziuni redus, adica o viteza mare la operatiile pe kernel) este <code>Fowler-Noll-Vo</code>, varianta <code>1a</code>, al carei pseudocod este urmatorul:

```
algorithm fnv-1a is
    hash := FNV_offset_basis

    for each byte_of_data to be hashed do
        hash := hash XOR byte_of_data
        hash := hash × FNV_prime

    return hash
```

_Mai multe detalii desprea aceasta functie de hashing [aici](https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function)._

### Performanta

Output-ul rularii checker-ului <code>bench.py</code> pe coada <code>hp-sl.q</code> (avand GPU Tesla K40) este urmatorul:

```
------- Test T1 START   ----------

HASH_BATCH_INSERT   count: 1000000          speed: 113M/sec         loadfactor: 55%
HASH_BATCH_GET      count: 1000000          speed: 138M/sec         loadfactor: 55%
----------------------------------------------
AVG_INSERT: 113 M/sec,  AVG_GET: 138 M/sec,     MIN_SPEED_REQ: 10 M/sec


------- Test T1 END     ----------       [ OK RESULT: +20 pts ]



------- Test T2 START   ----------

HASH_BATCH_INSERT   count: 500000           speed: 91M/sec          loadfactor: 55%
HASH_BATCH_INSERT   count: 500000           speed: 84M/sec          loadfactor: 55%
HASH_BATCH_GET      count: 500000           speed: 110M/sec         loadfactor: 55%
HASH_BATCH_GET      count: 500000           speed: 109M/sec         loadfactor: 55%
----------------------------------------------
AVG_INSERT: 88 M/sec,   AVG_GET: 110 M/sec,     MIN_SPEED_REQ: 20 M/sec


------- Test T2 END     ----------       [ OK RESULT: +20 pts ]



------- Test T3 START   ----------

HASH_BATCH_INSERT   count: 125000           speed: 46M/sec          loadfactor: 55%
HASH_BATCH_INSERT   count: 125000           speed: 40M/sec          loadfactor: 55%
HASH_BATCH_INSERT   count: 125000           speed: 41M/sec          loadfactor: 55%
HASH_BATCH_INSERT   count: 125000           speed: 56M/sec          loadfactor: 73%
HASH_BATCH_INSERT   count: 125000           speed: 37M/sec          loadfactor: 55%
HASH_BATCH_INSERT   count: 125000           speed: 57M/sec          loadfactor: 66%
HASH_BATCH_INSERT   count: 125000           speed: 32M/sec          loadfactor: 55%
HASH_BATCH_INSERT   count: 125000           speed: 55M/sec          loadfactor: 62%
HASH_BATCH_GET      count: 125000           speed: 61M/sec          loadfactor: 62%
HASH_BATCH_GET      count: 125000           speed: 63M/sec          loadfactor: 62%
HASH_BATCH_GET      count: 125000           speed: 64M/sec          loadfactor: 62%
HASH_BATCH_GET      count: 125000           speed: 64M/sec          loadfactor: 62%
HASH_BATCH_GET      count: 125000           speed: 64M/sec          loadfactor: 62%
HASH_BATCH_GET      count: 125000           speed: 64M/sec          loadfactor: 62%
HASH_BATCH_GET      count: 125000           speed: 62M/sec          loadfactor: 62%
HASH_BATCH_GET      count: 125000           speed: 60M/sec          loadfactor: 62%
----------------------------------------------
AVG_INSERT: 46 M/sec,   AVG_GET: 63 M/sec,      MIN_SPEED_REQ: 40 M/sec


------- Test T3 END     ----------       [ OK RESULT: +15 pts ]



------- Test T4 START   ----------

HASH_BATCH_INSERT   count: 2500000          speed: 130M/sec         loadfactor: 55%
HASH_BATCH_INSERT   count: 2500000          speed: 114M/sec         loadfactor: 55%
HASH_BATCH_INSERT   count: 2500000          speed: 99M/sec          loadfactor: 55%
HASH_BATCH_INSERT   count: 2500000          speed: 102M/sec         loadfactor: 73%
HASH_BATCH_GET      count: 2500000          speed: 156M/sec         loadfactor: 73%
HASH_BATCH_GET      count: 2500000          speed: 156M/sec         loadfactor: 73%
HASH_BATCH_GET      count: 2500000          speed: 144M/sec         loadfactor: 73%
HASH_BATCH_GET      count: 2500000          speed: 139M/sec         loadfactor: 73%
----------------------------------------------
AVG_INSERT: 112 M/sec,  AVG_GET: 149 M/sec,     MIN_SPEED_REQ: 50 M/sec


------- Test T4 END     ----------       [ OK RESULT: +15 pts ]



------- Test T5 START   ----------

HASH_BATCH_INSERT   count: 20000000         speed: 132M/sec         loadfactor: 55%
HASH_BATCH_INSERT   count: 20000000         speed: 116M/sec         loadfactor: 55%
HASH_BATCH_GET      count: 20000000         speed: 142M/sec         loadfactor: 55%
HASH_BATCH_GET      count: 20000000         speed: 124M/sec         loadfactor: 55%
----------------------------------------------
AVG_INSERT: 124 M/sec,  AVG_GET: 133 M/sec,     MIN_SPEED_REQ: 50 M/sec


------- Test T5 END     ----------       [ OK RESULT: +15 pts ]

TOTAL gpu_hashtable  85/85
```

Se poate observa cum, in afara de testul 3, la toate celelalte teste, vitezele medii pentru operatiile de insert si get depasesc considerabil viteza minima necesara. In special la testul 4, unde deseori viteza la operatia get depasea 150 M/sec.

Viteza operatiei get nu variaza asa mult cu cea a operatiei insert deoarece nu necesita redimensionare si nici operatii atomice, ca in cazul celorlalte doua. De asemenea, variaza mult mai putin cand vine vorba de redimensionarea vectorului.

Se poate observa ca acolo unde la o operatie de insert nu este necesara o redimensionare, viteza creste semnificativ datorita eliminarii pasului de reshape.

### Profiling

La rularea testului 3 folosind <code>nvprof</code> (mai multe detalii despre ce este si ce face se pot gasi [aici](https://docs.nvidia.com/cuda/profiler-users-guide/index.html#nvprof-overview)), am obtinut urmatorul output:

```
==57351== Profiling result:
            Type  Time(%)      Time     Calls       Avg       Min       Max  Name
 GPU activities:   36.34%  3.3806ms         9  375.62us  10.144us  559.76us  kernel_insert(entry*, int*, int*, int, int, int*)
                   21.44%  1.9943ms        26  76.703us  1.0560us  83.425us  [CUDA memcpy HtoD]
                   19.88%  1.8498ms         6  308.29us  2.4000us  989.65us  kernel_reshape(entry*, int, entry*, int)
                   15.61%  1.4523ms         8  181.54us  162.50us  243.14us  kernel_get(entry*, int*, int, int, int*)
                    6.63%  616.59us         8  77.073us  76.833us  77.313us  [CUDA memcpy DtoH]
                    0.11%  9.8560us         7  1.4080us     896ns  3.2000us  [CUDA memset]
      API calls:   79.04%  236.58ms        33  7.1692ms  10.254us  231.20ms  cudaMalloc
                    8.41%  25.180ms        17  1.4812ms  210.38us  20.731ms  cudaMallocManaged
                    3.11%  9.3096ms        23  404.77us  385.22us  437.94us  cudaGetDeviceProperties
                    2.93%  8.7747ms        34  258.08us  12.369us  664.93us  cudaMemcpy
                    2.31%  6.9149ms        23  300.65us  9.2890us  998.32us  cudaDeviceSynchronize
                    1.93%  5.7650ms        49  117.65us  14.548us  189.40us  cudaFree
                    0.87%  2.6023ms         3  867.45us  865.00us  871.36us  cuDeviceTotalMem
                    0.68%  2.0274ms        23  88.146us  59.190us  173.77us  cudaLaunch
                    0.54%  1.6153ms       282  5.7270us     293ns  204.08us  cuDeviceGetAttribute
                    0.09%  261.18us         7  37.311us  29.211us  61.360us  cudaMemset
                    0.05%  136.40us         3  45.465us  43.569us  48.416us  cuDeviceGetName
                    0.03%  96.877us       186     520ns     204ns  4.2080us  cudaGetLastError
                    0.01%  33.422us       118     283ns     181ns  3.2390us  cudaSetupArgument
                    0.00%  11.268us        23     489ns     401ns  1.8960us  cudaConfigureCall
                    0.00%  7.3620us         6  1.2270us     383ns  4.3360us  cuDeviceGet
                    0.00%  3.5560us         3  1.1850us     310ns  2.2730us  cuDeviceGetCount
```

La rularea testului 5 am obtinut cu <code>nvprof</code> am obtinut:

```
 GPU activities:   34.00%  185.25ms         8  23.157ms  1.0560us  36.143ms  [CUDA memcpy HtoD]
                   26.00%  141.67ms         3  47.222ms  8.4170us  76.084ms  kernel_insert(entry*, int*, int*, int, int, int*)
                   22.36%  121.86ms         2  60.928ms  50.671ms  71.186ms  kernel_get(entry*, int*, int, int, int*)
                   15.28%  83.285ms         2  41.643ms  41.597ms  41.688ms  [CUDA memcpy DtoH]
                    2.35%  12.821ms         3  4.2736ms  2.6880us  11.681ms  kernel_reshape(entry*, int, entry*, int)
                    0.00%  7.0080us         4  1.7520us  1.1520us  3.4240us  [CUDA memset]
      API calls:   32.41%  279.47ms         8  34.934ms  9.8110us  76.099ms  cudaDeviceSynchronize
                   31.61%  272.54ms        10  27.254ms  11.813us  42.492ms  cudaMemcpy
                   24.04%  207.23ms        12  17.269ms  11.743us  201.84ms  cudaMalloc
                    6.18%  53.258ms        17  3.1328ms  16.170us  9.0313ms  cudaFree
                    4.60%  39.682ms         5  7.9364ms  266.36us  20.642ms  cudaMallocManaged
                    0.40%  3.4556ms         8  431.95us  382.77us  466.32us  cudaGetDeviceProperties
                    0.32%  2.7707ms         3  923.57us  920.76us  928.26us  cuDeviceTotalMem
                    0.20%  1.7248ms       282  6.1160us     300ns  211.27us  cuDeviceGetAttribute
                    0.18%  1.5238ms         8  190.47us  93.866us  474.17us  cudaLaunch
                    0.03%  270.54us         4  67.634us  40.705us  84.244us  cudaMemset
                    0.02%  148.79us         3  49.596us  46.240us  55.532us  cuDeviceGetName
                    0.01%  64.882us        63  1.0290us     238ns  16.133us  cudaGetLastError
                    0.00%  18.469us        40     461ns     178ns  3.3490us  cudaSetupArgument
                    0.00%  8.4970us         8  1.0620us     417ns  1.9360us  cudaConfigureCall
                    0.00%  8.0790us         6  1.3460us     394ns  4.7770us  cuDeviceGet
                    0.00%  3.8130us         3  1.2710us     382ns  2.3750us  cuDeviceGetCount
```

Putem observa cum la testul 3, unde au loc 8 operatii de insert, cel mai mult timp se petrece in functia <code>kernel_insert</code>, deci nu are loc un overhead exagerat.

Pe de alta parte, la testul 5, unde au loc inserturi cu foarte multe elemente, observam ca (s-a intamplat la o singura rulare acest lucru) copierea datelor din VRAM in memorie si invers dureaza foarte mult si inserarea in sine (adica functia <code>kernel_insert</code>) nu este cea mai solicitanta.

Din pacate, copierea aceasta este necesara intrucat kernelul trebuie sa lucreze cu date alocate in VRAM, iar Hashtable-ul primeste date alocate in RAM.

## Observatii

- In functie de cat de "ocupat" este GPU-ul de pe coada <code>hp-sl.q</code>, uneori la testul 3 la insert, viteza scade sub cea minima, dar nu cu mult (cea mai mica a fost 35-36 M/sec). Daca nu se mai ruleaza alte teme pe acelasi sistem in acelasi timp, nu apare aceasta problema.

### Bibliografie

https://stackoverflow.com/questions/10901752/what-is-the-significance-of-load-factor-in-hashmap

https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function

https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#atomiccas

https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#atomicadd

https://docs.nvidia.com/cuda/profiler-users-guide/index.html#nvprof-overview

https://ocw.cs.pub.ro/courses/asc/teme/tema3 

https://ocw.cs.pub.ro/courses/asc/laboratoare/07

https://ocw.cs.pub.ro/courses/asc/laboratoare/08

https://ocw.cs.pub.ro/courses/asc/laboratoare/09

### Link public repository
_(to be added)_