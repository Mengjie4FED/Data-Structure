/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    // ini. all vertices and edges to UNEXPLORED
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    for (size_t i = 0; i < vertices.size(); i++) {
      graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }
    for (size_t i = 0; i < edges.size(); i++) {
      graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }

    Vertex start = graph.getStartingVertex();
    queue<Vertex> q;
    q.push(start);
    graph.setVertexLabel(start, "VISITED");
    int min = INT_MAX;
    Vertex minS;
    Vertex minD;

    while (!q.empty()) {
      Vertex a = q.front();
      vector<Vertex> adjacents = graph.getAdjacent(a);
      q.pop();

      for (size_t i = 0; i < adjacents.size(); i++) {
        if (graph.getVertexLabel(adjacents[i]) == "UNEXPLORED") {
          q.push(adjacents[i]);
          graph.setVertexLabel(adjacents[i], "VISITED");
          graph.setEdgeLabel(a, adjacents[i], "DISCOVERY");
          if (graph.getEdgeWeight(a, adjacents[i]) < min) {
            min = graph.getEdgeWeight(a, adjacents[i]);
            minS = a;
            minD = adjacents[i];
          }
        }
        else if (graph.getEdgeLabel(a, adjacents[i]) == "UNEXPLORED") {
          graph.setEdgeLabel(a, adjacents[i], "CROSS");
          if (graph.getEdgeWeight(a, adjacents[i]) < min) {
            min = graph.getEdgeWeight(a, adjacents[i]);
            minS = a;
            minD = adjacents[i];
          }
        }
      }
    }
    graph.setEdgeLabel(minS, minD, "MIN");
    return min;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    vector<Vertex> vertices = graph.getVertices();
    vector<Edge> edges = graph.getEdges();
    for (size_t i = 0; i < vertices.size(); i++) {
      graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }
    for (size_t i = 0; i < edges.size(); i++) {
      graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }

    queue<Vertex> q;
    q.push(start);
    graph.setVertexLabel(start, "VISITED");
    unordered_map<Vertex, Vertex> parent;

    while (!q.empty()) {
      Vertex a = q.front();
      vector<Vertex> adjacents = graph.getAdjacent(a);
      q.pop();
      Vertex b;

      for (size_t i = 0; i < adjacents.size(); i++) {
        b = adjacents[i];
        if (graph.getVertexLabel(adjacents[i]) == "UNEXPLORED") {
          q.push(adjacents[i]);
          graph.setVertexLabel(adjacents[i], "VISITED");
          graph.setEdgeLabel(a, adjacents[i], "DISCOVERY");
          parent[adjacents[i]] = a;
          if (adjacents[i] == end) {
            break;
          }
        }
        else if (graph.getEdgeLabel(a, adjacents[i]) == "UNEXPLORED") {
          graph.setEdgeLabel(a, adjacents[i], "CROSS");
        }
      }

      if (b == end) {
        break;
      }
    }
    int count = 0;
    while (end != start) {
      graph.setEdgeLabel(end, parent[end], "MINPATH");
      end = parent[end];
      count++;
    }
    return count;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    DisjointSets forest;
    vector<Vertex> vertices = graph.getVertices();
    size_t verNum = vertices.size();
    forest.addelements(verNum);

    vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end());

    size_t count = 0;
    while (count < verNum - 1) {
      Edge eMin = edges.front();
      edges.erase(edges.begin());
      Vertex eS = eMin.source;
      Vertex eD = eMin.dest;
      if (forest.find(eS) != forest.find(eD)) {
        graph.setEdgeLabel(eS, eD, "MST");
        forest.setunion(forest.find(eS), forest.find(eD));
        count++;
      }
    }
}
