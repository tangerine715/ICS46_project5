#include "register_allocation.hpp"

#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <algorithm>
#include <iostream>


namespace shindler::ics46::project6 {

// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.
RegisterAssignment assignRegisters(const std::string &pathToGraph,
                                   int numRegisters) noexcept {
    InterferenceGraph<Variable> igraph = CSVReader::load(pathToGraph);
    std::vector<Variable> descending_degrees{};
    for (const auto& vertex : igraph.vertices())
    {
        descending_degrees.push_back(vertex);
    }


    // REPLACE LATER
    sortDescendingByDegree(descending_degrees, descending_degrees.size());
    // std::sort(descending_degrees.begin(), descending_degrees.end(), 
    // [&](const Variable& a, const Variable& b){
    //     return igraph.degree(a) > igraph.degree(b);
    // });

    RegisterAssignment mapping{};

    if (descending_degrees.empty() || igraph.degree(descending_degrees[0]) >= static_cast<unsigned int>(numRegisters))
    {
        return mapping;
    }

    for (int num = 1; num <= numRegisters; ++num)
    {
        for (const Variable &vertex : descending_degrees)
        {
            //if it's already colored, go ahead
            if(mapping.find(vertex) != mapping.end())
            {
                continue;
            }
            //if not, make sure none of the neighbors have the same color
            bool allNeighborsClear = true;
            for (const Variable &neighbor : igraph.neighbors(vertex))
            {
                if (mapping.find(neighbor) != mapping.end() && mapping.at(neighbor) == num)
                {
                    allNeighborsClear = false;
                    break;
                }
            }
            //if no neighbors had same color, go ahead and color it
            if (allNeighborsClear)
            {
                mapping[vertex] = num;
            }
        }
    }
    return mapping;
}

void sortDescendingByDegree(std::vector<Variable>& vertices, size_t size)
{
    //heapsort!
    for (int i = (size/2) - 1; i >= 0; --i)
    {
        heapify(vertices, size, i);
    }


    for (int i = size - 1; i >= 0; --i)
    {
        std::swap(vertices[0], vertices[i]);
        heapify(vertices, i, 0);
    }


    // if (low >= high)
    // {
    //     return vertices;
    // }
    // unsigned int med = (low + high) / 2;
    // mergeStep(mergeSortDescendingByDegree(vertices, low, med+1),
    //         mergeSortDescendingByDegree(vertices, med+1, high));
}

void heapify(std::vector<Variable>& vertices, size_t size, size_t root)
{
    //finding the minimum of the children
    size_t minIndex = 2*root + 1; //left child
    if (minIndex >= size)
    {
        return;
    }
    if (minIndex+1 < size && vertices.at(minIndex+1) < vertices.at(minIndex)) // right child
    { 
        ++minIndex; 
    }
    //swapping the root and smallest child if root is larger
    if (vertices.at(minIndex) < vertices.at(root)) 
    { 
        std::swap(vertices[root], vertices[minIndex]); 
        heapify(vertices, size, minIndex);
    }
}

// void mergeStep(std::vector<Variable>& vertices, unsigned int low, unsigned int high)
// {

// }


}  // namespace shindler::ics46::project6
