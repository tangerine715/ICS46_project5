#include "register_allocation.hpp"

#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"

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

    // TODO: You implement this!

    return {};
}

}  // namespace shindler::ics46::project6
