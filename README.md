# Genome Variant Ancestor Finder
This program will generate a graph that relates ancestor genomes to their decendants using variants (deviations relative to a baseline genome). It takes an input of genomes in the form of its variants, and outputs a file that shows all ancestor-descendant pairs.

### How it works:
The program first reads data from a file. This data is in the form of variants -- changes in a genome sequence. It then sorts this data by length in ascending order. This program makes the assumption that a genome with more variants cannot be the ancestor to a genome with fewer variants (this is always true unless a variant is flipped back to its earlier state, which is beyond the scope of this project). Using this assumption, we only have to compare shorter genomes to longer genomes. The program will not test to see if a longer genome is a subset of a shorter genome. After making all the valid comparisons, an output file stores the graph.

### Usage:
```sh
./GenomeTreeFinder [input filepath]
```
Example: `./GenomeTreeFinder input_files/26.txt`

The output is stored in the file `output.txt`.

### To compile:
```sh
g++ .\main.cpp .\variantSet.h -o GenomeTreeFinder
```