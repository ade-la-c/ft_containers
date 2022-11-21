#pragma once

#include "reverse_iterator.hpp"
#include "utils.hpp"
#include "pair.hpp"

namespace ft {


	template< class T >
	struct	Node {
		typedef	T	value_type;

		value_type		data;		/* Holds the key */
		Node*			parent;		/* Pointer to the parent */
		Node*			left;		/* Pointer to the left child */
		Node*			right;		/* Pointer to the right child */
		bool			color;		/* 1 = Red, 0 = Black */

		/* ************************** Constructors ************************** */
		/*	Default */
		Node() : data(value_type()) {}
		Node(const value_type & val) : data(val) {}
		/*	Copy */
		Node(const Node & x)
		: data(x.data), parent(x.parent), left(x.left), right(x.right), color(x.color) {}
		/*	Destructor */
		~Node() {}
		/*	Operator= */
		Node &	operator=(const Node & x) {
			if (this != &x) {
				this->data = x.data;
				this->color = x.color;
				this->parent = x.parent;
				this->left = x.left;
				this->right = x.right;
			}
			return *this;
		}
	};

	template< class Key, class T >
	class RBTree {

		public:

			typedef				Key																key_type;
			typedef				T																mapped_type;
			typedef	typename	ft::pair<const key_type, mapped_type>							value_type;
			typedef	typename	std::allocator< RBTree<Key, T> >								allocator_type;
			typedef typename	std::size_t														size_type;
			typedef typename	allocator_type::template rebind< Node<value_type> >::other		node_allocator;
			typedef				ft::Node<value_type>*											node_pointer;
			typedef				ft::Node<value_type>											node_type;

			/* ************************ Constructors ************************ */
			/*	Default */
			RBTree() {
				end = node_allocator().allocate(1);
				node_allocator().construct(end, node_type());
				end->parent = NULL;
				end->left = NULL;
				end->right = NULL;
				end->color = false;
				root = end;
				size = 0;
			}
			/*	Copy */
			RBTree(const RBTree & x) : root(x.root), end(x.end), size(x.size) {
				this->clear(this->root);
				this->insertAll(x.root);
			}
			/*	Operator= */
			RBTree &	operator=(const RBTree & x) {
				if (this != &x) {
					this->clear(this->root);
					this->insertAll(x.root);
					this->root = x.root;
					this->end = x.end;
					this->size = x.size;
				}
				return *this;
			}
			/*	Destructor */
			~RBTree() {
				node_allocator().destroy(end);
				node_allocator().deallocate(end, 1);
				end = NULL;
			}

			/* ************************************************************** */
			/* ********************** Member Functions ********************** */
			/* ************************************************************** */

			/* ************************************************************** */
			/* ************************** Accessors ************************* */
			/* ************************************************************** */
			node_pointer	getEnd() const { return this->end; }
			node_pointer	getRoot() const { return this->root; }
			size_type		getSize() const { return this->size; }

			// search returns the node corresponding to the key_type entered as parameter
			node_pointer	search(const key_type & key) const {
				node_pointer	tmp = this->root;

				while (tmp != end) {

					if (tmp->data.first == key) {
						return tmp;
					} else if (key < tmp->data.first) {
						tmp = tmp->left;
					} else {
						tmp = tmp->right;
					}
				}
				return NULL;
			}

			node_pointer	firstNode() const {
				node_pointer	tmp = root;

				if (tmp == end) {
					return end;
				}
				while (tmp->left != end) {
					tmp = tmp->left;
				}
				return tmp;
			}

			node_pointer	lastNode() const {
				node_pointer	tmp = root;

				if (tmp == end) {	
					return end;
				}
				while (tmp->right != end) {
					tmp = tmp->right;
				}
				return tmp;
			}

			/* ************************************************************** */
			/* ************************** Modifiers ************************* */
			/* ************************************************************** */

			/*	Insert the key to the tree in its appropriate position and fix
				the tree. */
			node_pointer	insertNode(const value_type& val) {
				node_pointer	find;

				if ((find = search(val.first)) != NULL)
					return find;
				node_pointer	node = node_allocator().allocate(1);
				node_allocator().construct(node, node_type(ft::make_pair<key_type, mapped_type>(val.first, val.second)));
				node->parent = NULL;
				node->left = end;
				node->right = end;
				node->color = true; /* new node is red */
				size++;
				node_pointer y = NULL;
				node_pointer x = this->root;

				while (x != end) {
					y = x;
					if (node->data < x->data)
						x = x->left;
					else
						x = x->right;
				}
				node->parent = y; /* y is parent of x */
				if (y == NULL)
					root = node;
				else if (node->data < y->data)
					y->left = node;
				else
					y->right = node;
				
				// /*	If new node is a root node, simply return/
				if (node->parent == NULL) {
					node->color = false;
					indexEnd();
					return node;
				}
				if (node->parent->parent == NULL) {
					indexEnd();
					return node;
				}
				// */
				//	Fix the tree
				fixInsert(node); // fixInsert(node)
				indexEnd();
				return node;
			}

			void			insertAll(node_pointer node) {

				if (node == NULL)
					return ;
				insertAll(node->left);
				insertAll(node->right);
				insertNode(node->data);
			}

			size_type		deleteNode(node_pointer node, const key_type & key) {
				node_pointer	x, y, z = end;

				/*	Find the node containing the key */
				while (node != end) { 
					if (node->data.first == key) {
						z = node;
					}
					if (node->data.first <= key)
						node = node->right;
					else
						node = node->left;
				}
				if (z == end)
					return 0;
				y = z;
				int	y_original_color = y->color;
				if (z->left == end) {
					x = z->right;
					rbTransplant(z, z->right);
				} else if (z->right == end) {
					x = z->left;
					rbTransplant(z, z->left);
				} else {
					y = minimum(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else {
						rbTransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					rbTransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				node_allocator().destroy(z);
				node_allocator().deallocate(z, 1);
				size--;
				if (y_original_color == 0)
					fixDelete(x); /* fixDelete(x) */
				indexEnd();
				return 1;
			}

			void			clear(node_pointer node) {
				if (node == end)
					return;
				clear(node->left);
				clear(node->right);
				node_allocator().destroy(node);
				node_allocator().deallocate(node, 1);
				node = NULL;
			}

			void			swap(RBTree & x) {
				size_type		s_size;
				node_pointer	s_root;
				node_pointer	s_end;

				s_size = x.size;
				s_root = x.root;
				s_end = x.end;
				x.size = this->size;
				x.root = this->root;
				x.end = this->end;
				this->size = s_size;
				this->root = s_root;
				this->end = s_end;
			}

		private:

			node_pointer	root;
			node_pointer	end;
			size_type		size;

			void	indexEnd() {
				end->left = firstNode();
				end->right = lastNode();
			}

			node_pointer	minimum(node_pointer node) {
				while (node->left != end)
					node = node->left;
				return node;
			}

			void	rbTransplant(node_pointer u, node_pointer v) {
				if (u->parent == NULL)
					root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void	leftRotate(node_pointer x) {
				node_pointer	y = x->right;
				x->right = y->left;
				if (y->left != end)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					this->root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void	rightRotate(node_pointer x) {
				node_pointer	y = x->left;
				x->left = y->right;
				if (y->right != end)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					this->root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			/* Fix the RBTree after inserting an element */
			void	fixInsert(node_pointer k) {
				node_pointer	u;

				while (k->parent->color == 1) {
					if (k->parent == k->parent->parent->right) {
						u = k->parent->parent->left; /* Uncle */
						if (u->color == 1) {
							/* case 3.1 */
							u->color = false;
							k->parent->color = false;
							k->parent->parent->color = true;
							k = k->parent->parent;
						} else {
							if (k == k->parent->left) {
								/* case 3.2.2 */
								k = k->parent;
								rightRotate(k);
							}
							/* case 3.2.1 */
							k->parent->color = false;
							k->parent->parent->color = true;
							leftRotate(k->parent->parent);
						}
					} else {
						u = k->parent->parent->right; /* Uncle */
						if (u->color == 1) {
							/* mirror case 3.1 */
							u->color = false;
							k->parent->color = false;
							k->parent->parent->color = true;
							k = k->parent->parent;
						} else {
							if (k == k->parent->right) {
								/* mirror case 3.2.2 */
								k = k->parent;
								leftRotate(k);
							}
							/* mirror case 3.2.1 */
							k->parent->color = false;
							k->parent->parent->color = true;
							rightRotate(k->parent->parent);
						}
					}
					if (k == root)
						break ;
				}
				root->color = false;
			}

			/* Fix the RBTree after deleting a element */
			void	fixDelete(node_pointer x) {
				node_pointer	s;
				while (x != root && x->color == 0) {
					if (x == x->parent->left) {
						s = x->parent->right;
						if (s->color == 1) {
							/* case 3.1 */
							s->color = false;
							x->parent->color = true;
							leftRotate(x->parent);
							s = x->parent->right;
						}
						if (s->left->color == 0 && s->right->color == 0) {
							/* case 3.2 */
							s->color = true;
							x = x->parent;
						} else {
							if (s->right->color == 0) {
								/* case 3.3 */
								s->left->color = false;
								s->color = true;
								rightRotate(s);
								s = x->parent->right;
							}
							/* case 3.4 */
							s->color = x->parent->color;
							x->parent->color = false;
							s->right->color = false;
							leftRotate(x->parent);
							x = root;
						}
					} else {
						s = x->parent->left;
						if (s->color == 1) {
							/* case 3.1 */
							s->color = false;
							x->parent->color = true;
							rightRotate(x->parent);
							s = x->parent->left;
						}
						if (s->left->color == 0 && s->right->color == 0) {
							/* case 3.2 */
							s->color = true;
							x = x->parent;
						} else {
							if (s->left->color == 0) {
								/* case 3.3 */
								s->right->color = false;
								s->color = true;
								leftRotate(s);
								s = x->parent->left;
							}
							/* case 3.4 */
							s->color = x->parent->color;
							x->parent->color = false;
							s->left->color = false;
							rightRotate(x->parent);
							x = root;
						}
					}
				}
				x->color = false;
			}

	};

}
