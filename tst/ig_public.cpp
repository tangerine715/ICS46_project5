#include <CSVReader.hpp>
#include <IGWriter.hpp>
#include <InterferenceGraph.hpp>
#include <catch2/catch_amalgamated.hpp>

#include <iostream>
#include <fstream>
#include <string>

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

TEST_CASE("CompleteSixAddEdgesAndVertices", "[Required][IG]") {
    const auto &GRAPH = GRAPH_DIR + "complete_6.csv";
    /// autograder/git-repo/student-execution-files/tests/
    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.numEdges() == 15);
    REQUIRE(igraph.numVertices() == 6);
}

TEST_CASE("CompleteSixNeighbors", "[Required][IG]") {
    const auto &GRAPH = GRAPH_DIR + "complete_6.csv";

    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);
    const std::unordered_set<proj6::Variable> &expected_neighbors = {"1", "2", "3", "4", "5"};

    REQUIRE(igraph.neighbors("6") == expected_neighbors);
    REQUIRE(igraph.numVertices() == 6);
    REQUIRE(igraph.numEdges() == 15);
}

TEST_CASE("BigBipartiteAddEdgesAndVertices", "[Required][IG]") {
    const auto &GRAPH = GRAPH_DIR + "big_bipartite.csv";
    /// autograder/git-repo/student-execution-files/tests/
    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.numEdges() == 8);
    REQUIRE(igraph.numVertices() == 6);
}

TEST_CASE("BigBipartiteNeighbors", "[Required][IG]") {
    const auto &GRAPH = GRAPH_DIR + "big_bipartite.csv";

    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);
    const std::unordered_set<proj6::Variable> &expected_neighbors = {"x", "y"};

    REQUIRE(igraph.neighbors("a") == expected_neighbors);
}

TEST_CASE("CheckEdgeExists", "[IG]") {
    proj6::InterferenceGraph<std::string> graph;
    graph.addVertex("x");
    graph.addVertex("y");
    graph.addVertex("z");
    graph.addEdge("x", "y");

    REQUIRE(graph.interferes("x", "y"));
    REQUIRE_FALSE(graph.interferes("x", "z"));
}

TEST_CASE("RemoveEdgesAndVertices", "[IG]") {
    proj6::InterferenceGraph<std::string> graph;
    graph.addVertex("x");
    graph.addVertex("y");
    graph.addEdge("x", "y");
    graph.removeEdge("x", "y");
    graph.removeVertex("x");

    REQUIRE(graph.numEdges() == 0);
    REQUIRE(graph.numVertices() == 1);
}


TEST_CASE("Complete1000", "[IG]") {
    const auto &GRAPH = GRAPH_DIR + "complete_1000.csv";
    const int n = 1000;  // Number of vertices
    // std::ofstream outfile(GRAPH);

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = i + 1; j <= n; ++j) {
    //         if(i!=(n-1) || j!=(n))
    //         { 
    //             outfile << i << "," << j << '\n'; 
    //         }
    //         else 
    //         {
    //             outfile << i << "," << j; 
    //         }
    //     }
    // }

    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.numVertices() == n);
    REQUIRE(igraph.numEdges() == (n-1)*n/2);

    
}


}  // namespace
