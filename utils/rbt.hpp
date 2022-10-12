#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>
// #include "iterator.hpp"
#define REDSTR "\033[31m"
#define RESET "\033[0m"

namespace ft {

template <

	typename T,
	typename Compare = std::less<T>,
	typename Allocator = std::allocator<T>

> class RBtree {
	private:

		class RBnode;
		template <typename U> class iterator_t;
		typedef typename Allocator::template rebind<RBnode>::other	node_allocator_type;

	public:

		/* Member Types */

		typedef				T										value_type;
		typedef				size_t									size_type;
		typedef				std::ptrdiff_t							difference_type;
		typedef				Compare									value_compare;
		typedef				Allocator								allocator_type;
		typedef typename	Allocator::reference					reference;
		typedef typename	Allocator::const_reference				const_reference;
		typedef typename	Allocator::pointer						pointer;
		typedef typename	Allocator::const_pointer				const_pointer;
		typedef				iterator_t<T>							iterator;
		typedef				iterator_t<T const>						const_iterator;
		typedef				ft::reverse_iterator<iterator>			reverse_iterator;
		typedef				ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		/* Exceptions */ 

		class ElementNotFoundException : public std::exception {
			public:
				virtual const char * what() const throw() {
					return "Element not found";
				}
		};

		/* Constructors and destructors */

		RBtree(Compare const & comp = Compare(), Allocator const & alloc = Allocator())
		: comp(comp), value_alloc(alloc), node_alloc(alloc), leaf(construct()) {

			size = 0;
			root = leaf;
			leaf->parent = root;
		}
		RBtree(const RBtree & copy) : comp(copy.comp), value_alloc(copy.value_alloc), node_alloc(copy.node_alloc), leaf(construct()) {

			root = leaf;
			leaf->parent = root;
			size = copy.size;
			const_iterator it;
			const_iterator ite = copy.end();
			for (it = copy.begin(); it != ite; it++)
				insert(*it);
		}
		~RBtree() {

			clear();
			destruct(leaf);
		}

		/* Member functions */

		//The compare class has to have () overloads if you wish to compare a key of a different type -> have comp(T, T), comp(Key, T) and comp(T, Key)
		template <typename Key>
		iterator	get(Key const & key) const throw(ElementNotFoundException) {

			RBnode * current = root;

			while (1) {
				if (current == leaf)
					throw ElementNotFoundException();
				else if (!comp(key, *current->data) && !comp(*current->data, key))
					return iterator(current);
				else if (comp(key, *current->data))
					current = current->left;
				else
					current = current->right;
			}
		}
		template <typename Key>
		iterator	lower_bound(Key const & key) {

			RBnode * current = root;
			RBnode * tmp;

			while (current != leaf && comp(*current->data, key))
				current = current->right;
			if (!comp(key, *current->data) && !comp(*current->data, key))
				return iterator(current);

			//I am smaller than current, but bigger than parent or am root
			tmp = current->left;
			while (tmp != leaf) {
				if (!comp(key, *tmp->data) && !comp(*tmp->data, key))
					return iterator(tmp);
//while I am smaller than left one, go left
				while (tmp != leaf && comp(key, *tmp->data)) {
					current = tmp;
					tmp = tmp->left;
				}
//go to the right of left one while it is smaller than me, until it's not or I hit leaf
				while (tmp != leaf && comp(*tmp->data, key))
					tmp = tmp->right;
			}
			return iterator(current);
		}
		template <typename Key>
		iterator	upper_bound(Key const & key) {

			RBnode * current = root;
			RBnode * tmp;

			while (current != leaf && comp(*current->data, key))
				current = current->right;
			if (!comp(key, *current->data) && !comp(*current->data, key))
				return iterator(current->next());

			tmp = current->left;
			while (tmp != leaf) {
				if (!comp(key, *tmp->data) && !comp(*tmp->data, key))
					return iterator(tmp->next());
//while I am smaller than left one, go left
				while (tmp != leaf && comp(key, *tmp->data)) { 
					current = tmp;
					tmp = tmp->left;
				}
//go to the right of left one while it is smaller than me, until it's not or I hit leaf
				while (tmp != leaf && comp(*tmp->data, key)) 
					tmp = tmp->right;
			}
			return iterator(current);
		}
		iterator	insert(value_type const & data) {

			RBnode * node = insert_recolor(bst_insert(data));
			leaf->parent = root;
			++size;
			return iterator(node);
		}
		template <typename Key>
		size_type	remove(Key const & key) {

			RBnode * node;
			node = bst_delete<Key>(key);
			if (!node)
				return 0;
			--size;
			remove_recolor(node);
			leaf->parent = root;
			return 1;
		}
		void		remove(iterator & it) {

			if (!it.node || it.node == leaf)
				return;
			RBnode * node = bst_delete(it.node);
			remove_recolor(node);
			leaf->parent = root;
		}
		void		clear() {

			while(root != leaf)
				bst_delete(root);
		}
		size_type	get_size() const { return size; }
		void		output() const { output(root, 0); }
		void		inorder_print() const {

			const_iterator it;
			const_iterator ite = end();

			for(it = begin(); it != ite; it++)
				std::cout << *it << std::endl;
		}
		void		r_inorder_print() const {

			const_reverse_iterator it;
			const_reverse_iterator ite = rend();

			for (it = rbegin(); it != ite; ++it)
				std::cout << *it << std::endl;
		}

		/* iterators*/

		iterator				begin() {

			RBnode * tmp = root;

			if (tmp == leaf)
				return iterator(leaf);
			while (tmp->left != leaf)
				tmp = tmp->left;
			return iterator(tmp);
		}
		iterator				end() { return iterator(leaf); }
		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_iterator			begin() const {

			RBnode * tmp = root;

			if (tmp == leaf)
				return const_iterator(leaf);
			while (tmp->left != leaf)
				tmp = tmp->left;
			return const_iterator(tmp);
		}
		const_iterator			end() const { return const_iterator(leaf); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

		/* Operator overloads */

		RBtree &				operator=(const RBtree<value_type> & rhs) {

			while (root != leaf)
				bst_delete(root);
			const_iterator it;
			const_iterator ite = rhs.end();
			for (it = rhs.begin(); it != ite; it++)
				insert(*it);
			return *this;
		}

	private:

		/* classes, structs and enums */

		typedef enum color {

			BLACK,
			RED
		} color_t;
		typedef enum side {

			LEFT,
			RIGHT
		} side_t;
		class RBnode {

			public :


				value_type * data;
				color_t color;
				bool is_double;
				side_t side;
				RBnode * parent;
				RBnode * left;
				RBnode * right;
				allocator_type & value_alloc;

				RBnode(allocator_type & value_alloc) : value_alloc(value_alloc) {

					this->data = NULL;
					color = BLACK;
					is_double = false;
					parent = NULL;
					left = right = NULL;
				}

				RBnode(value_type const & data, RBnode * const leaf, allocator_type & value_alloc) : value_alloc(value_alloc) {

					this->data = value_alloc.allocate(1);
					value_alloc.construct(this->data, data);

					color = RED;
					is_double = false;
					parent = NULL;
					left = right = leaf;
				}

				RBnode(RBnode const & cpy) : value_alloc(cpy.value_alloc) { *this = cpy; }

				RBnode & operator=(RBnode const & rhs) {

					if (rhs.data) {
						this->data = value_alloc.allocate(1);
						value_alloc.construct(this->data, *rhs.data);
					} else {
						this->data = NULL;
					}

					color = rhs.color;
					is_double = rhs.is_double;
					parent = rhs.parent;
					left = rhs.left;
					right = rhs.right;
					side = rhs.side;

					return *this;
				}

				~RBnode() {

					if (data) {
						value_alloc.destroy(data);
						value_alloc.deallocate(data, 1);
					}
				}

				RBnode * next() const {

					RBnode * tmp;

					if (this->is_leaf()) { //shouldn't be happening
						return const_cast<RBnode *>(this);
					} else if (!right->is_leaf()) {
						tmp = right;
						while (!tmp->left->is_leaf())
							tmp = tmp->left;
						return tmp;
					} else if (parent) {
						tmp = const_cast<RBnode *>(this);
						while (tmp->side == RIGHT && tmp->parent)
							tmp = tmp->parent;
						if (tmp->parent)
							return tmp->parent;
						else //rightmost node
							return right; //leaf
					} else { //root and no right child
						return right; //leaf
					}
				}

				RBnode * previous() const {

					RBnode * tmp;

					if (this->is_leaf()) {
						tmp = parent; //root
						while (!tmp->right->is_leaf())
							tmp = tmp->right;
						return tmp;
					} else if (!left->is_leaf()) {
						tmp = left;
						while (!tmp->right->is_leaf())
							tmp = tmp->right;
						return tmp;
					} else if (parent) {
						tmp = const_cast<RBnode *>(this);
						while (tmp->side == LEFT && tmp->parent)
							tmp = tmp->parent;
						return tmp->parent;
					} else {
						return const_cast<RBnode *>(this); //first element
					}
				}

				bool is_leaf() const {
					return left == NULL && right == NULL;
				}

		};
		RBnode * construct() {

			RBnode * node;

			node = node_alloc.allocate(1);
			node_alloc.construct(node, RBnode(value_alloc));
			node->left = node->right = NULL;
			return node;
		}
		RBnode * construct(value_type const & data) {

			RBnode * node;

			node = node_alloc.allocate(1);
			node_alloc.construct(node, RBnode(data, leaf, value_alloc));
			return node;
		}
		RBnode * construct(RBnode const & cpy) {

			RBnode * node;

			node = node_alloc.allocate(1);
			node_alloc.construct(node, cpy);
			return node;
		}
		void destruct(RBnode * node) {

			node_alloc.destroy(node);
			node_alloc.deallocate(node, 1);
		}

		//does not keep ordering
		void swap_nodes(RBnode * lhs, RBnode * rhs) {

			if (lhs != root) {
				if (rhs != root)
					std::swap(lhs->side == LEFT ? lhs->parent->left : lhs->parent->right,
							rhs->side == LEFT ? rhs->parent->left : rhs->parent->right);
				else
					std::swap(lhs->side == LEFT ? lhs->parent->left : lhs->parent->right, root);
			} else {
				std::swap(root, rhs->side == LEFT ? rhs->parent->left : rhs->parent->right);
			}
			std::swap(lhs->parent, rhs->parent);
			lhs->left->parent = lhs->right->parent = rhs;
			rhs->left->parent = rhs->right->parent = lhs;
			std::swap(lhs->left, rhs->left);
			std::swap(lhs->right, rhs->right);
			std::swap(lhs->side, rhs->side);
			std::swap(lhs->color, rhs->color);
			std::swap(lhs->is_double, rhs->is_double); //should never be double
		}

		template <typename U>
		class iterator_t {

			public:

				typedef typename ft::iterator_traits<U *>::difference_type difference_type;
				typedef typename ft::iterator_traits<U *>::value_type value_type;
				typedef typename ft::iterator_traits<U *>::pointer pointer;
				typedef typename ft::iterator_traits<U *>::reference reference;
				typedef std::bidirectional_iterator_tag iterator_category;

				iterator_t() : node(NULL) {}
				iterator_t(RBnode * node) : node(node) {}
				template <typename V>
				iterator_t(iterator_t<V> const & cpy) { *this = cpy; }
				~iterator_t() {};

				iterator_t & operator++() {
					node = node->next();
					return *this;
				}

				iterator_t   operator++(int) {
					iterator_t cpy(*this);

					node = node->next();
					return cpy;
				}

				iterator_t & operator--() {
					node = node->previous();
					return *this;
				}

				iterator_t   operator--(int) {
					iterator_t cpy(*this);

					node = node->previous();
					return cpy;
				}


				reference operator*() const { return *node->data; }
				pointer operator->() const { return node->data; }

				template <typename V>
				iterator_t & operator=(iterator_t<V> const & rhs) {
					node = rhs.node;
					return *this;
				}

				template <typename V>
				friend bool operator==(iterator_t<U> const & lhs, iterator_t<V> const & rhs) { return lhs.node == rhs.node; }

				template <typename V>
				friend bool operator!=(iterator_t<U> const & lhs, iterator_t<V> const & rhs) { return lhs.node != rhs.node; }

				RBnode * node;

		};

		/* Member functions */

		void left_rotate(RBnode * node) {

			RBnode * tmp;

			if (node == root) {
				root = node->right;
			} else if (node->side == LEFT) {
				node->parent->left = node->right;
			} else {
				node->parent->right = node->right;
			}
			node->right->parent = node->parent;
			node->right->side = node->side;

			tmp = node->right;
			node->right = node->right->left;
			if (node->right != leaf) {
				node->right->side = RIGHT;
				node->right->parent = node;
			}
			tmp->left = node;
			node->parent = tmp;
			node->side = LEFT;
		}
		void right_rotate(RBnode * node) {

			RBnode * tmp;

			if (node == root) {
				root = node->left;
			} else if (node->side == LEFT) {
				node->parent->left = node->left;
			} else {
				node->parent->right = node->left;
			}
			node->left->parent = node->parent;
			node->left->side = node->side;

			tmp = node->left;
			node->left = node->left->right;
			if (node->left != leaf) {
				node->left->side = LEFT;
				node->left->parent = node;
			}
			tmp->right = node;
			node->parent = tmp;
			node->side = RIGHT;
		}
		RBnode * insert_recolor(RBnode * node) {

			if (node == root) {
				node->color = BLACK;
				return node;
			} else if (node->parent->color == BLACK) {
				return node;
			}

			RBnode * uncle;
			RBnode * parent = node->parent;
			RBnode * grandfather = node->parent->parent;

			if (parent->side == LEFT) {
				uncle = grandfather->right;
			} else {
				uncle = grandfather->left;
			}

			if (uncle->color == RED) {
				parent->color = BLACK;
				uncle->color = BLACK;
				grandfather->color = RED;
				insert_recolor(grandfather);
				return node;
			}

			if (parent->side == LEFT) {
				if (node->side == RIGHT) {
					left_rotate(parent);
					parent = node;
				}
				right_rotate(grandfather);
			} else {
				if (node->side == LEFT) {
					right_rotate(parent);
					parent = node;
				}
				left_rotate(grandfather);
			}
			parent->color = BLACK;
			grandfather->color = RED; // is now uncle
			return node;
		}
		void remove_recolor(RBnode * node) {

			RBnode * sibling;
			RBnode * parent;

			if (!node->is_double || node == root) {
				node->is_double = false;
				return ;
			}

			parent = node->parent;
			if (node->side == LEFT)
				sibling = parent->right;
			else
				sibling = parent->left;

			if (sibling->color == RED) {
				if (sibling->side == RIGHT)
					left_rotate(parent);
				else
					right_rotate(parent);
				sibling->color = BLACK;
				parent->color = RED;
				if (node->side == LEFT)
					sibling = parent->right;
				else
					sibling = parent->left;
			}

			if (sibling == leaf ||
					(sibling->color == BLACK && sibling->left->color == BLACK && sibling->right->color == BLACK)) {
				if (sibling != leaf)
					sibling->color = RED;
				if (parent->color == RED)
					parent->color = BLACK;
				else
					parent->is_double = true;
				remove_recolor(parent);
			} else if (sibling->color == BLACK &&
					(sibling->left->color == RED || sibling->right->color == RED)) {
				if (sibling->side == RIGHT) {
					if (sibling->right->color == BLACK) {
						right_rotate(sibling);
						sibling->color = RED;
						sibling->parent->color = BLACK;
						sibling = sibling->parent;
					}
					left_rotate(parent);
					sibling->right->color = BLACK;
				} else {
					if (sibling->left->color == BLACK) {
						left_rotate(sibling);
						sibling->color = RED;
						sibling->parent->color = BLACK;
						sibling = sibling->parent;
					}
					right_rotate(parent);
					sibling->left->color = BLACK;
				}
			}
		}
		RBnode * bst_insert(value_type const & data) {

			if (root == leaf) {
				root = construct(data);
				return root;
			}

			RBnode * current = root;
			while (1) {
				if (current == leaf)
					std::cerr << "leaf" << std::endl;
				if (!comp(data, *(current->data))) {
					if (current->right != leaf)
						current = current->right;
					else {
						current->right = construct(data);
						current->right->side = RIGHT;
						current->right->parent = current;
						return current->right;
					}
				}
				else {
					if (current->left != leaf)
						current = current->left;
					else {
						current->left = construct(data);
						current->left->side = LEFT;
						current->left->parent = current;
						return current->left;
					}
				}
			}
		}
		RBnode * bst_delete(RBnode * node) {

			RBnode * successor;

			if (node == leaf)
				return leaf;
			if (node->right == leaf || node->left == leaf) {
				if (node->right == leaf) {
					successor = node->left;
				} else {
					successor = node->right;
				}

				if (node != root) {
					if (node->side == LEFT) {
						node->parent->left = successor;
						successor->parent = node->parent;
						successor->side = LEFT;
					} else {
						node->parent->right = successor;
						successor->parent = node->parent;
						successor->side = RIGHT;
					}
				} else {
					root = successor;
					successor->parent = NULL;
				}
				if (node->color == BLACK && successor->color == BLACK)
					successor->is_double = true;
				destruct(node);

				return successor;
			} else {
				successor = node->next(); //cannot be leaf
				swap_nodes(node, successor);
//				node->data = successor->data; //TODO invalidates iterators
//				successor->data = NULL; //to not delete data when deleting successor
				return (bst_delete(node));
			}
		}
		template<typename Key>
		RBnode * bst_delete(Key const & key) {

			RBnode * current = root;

			while (1) {
				if (current == leaf)
					return NULL; //can't return leaf because it can also happen when a node got deleted
				else if (!comp(key, *current->data) && !comp(*current->data, key))
					return bst_delete(current);
				else if (comp(key, *current->data))
					current = current->left;
				else
					current = current->right;
			}
		}
		void output(RBnode const * node, int depth) const {

			if (node == leaf) {
				std::cout << std::string(depth, '\t') << "\033[47m \033[0m" << std::endl;
				return;
			}
			output(node->right, depth + 1);
			if (node->color == RED)
				std::cout << std::string(depth, '\t') << REDSTR << *node->data << RESET << std::endl;
			else
				std::cout << std::string(depth, '\t') << *node->data << std::endl;
			output(node->left, depth + 1);
		}

		/* Member variables */

		RBnode * root;
		value_compare comp;
		allocator_type value_alloc;
		node_allocator_type node_alloc;
		RBnode * const leaf;
		size_type size;


};

/* for a static leaf
   template<typename T, typename Compare, typename Allocator>
   typename RBtree<T, Compare, Allocator>::RBnode * RBtree<T, Compare, Allocator>::leaf = RBtree<T, Compare, Allocator>::RBnode::construct();
   */

}
