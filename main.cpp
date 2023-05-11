#include <iostream>
#include <fstream>
#include <iterator>
#include <bits/stdc++.h>

#include "variantSet.h"

int qsPartition(int* arr, VariantSet* vs[], int s, int e) {
  int p = arr[s];

  int n = 0;
  for (int i = s+1; i <= e; i++) if (arr[i] <= p) n++;
  int index = s + n;
  std::swap(arr[index], arr[s]);
  std::swap(vs[index], vs[s]);

  int i = s;
  int j = e;
  while (i < index && j > index) {
    while (arr[i] <= p) i++;
    while (arr[j] > p) j--;
    
    if (i < index && j > index) {
      std::swap(arr[i], arr[j]);
      std::swap(vs[i], vs[j]);
      i++;
      j--;
    }
  }

  return index;
}

void quickSort(int* arr, VariantSet* vs[], int s, int e) {
  if (s >= e) return;
  int p = qsPartition(arr, vs, s, e);
  quickSort(arr, vs, s, p-1);
  quickSort(arr, vs, p+1, e);
}

bool subset(int arr1[], int arr2[], int arr1Len, int arr2Len) {
  bool broken;
  for (int i = 0; i < arr2Len; i++) {
    broken = false;
    for (int j = 0; j < arr1Len; j++) {
      if (arr2[i] == arr1[j]) {
        broken = true;
        break;
      }
    }
    if (!broken) return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  /* LOAD DATA */
  std::ifstream inputFile(argv[1]);

  // Counts the number of lines in the file
  inputFile.unsetf(std::ios_base::skipws);
  unsigned numLines = std::count(std::istream_iterator<char>(inputFile), std::istream_iterator<char>(), '\n');
  inputFile.clear();
  inputFile.seekg(0);

  // Create the empty set of sets
  VariantSet* setOfSets[numLines];

  // Populate the set of sets by reading each line
  std::string line;
  int i = 0;
  while (getline(inputFile, line)) {
    // Count the number of variants in each line
    int numVariants = 1;
    size_t pos = 0;
    for (int c = 0; c < line.size(); c++) if (line[c] == ' ') numVariants++;

    // Split each line into its variants and load them into an array
    int variants[numVariants];
    int j = 0;
    pos = 0;
    std::string token;
    while ((pos = line.find(' ')) != std::string::npos) {
        token = line.substr(0, pos);
        variants[j] = std::stoi(token);
        line.erase(0, pos + 1);
        j++;
    }
    variants[j] = std::stoi(line);

    setOfSets[i] = new VariantSet;
    setOfSets[i]->addVariants(variants, numVariants);
    setOfSets[i]->numVariants = numVariants;

    i++;
  }
  inputFile.close();

  /* SORT DATA */
  int sizes[numLines];
  for (int i = 0; i < numLines; i++) {
    sizes[i] = setOfSets[i]->numVariants;
  }

  quickSort(sizes, setOfSets, 0, numLines-1);

  // for (int i = 0; i < numLines; i++) {
  //   VariantSet* vs = setOfSets[i];
  //   for (int j = 0; j < vs->numVariants; j++) {
  //     std::cout << vs->getVariant(j) << " ";
  //   }
  //   std::cout << std::endl;
  // }

  std::ofstream outputFile("output.txt");

  for (int i = 0; i < numLines-1; i++) {
    VariantSet* parentSet = setOfSets[i];
    int parentVariants[parentSet->numVariants];
    parentSet->variantArray(parentVariants);
        
    for (int j = i+1; j < numLines; j++) {
      VariantSet* childSet = setOfSets[j];
      int childVariants[childSet->numVariants];
      childSet->variantArray(childVariants);
      if (subset(childVariants, parentVariants, childSet->numVariants, parentSet->numVariants)) {
        parentSet->addEdge(childSet);
        for (int n = 0; n < parentSet->numVariants; n++) {
          if (n != 0) outputFile << ",";
          outputFile << parentVariants[n];
        }
        outputFile << "->";
        for (int n = 0; n < childSet->numVariants; n++) {
          if (n != 0) outputFile << ",";
          outputFile << childVariants[n];
        }
        outputFile << std::endl;
      }
    }
  }
  outputFile.close();
}