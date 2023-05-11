
#include <iostream>

struct Variant {
  int value = -1;
  Variant* nextVariant = nullptr;
};

#ifndef VariantSet_H
#define VariantSet_H

struct VariantSet {
  Variant* variant = new Variant;
  int numVariants;
  VariantSet* forwardEdges[100];

  // Converts an array of variants into a linked list datastructure
  void addVariants(int* variants, int numVariants) {
    variant->value = variants[0];
    for (int i = 1; i < numVariants; i++) { insertNode(variants[i]); }
  }

  void insertNode(int value) {
    Variant* newVariant = new Variant;
    newVariant->value = value;
    Variant* curr = variant;
    while (curr->nextVariant != nullptr) curr = curr->nextVariant;
    curr->nextVariant = newVariant;
  }

  // Gets the nth variant in the set
  int getVariant(int n) {
    Variant* curr = variant;
    for (int i = 0; i < n; i++) curr = curr->nextVariant;
    return curr->value;
  }

  void variantArray(int variants[]) {
    variants[0] = variant->value;
    Variant* curr = variant;
    int i = 1;
    while (curr->nextVariant != nullptr && i < numVariants) {
      curr = curr->nextVariant;
      variants[i] = curr->value;
      i++;
    }
  }

  void addEdge(VariantSet* child) {
    int i = 0;
    while (forwardEdges[i] != nullptr) i++;
    forwardEdges[i] = child;
  }
};

#endif