#pragma once
#include "node.hpp"
#include "util/pretty_print.hpp"

template<class T>
inline T& node<T>::value() {
	return *m_value;
}

template<class T>
inline const T& node<T>::value() const {
	return *m_value;
}

template<class T>
inline void node<T>::fw_connect(const node& n) {
	m_edges.emplace(&n);
}

template<class T>
inline void node<T>::bi_connect(node& n) {
	fw_connect(n);
	n.fw_connect(*this);
}

template<class T>
inline void node<T>::fw_disconnect(const node& n) {
	m_edges.erase(&n);
}

template<class T>
inline void node<T>::bi_disconnect(node& n) {
	fw_disconnect(n);
	n.fw_disconnect(*this);
}

template<class T>
inline typename node<T>::id_type node<T>::id() const noexcept {
	return reinterpret_cast<id_type>(m_value.get());
}

template<class T>
inline node<T>::node(T* adopt_ptr, container edges) :
	m_value(adopt_ptr),
	m_edges(edges) {
}

template<class T>
template<class... Args>
inline node<T>::node(Args&&... args) :
	m_value(std::make_unique<T>(std::forward<Args>(args)...)) {
}

template<class T>
inline typename node<T>::nodes_view 
node<T>::adjacent_nodes() noexcept {
	return nodes_view(m_edges);
}

template<class T>
inline typename node<T>::const_nodes_view 
node<T>::adjacent_nodes() const noexcept {
	return const_nodes_view(m_edges);
}

template <class T>
std::ostream& operator<<(std::ostream& os, const node<T>& obj) {
	os << "{#" << pretty(obj.id()) << ": " << obj.value() << "}";
	return os;
}

namespace std {

template <class T>
struct hash<node<T>> {
	std::size_t operator()(const node<T>& nd) const noexcept {
		return std::hash<typename node<T>::id_type>()(nd.id());
	}
};

}