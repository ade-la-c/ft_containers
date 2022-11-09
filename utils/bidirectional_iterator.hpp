#pragma once

#include <iostream>

#include "utils.hpp"
#include "rbt_n.hpp"

namespace	ft {


	template< typename T >
	class bidirectional_iterator {
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
			template< class U >
			bidirectional_iterator(const bidirectional_iterator< U >& x) : _node(x._node), _end(x._end) {}

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
			reference	operator*() const {
				return (this->_node->data);
			}
			/*	Operator++ - Increment iterator position */
			bidirectional_iterator &		operator++(void) {
				node_pointer	cursor = _node;

				if (_node->right == _end) {
					cursor = _node->parent;
					while (cursor != NULL && cursor != _end && cursor->data.first < _node->data.first)
						cursor = cursor->parent;
					if (cursor == 0)
						_node = _end;
					else
						_node = cursor;
				} else if (cursor == _end) {
					_node = _end;
				} else {
					cursor = _node->right;
					if (cursor == _end->parent && cursor->right == _end)
						_node = cursor;
					else {
						while (cursor->left != _end)
							cursor = cursor->left;
					}
					_node = cursor;
				}
				return (*this);
			}

			bidirectional_iterator			operator++(int) {
				bidirectional_iterator	tmp(*this);

				operator++();
				return (tmp);
			}
			/*	Operator-- - Decrease iterator opinion */
			bidirectional_iterator &		operator--(void) {
				node_pointer	cursor = _node;

				if (_node->left == _end) {
					cursor = _node->parent;
					while (cursor != NULL && cursor != _end && cursor->data.first > _node->data.first)
						cursor = cursor->parent;
					_node = cursor;
					if (cursor == 0)
						_node = _end->right;
					else
						_node = cursor;
				} else if (cursor == _end) {
					_node = _end->right;
				} else {
					cursor = _node->left;
					if (cursor == _end->parent && cursor->left == _end)
						_node = cursor;
					else {
						while (cursor->right != _end)
							cursor = cursor->right;
					}
					_node = cursor;
				}
				return (*this);
			}

			bidirectional_iterator			operator--(int) {
				bidirectional_iterator	tmp(*this);

				operator--();
				return (tmp);
			}
			/*	Operator-> - Dereference iterator */
			pointer		operator->() const {
				return (&this->_node->data);
			}

		private:
			node_pointer	_node;
			node_pointer	_end;
	};



}
