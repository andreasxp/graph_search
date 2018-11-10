#pragma once
#include <iterator>

#include "graph_random.hpp"
#include "util/generator.hpp"
#include "util/iterator.hpp"

template <class T>
void push_random_edge(graph<T>& g) {
	std::size_t max_edges = g.size() * (g.size() - 1) / 2;
	if (g.count_edges() == max_edges) throw std::invalid_argument("push_random_edge: graph is complete");

	// Select it1 that is not yet connected to all nodes
	auto it1 = zh::select(g);

	while (it1->edges().size() == g.size() - 1) {
		it1++;
		if (it1 == g.end()) it1 = g.begin();
	}

	// Select id2 that is not connected to id1
	auto it2 = zh::select(g);

	while (it2 == it1 || it2->edges().find(&*it1) != it2->edges().end()) {
		it2++;
		if (it2 == g.end()) it2 = g.begin();
	}

	g.connect(it1, it2);
}

template <class T>
void pop_random_edge(graph<T>& g) {
	if (g.count_edges() == 0) throw std::invalid_argument("pop_random_edge: graph is empty (no edges)");

	auto it1 = zh::select(g);

	// Select id1 that is connected to at least one node
	while (it1->edges().size() == 0) {
		it1++;
		if (it1 == g.end()) it1 = g.begin();
	}

	// Select a random connected node
	auto it2 = zh::select(it1->edges());

	g.disconnect(*it1, **it2);
}

template <class T>
void mutate_edges(graph<T>& g, double target_ratio) {
	if (target_ratio < 0 || target_ratio > 1) throw std::invalid_argument("mutate_edges: target_ratio must be a ratio in [0, 1]");

	std::size_t max_edges = g.size() * (g.size() - 1) / 2;
	std::size_t edges = g.count_edges();
	std::size_t taredges = static_cast<std::size_t>(round(target_ratio * max_edges));

	if (edges < taredges) {
		while (edges < taredges) {
			push_random_edge(g);
			edges++;
		}
	}
	else {
		while (edges > taredges) {
			pop_random_edge(g);
			edges--;
		}
	}
}

template <class T, class Gen>
void push_random_node(graph<T>& g, Gen&& value_gen) {
	g.emplace(value_gen());
}

template <class T>
void push_random_node(graph<T>& g) {
	push_random_node(g, generator<T>());
}

template <class T>
void pop_random_node(graph<T>& g) {
	if (g.empty()) throw std::invalid_argument("pop_random_node: graph has no nodes");

	auto it = zh::select(g);
	g.erase(it);
}

template <class T, class Gen>
void mutate_nodes(graph<T>& g, std::size_t target_size, Gen&& value_gen) {
	if (target_size > g.size()) {
		for (std::size_t i = g.size(); i < target_size; i++) {
			push_random_node<T>(g, value_gen);
		}
	}
	else {
		for (std::size_t i = g.size(); i > target_size; i--) {
			pop_random_node<T>(g);
		}
	}
}

template <class T>
void mutate_nodes(graph<T>& g, std::size_t target_size) {
	mutate_nodes(g, target_size, generator<T>());
}

template <class T, class Gen>
void mutate(graph<T>& g, std::size_t target_size, double target_ratio, Gen&& value_gen) {
	if (target_ratio < 0 || target_ratio > 1) throw std::invalid_argument("mutate: edges_ratio must be a ratio in [0, 1]");

	mutate_nodes(g, target_size, value_gen);
	mutate_edges(g, target_ratio);
}

template <class T>
void mutate(graph<T>& g, std::size_t target_size, double target_ratio) {
	mutate(g, target_size, target_ratio, generator<T>());
}