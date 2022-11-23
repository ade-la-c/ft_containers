#pragma once

#include <iostream>

#include "utils.hpp"
#include "rbt_n.hpp"

namespace	ft {


	template< typename T >
	class	bidirectional_iterator {

		public:
			/* ************************ Member Types ************************ */
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::iterator_category	iterator_category;
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::value_type			value_type;
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::difference_type	difference_type;
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::pointer			pointer;
			typedef typename	ft::iterator_traits< ft::iterator< ft::bidirectional_iterator_tag, T> >::reference			reference;
			typedef				ft::Node< T >																				node_reference;
			typedef				ft::Node< T >*																				node_pointer;

			/* ************************ Constructors ************************ */
			/*	Default */
			bidirectional_iterator() : _node(NULL), _end(NULL) {}
			bidirectional_iterator(node_pointer node, node_pointer end) : _node(node), _end(end) {}

			/*	Copy */
			bidirectional_iterator(const bidirectional_iterator& x) : _node(x._node), _end(x._end) {}

			/*	Operator= */
			template< class U >
			bidirectional_iterator & operator=(const bidirectional_iterator & x) {
				if (this != &x) {
					this->_node = x._node;
					this->_end = x._end;
					this->_comp = x.comp;
				}
			}

			/*	Destructor */
			~bidirectional_iterator() {}

			/* ********************** Base & Operators ********************** */
			/*	Base - returns base iterator */
			node_pointer	base() const {
				return (this->_node);
			}
			/*	Operator* - Dereference iterator */
			reference	operator*() {
				return (this->_node->data);
			}
			const reference	operator*() const {
				return (this->_node->data);
			}

			/*	Operator++ - Increment iterator position */
			bidirectional_iterator &		operator++(void) {

				if (_node->right != _end) {

					_node = _node->right;
					while (_node->left != _end) { _node = _node->left; }

				} else {

					node_pointer tmp = _node;
					while (tmp->parent && tmp == tmp->parent->right) {
						tmp = tmp->parent;
					}
					if (tmp->parent != _end) { _node = tmp->parent; }
					if (!_node) { _node = _end; }

				}
				return *this;
			}

			bidirectional_iterator			operator++(int) {
				bidirectional_iterator	tmp(*this);

				operator++();
				return (tmp);
			}
			/*	Operator-- - Decrease iterator opinion */
			bidirectional_iterator &		operator--(void) {

				if ( _node == _end ) {

					while (_node->parent) { _node = _node->parent; }
					while (_node->right != _end) { _node = _node->right; }

				} else if (_node->left != _end) {

					_node = _node->left;
					while (_node->right != _end) { _node = _node->right; }

				} else {

					node_pointer tmp = _node;
					while (tmp->parent && tmp == tmp->parent->left) {
						tmp = tmp->parent;
					}
					_node = tmp->parent;
					if (!_node) { _node = _end; }
				}
				return *this;
			}

			bidirectional_iterator			operator--(int) {
				bidirectional_iterator	tmp(*this);

				operator--();
				return (tmp);
			}
			/*	Operator-> - Dereference iterator */
			pointer		operator->() {
				return (&this->_node->data);
			}

			const pointer		operator->() const {
				return (&this->_node->data);
			}

			operator bidirectional_iterator< const T >() const {
				return bidirectional_iterator< const T >( (typename bidirectional_iterator< const T >::node_pointer) _node,
															(typename bidirectional_iterator< const T >::node_pointer) _end);
			}

			const node_pointer	getNode() const { return _node; }
			node_pointer	getNode() { return _node; }
			const node_pointer	getEnd() const { return _end; }
			node_pointer	getEnd() { return _end; }

		private:

			node_pointer	_node;
			node_pointer	_end;
	};

	template< class T >
	bool	operator==(const ft::bidirectional_iterator< T >& lhs, const ft::bidirectional_iterator< T >& rhs)
	{ return ((void*)lhs.base() == (void*)(rhs.base())); }
	template< class T >
	bool	operator==(const ft::bidirectional_iterator< T >& lhs, const ft::bidirectional_iterator< const T >& rhs)
	{ return ((void*)lhs.base() == (void*)(rhs.base())); }
	template< class T >
	bool	operator==(const ft::bidirectional_iterator< const T >& lhs, const ft::bidirectional_iterator< T >& rhs)
	{ return ((void*)lhs.base() == (void*)(rhs.base())); }
	template< class T >
	bool	operator!=(const ft::bidirectional_iterator< T >& lhs, const ft::bidirectional_iterator< T >& rhs)
	{ return ((void*)lhs.base() != (void*)(rhs.base())); }
	template< class T >
	bool	operator!=(const ft::bidirectional_iterator< T >& lhs, const ft::bidirectional_iterator< const T >& rhs)
	{ return ((void*)lhs.base() != (void*)(rhs.base())); }
	template< class T >
	bool	operator!=(const ft::bidirectional_iterator< const T >& lhs, const ft::bidirectional_iterator< T >& rhs)
	{ return ((void*)lhs.base() != (void*)(rhs.base())); }

}
