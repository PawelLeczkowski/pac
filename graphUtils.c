//
// Created by pawel on 02.06.2026.
//

#include "graphUtils.h"

#include <math.h>
#include <stdlib.h>

struct Graph * CreateGraphFromFile(char *path) {
	//todo implement
}

struct Graph* CreateGraphFromMatrix(double **matrix, size_t size) {
	struct Graph* graph = malloc(sizeof(struct Graph));
	if (graph == NULL) {
		return NULL;
	}

	graph->vertices = malloc(sizeof(struct Vertex*) * size);
	if (graph->vertices == NULL) {
		free(graph);
		return NULL;
	}
	graph->vertexCount = size;

	// couting edges
	size_t edges = 0;
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			if (matrix[i][j] != NAN) {
				edges++;
			}
		}
	}

	graph->edges = malloc(sizeof(struct Edge*) * edges);
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
			if (matrix[i][j] != NAN) {
				graph->edges[edge].source = &graph->vertices[i];
				graph->edges[edge].destination = &graph->vertices[j];
				graph->edges[edge].weight = matrix[i][j];
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
		size_t index = 0;
		for (int j = 0; j < graph->edgeCount; j++) {
			if (vertex->id == graph->edges[j].source->id) {
				vertex->edges = &graph->edges[j];
				index++;
			}
		}
	}

	return graph;
}

char * CreateMatrixFromGraph(struct Graph *graph) {
	//todo implement
}
