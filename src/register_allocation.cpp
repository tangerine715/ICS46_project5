#include "register_allocation.hpp"

#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <algorithm>


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
    // sortDescendingByDegree(descending_degrees);
    std::sort(descending_degrees.begin(), descending_degrees.end(), 
    [&](const Variable& a, const Variable& b){
        return igraph.degree(a) > igraph.degree(b);
    });

    
    RegisterAssignment mapping{};

    for (int num = 1; num <= numRegisters; ++num)
    {
        for (const Variable &vertex : descending_degrees)
        {
            //if it's already colored, go ahead
            if(mapping.find(vertex) != mapping.end())
            {
                break;
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

// void sortDescendingByDegree(std::vector<Variable>& vertices)
// {
//     //heapsort!
//     for (size_t i = vertices.size()/2; i < vertices.size(); --i)
//     {
//         heapify(vertices, i);
//     }

//     size_t end = vertices.size() - 1;
//     std::swap(vertices[0], vertices[end--]); //double check this does the thing

//     for (size_t i = 1; i < vertices.size(); ++i, --end)
//     {
//         std::swap(vertices[i], vertices[end]);
//         heapify(vertices, i);
//     }


//     // if (low >= high)
//     // {
//     //     return vertices;
//     // }
//     // unsigned int med = (low + high) / 2;
//     // mergeStep(mergeSortDescendingByDegree(vertices, low, med+1),
//     //         mergeSortDescendingByDegree(vertices, med+1, high));
// }

// void heapify(std::vector<Variable>& vertices, size_t index)
// {
//     size_t minIndex = 2*index + 1;
//     if(minIndex+1 != vertices.size())
//     if (vertices.at(minIndex) > vertices.at(minIndex+1)) { ++minIndex; }
//     if (vertices.at(index) > vertices.at(minIndex)) { std::swap(vertices[index], vertices[minIndex]); }
// }

// // void mergeStep(std::vector<Variable>& vertices, unsigned int low, unsigned int high)
// // {

// // }


}  // namespace shindler::ics46::project6
