<mark>Template for your README. Remove all unused parts and instructions</mark>

# Lab work 3: Parallel File Indexing
Authors (team):
- [Mykhailo Bondarenko](https://github.com/michael-2956)
- [Bohdan Ruban](https://github.com/iamthewalrus67)
- [Ostap Trush](https://github.com/Adeon18)

Variant: _No Variant for this lab_
## Prerequisites

- gcc
- CMake
- boost
- Preferably a PC with multiple logical cores :D

### Compilation

_Run `./compile.sh` with the needed flags to compile the project(the binary will be in ./bin/)_

### Installation

1. Install all Prerequisites
2. Libs for python script:
```bash
pip install -r requirements.txt
```

### Usage

_The binary takes the config path as its argument._
```bash
./word_indexer <path_to_config_file>
```

_The config file has path to the directory to be indexed, thread count and output paths._
```
indir="data/to_index"     # Директорія для індексації
out_by_a="data/res_a.txt"  # Результати, посортовані за алфавітом
out_by_n="data/res_n.txt"  # Результати, посортовані за кількістю
indexing_threads=3
```

### Important!

_None for now..._

### Results

_We have a word indexer program that can index words in parallel._

_The graphs should go here..._


# Additional tasks
```
Додаткове завдання - 1 (2 бали): дослідити залежність часу виконання від кількості потоків на різних комп’ютерах і з різними наборами параметрів.
```

