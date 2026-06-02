//
// Created by pawel on 02.06.2026.
//

#ifndef PPC_PACDEF_H
#define PPC_PACDEF_H

struct Edge {
	double weight;
	struct Vertex* source;
	struct Vertex* destination;
};

struct Vertex {
	int id;
	void* value;
	struct Edge* edges;
	size_t degree;
};

struct Graph {
	struct Vertex* vertices;
	size_t vertexCount;
	struct Edge* edges;
	size_t edgeCount;
};

#endif //PPC_PACDEF_H