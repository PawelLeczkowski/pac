//
// Created by pawel on 02.06.2026.
//

#include "graphUtils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph * CreateGraphFromFile(char *path) {
	if (path == NULL) {
		return NULL;
	}

	FILE * file = fopen(path, "r");
	if (file == NULL) {
		return NULL;
	}

	size_t size = 0;
	fscanf(file, "%llu", &size);

	double* matrix = calloc(size * size, sizeof(double*));

	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			int c = getc(file);
			ungetc(c, file);
			if (c == 'N') {
				getc(file);
				getc(file);
				matrix[i * size + j] = NAN;
			}
			else {
				fscanf(file, "%lf", &matrix[i * size + j]);
			}
		}
	}

	struct Graph* graph = CreateGraphFromMatrix(size, matrix);

	free(matrix);
	fclose(file);

	return graph;
}

struct Graph* CreateGraphFromMatrix(size_t size, double* matrix) {
	struct Graph* graph = malloc(sizeof(struct Graph));
	if (graph == NULL) {
		return NULL;
	}

	graph->vertices = calloc(size, sizeof(struct Vertex));
	if (graph->vertices == NULL) {
		free(graph);
		return NULL;
	}
	graph->vertexCount = size;

	// couting edges
	size_t edges = 0;
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			if (!isnan(matrix[i * size + j])) {
				edges++;
			}
		}
	}

	graph->edges = malloc(sizeof(struct Edge) * edges);
	if (graph->edges == NULL) {
		free(graph->vertices);
		free(graph);
		return NULL;
	}
	graph->edgeCount = edges;

	// creating edgess and assiging ids to verticies
	int edge = 0;
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			if (!isnan(matrix[i * size + j])) {
				graph->edges[edge].source = &graph->vertices[i];
				graph->edges[edge].destination = &graph->vertices[j];
				graph->edges[edge].weight = matrix[i * size + j];
				edge++;

				graph->vertices[i].degree++;
			}
		}
		graph->vertices[i].id = i;
	}

	// assiging edges to verticies
	for (int i = 0; i < graph->vertexCount; ++i) {
		struct Vertex *vertex = &graph->vertices[i];
		vertex->edges = malloc(sizeof(struct Edge*) * graph->vertices[i].degree);

		if (vertex->edges == NULL) {
			for (int j = 0; j < i; ++j) {
				free(graph->vertices[j].edges);
			}
			free(graph->edges);
			free(graph->vertices);
			free(graph);
			return NULL;
		}

		// searching for all edges whose source is ith vertex
		int index = 0;
		for (int j = 0; j < graph->edgeCount; j++) {
			if (vertex == graph->edges[j].source) {
				vertex->edges[index] = &graph->edges[j];
				index++;
			}
		}
	}

	return graph;
}

int SaveGraphToFile(struct Graph *graph, char* path) {
	if (graph == NULL) {
		return -1;
	}

	FILE * file = fopen(path, "w");
	if (file == NULL) {
		return -2;
	}

	fprintf(file, "%llu\n", graph->vertexCount);

	for (int i = 0; i < graph->vertexCount; ++i) {
		struct Vertex *vertex = &graph->vertices[i];

		int index = 0;
		for (int j = 0; j < graph->vertexCount; ++j) {
			if (index <= vertex->degree && vertex->edges[index]->destination->id == j) {
				fprintf(file,"%.10g ", vertex->edges[index]->weight);
				index++;
			}
			else {
				fprintf(file,"NaN ");
			}
		}
		fprintf(file, "\n");
	}

	fclose(file);

	return 0;
}
