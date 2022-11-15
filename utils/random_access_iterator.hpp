#pragma once

#include "utils.hpp"

namespace	ft {


	template< class T >
	class	random_access_iterator {
		public:
			/* ************************ Member Types ************************ */
			typedef typename ft::iterator_traits< T* >::iterator_category	iterator_category;
			typedef typename ft::iterator_traits< T* >::value_type			value_type;
			typedef typename ft::iterator_traits< T* >::difference_type		difference_type;
			typedef typename ft::iterator_traits< T* >::pointer				pointer;
			typedef typename ft::iterator_traits< T* >::reference			reference;

			/* ************************ Constructors ************************ */
			/*	 Default */
			random_access_iterator(pointer ptr = nullptr) : _node(ptr) {}
			/*	Copy */
			template< class V >
			random_access_iterator(const random_access_iterator<V>& x) : _node(x.base()) {}
			/*	Destructor */
			~random_access_iterator() {
				_node = nullptr;
			}

			/* ********************** Base & Operators ********************** */
			/*	Base - returns base iterator */
			pointer	base() const {
				return (this->_node);
			}
			/*	Operator* - Dereference iterator */
			reference	operator*() const {
				return (*this->_node);
			}
			/*	Operator+ - Addition operator */
			random_access_iterator	operator+(difference_type n) const {
				random_access_iterator	tmp = *this;
				return (tmp += n);
			}
			/*	Operator++ - Increment iterator position */
			random_access_iterator&	operator++() {
				this->_node++;
				return (*this);
			}

			random_access_iterator	operator++(int) {
				random_access_iterator	tmp = *this;
				++(*this);
				return (tmp);
			}
			/*	Operator+= - Advance iterator */
			random_access_iterator&	operator+=(difference_type n) {
				this->_node += n;
				return (*this);
			}
			/*	Operator- - Substraction iterator */
			random_access_iterator	operator-(difference_type n) const {
				random_access_iterator	tmp = *this;
				return (tmp -= n);
			}
			/*	Operator-- - Decrease iterator opinion */
			random_access_iterator&	operator--() {
				this->_node--;
				return (*this);
			}

			random_access_iterator	operator--(int) {
				random_access_iterator	tmp = *this;
				--(*this);
				return (tmp);
			}
			/*	Operator-= - Retrocede iterator */
			random_access_iterator&	operator-=(difference_type n) {
				this->_node -= n;
				return (*this);
			}
			/*	Operator-> - Dereference iterator */
			pointer	operator->() const {
				return (this->_node);
			}
			/*	Operator[] - Dereference iterator with offset */
			reference	operator[](difference_type n) const {
				return *(this->_node + n);
			}

		private:
			pointer	_node;
	};

	/* *************** Non Members Vector Iterator Functions **************** */
	// Operator==
	template< class T >
	bool	operator==(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T> & rhs) {
		return (lhs.base() == rhs.base());
	}
	template< class T, class U >
	bool	operator==(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<U> & rhs) {
		return (lhs.base() == rhs.base());
	}

	// Operator !=
	template< class T >
	bool	operator!=(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T> & rhs) {
		return (lhs.base() != rhs.base());
	}
	template< class T, class U >
	bool	operator!=(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<U> & rhs) {
		return (lhs.base() != rhs.base());
	}

	// Operator<
	template< class T >
	bool	operator<(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T> & rhs) {
		return (lhs.base() < rhs.base());
	}
	template< class T, class U >
	bool	operator<(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<U> & rhs) {
		return (lhs.base() < rhs.base());
	}

	// Operator<=
	template< class T >
	bool	operator<=(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T> & rhs) {
		return (lhs.base() <= rhs.base());
	}
	template< class T, class U >
	bool	operator<=(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<U> & rhs) {
		return (lhs.base() <= rhs.base());
	}

	// Operator>
	template< class T >
	bool	operator>(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T> & rhs) {
		return (lhs.base() > rhs.base());
	}
	template< class T, class U >
	bool	operator>(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<U> & rhs) {
		return (lhs.base() > rhs.base());
	}

	// Operator>=
	template< class T >
	bool	operator>=(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T> & rhs) {
		return (lhs.base() >= rhs.base());
	}
	template< class T, class U >
	bool	operator>=(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<U> & rhs) {
		return (lhs.base() >= rhs.base());
	}

	// Operator+
	template< class T >
	random_access_iterator<T>	operator+(typename ft::random_access_iterator<T>::difference_type n, const ft::random_access_iterator<T> & iter) {
		return (random_access_iterator<T>(iter.base() + n));
	}

	// Operator-
	template< class T >
	typename ft::random_access_iterator<T>::diffrence_type	operator-(const random_access_iterator<T> & lhs, const ft::random_access_iterator<T> & rhs) {
		return (lhs.base() - rhs.base());
	}
	template< class T, class U >
	typename ft::random_access_iterator<T>::difference_type	operator-(const random_access_iterator<T> & lhs, const ft::random_access_iterator<U> & rhs) {
		return (lhs.base() - rhs.base());
	}



}
