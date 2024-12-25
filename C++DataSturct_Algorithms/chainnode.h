#ifndef CHAINNODE_H_
#define CHAINNODE_H
template<class T>
struct chainNode
{
	T data_m;
	struct chainNode<T>* next_m;
	chainNode(T& data, chainNode<T>* next) {
		this->data_m = data_m;
		this->next_m = next;
	}
	chainNode(T data, chainNode<T>* next) {
		this->data_m = data;
		this->next_m = next;
	}
	chainNode(chainNode<T>& node) {
		this->data_m = node.data_m;
		this->next_m = node.next_m;
	}
	chainNode(chainNode<T>* node) {
		this->data_m = node->data_m;
		this->next_m = node->next_m;
	}
	chainNode(T& data) { this->data_m = data; this->next_m = nullptr; }
};
#endif
