//
// Created by pawel on 02.06.2026.
//

#ifndef PPC_GRAPHUTILS_H
#define PPC_GRAPHUTILS_H


#include <stddef.h>

#include "pacdef.h"

struct Graph* CreateGraphFromFile(char* path);

struct Graph* CreateGraphFromMatrix(size_t size, double* matrix);

int SaveGraphToFile(struct Graph* graph, char* path);

#endif //PPC_GRAPHUTILS_H