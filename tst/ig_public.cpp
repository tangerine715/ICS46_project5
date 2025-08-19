#include <CSVReader.hpp>
#include <IGWriter.hpp>
#include <InterferenceGraph.hpp>
#include <catch2/catch_amalgamated.hpp>

namespace {

namespace proj6 = shindler::ics46::project6;

const std::string &GRAPH_DIR = std::string("tst/graphs/");

TEST_CASE("SimpleAddEdgesAndVertices", "[Required][IG]") {
    const auto &GRAPH = GRAPH_DIR + "simple.csv";
    /// autograder/git-repo/student-execution-files/tests/
    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.numEdges() == 3);
    REQUIRE(igraph.numVertices() == 3);
}

TEST_CASE("Neighbors", "[Required][IG]") {
    const auto &GRAPH = GRAPH_DIR + "simple.csv";

    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);
    const std::unordered_set<proj6::Variable> &expected_neighbors = {"y", "z"};

    REQUIRE(igraph.neighbors("x") == expected_neighbors);
}

}  // namespace
