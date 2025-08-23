#ifndef __PROJ6_INTERFERENCE_GRAPH__HPP
#define __PROJ6_INTERFERENCE_GRAPH__HPP

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <ranges>

namespace shindler::ics46::project6 {

class UnknownVertexException : public std::runtime_error {
   public:
    explicit UnknownVertexException(const std::string &vertex)
        : std::runtime_error("Unkown vertex " + vertex) {}
};

class UnknownEdgeException : public std::runtime_error {
   public:
    UnknownEdgeException(const std::string &source,
                         const std::string &destination)
        : std::runtime_error("Unknown edge " + source + " - " + destination) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file. Though this class is templated, because of the usage of exceptions
// UnknownVertexException and UnknownEdgeException it will
// ONLY be tested with strings.
template <typename T>
class InterferenceGraph {
   public:
    // Custom type used to represent edges. This is mainly
    // used in the utility function for reading and writing
    // the graph structure to/from files. You don't need to use it.
    using EdgeTy = std::pair<T, T>;

    // priorities: 
    // speed of adding edges (to hit 1000 vertices)
    // speed of adding vertices 
    // speed of sorting (so ease in computing degree, or pre-sorted by degree)

    // Idea 1: adjacency matrix
    // std::vector<std::vector<T>> adj;
    // std::vector<T> vertices; 

    // speed of adding edges - this is O(n), i would need to find indexes of vertices first
    // speed of adding vertices - O(1) or O(n) - depends on time complexity of adding a vector with all 0's of given size
    // speed of sorting (so ease in computing degree, or pre-sorted by degree) - O(1) - just size

    // Idea 2: adjacency list with a vector
    // std::unordered_map<T, std::vector<T>> adj;

    // speed of adding edges - this is O(1), i just push back on vector at given key
    // speed of adding vertices - O(1) - i just have an empty vertex added
    // speed of sorting (so ease in computing degree, or pre-sorted by degree) - O(1) - just size of the vector
    // do note speed of SEARCHING (check if this edge exists) is O(degree)

    // Idea 3: adjacency list with a unordered set
    std::unordered_map<T, std::unordered_set<T>> adj;

    // speed of adding edges - this is O(1)
    // speed of adding vertices - O(1)
    // speed of sorting (so ease in computing degree, or pre-sorted by degree) - O(n) - just size
    // do note speed of SEARCHING (check if this edge exists) is O(1)


    unsigned int numberOfEdges;
    unsigned int numberOfVertices;
    //this matrix assigns every edge, and every vector row ends in the sum of all the edges
    //(ease of degree computation?)
    



    InterferenceGraph();

    // You DO NOT need to implement these
    InterferenceGraph(const InterferenceGraph &) = delete;
    InterferenceGraph(InterferenceGraph &&) = default;
    InterferenceGraph &operator=(const InterferenceGraph &) = delete;
    InterferenceGraph &operator=(InterferenceGraph &&) = default;

    ~InterferenceGraph();

    void addEdge(const T &source, const T &destination);

    void addVertex(const T &vertex);

    void removeEdge(const T &source, const T &destination);

    void removeVertex(const T &vertex);

    [[nodiscard]] std::unordered_set<T> vertices() const noexcept;

    [[nodiscard]] std::unordered_set<T> neighbors(const T &vertex) const;

    [[nodiscard]] unsigned numVertices() const noexcept;

    [[nodiscard]] unsigned numEdges() const noexcept;

    [[nodiscard]] bool interferes(const T &source, const T &destination) const;

    [[nodiscard]] unsigned degree(const T &vertex) const;

   private:
    // Private member variables here.
};

template <typename T>
InterferenceGraph<T>::InterferenceGraph() {
   
}

template <typename T>
InterferenceGraph<T>::~InterferenceGraph() {
    
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const {
    return adj.at(vertex);
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept {
    std::unordered_set<T> vertex;
    vertex.reserve(adj.size());
    for (auto& [vert, edges] : adj) 
    { 
        vertex.insert(vert); 
    }
    return vertex;
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept {
    return numberOfVertices;
}

template <typename T>
unsigned InterferenceGraph<T>::numEdges() const noexcept {
    return numberOfEdges;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &source, const T &destination) {
    if(adj.find(source) == adj.end() || adj.find(destination) == adj.end())
    {
        throw shindler::ics46::project6::UnknownVertexException("couldn't find it rip");
    }
    adj.at(source).insert(destination);
    adj.at(destination).insert(source);
    ++numberOfEdges;
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &source, const T &destination) {
    if(adj.find(source) == adj.end() || adj.find(destination) == adj.end())
    {
        throw shindler::ics46::project6::UnknownVertexException("couldn't find it rip");
    }
    adj.at(source).erase(adj.at(source).find(destination));
    adj.at(destination).erase(adj.at(destination).find(source));
    --numberOfEdges;
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) {
//     (void) adj[vertex]; //hopefully allowed 
    if(adj.find(vertex) != adj.end())
    {
        return;
    }
    (void) adj[vertex];
    ++numberOfVertices;
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) {
    if(adj.find(vertex) == adj.end())
    {
        return;
    }
    adj.erase(vertex);
    --numberOfVertices;
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &source,
                                      const T &destination) const {
    if(adj.find(source) == adj.end() || adj.find(destination) == adj.end())
    {
        throw shindler::ics46::project6::UnknownVertexException("couldn't find it rip");
    }
    return adj.at(source).find(destination) != adj.at(source).end();
}

template <typename T>
unsigned InterferenceGraph<T>::degree(const T &vertex) const {
    if(adj.find(vertex) == adj.end())
    {
        throw shindler::ics46::project6::UnknownVertexException("couldn't find it rip");
    }
    return adj.at(vertex).size();
}

}  // namespace shindler::ics46::project6

#endif
