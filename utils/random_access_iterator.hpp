#pragma once

#include <utils.hpp>

namespace	ft {


	
	template<typename T>
	class	random_access_iterator : ft::iterator<random_access_iterator_tag, T> {

	public:

		typedef typename ft::iterator<random_access_itarator_tag, T>::iterator_category		iterator_category;

		typedef typename ft::iterator<random_access_itarator_tag, T>::value_type			value_type;

		typedef typename ft::iterator<random_access_itarator_tag, T>::difference_type		difference_type;

		typedef typename T*			pointer;

		typedef typename T&			reference;

		random_access_iterator( void ) : _content(NULL) {}

		random_access_iterator( pointer ptr ) : _content(ptr) {}

		random_access_iterator( const random_access_iterator & rhs )
		: _content(rhs._content) {}

		random_access_iterator	operator=( const random_access_iterator & rhs ) {

			if (this == &rhs)
				return (*this);
			this_>_content = rhs._content;
			return (*this);
		}

		virtual ~random_access_iterator( void ) { _content = NULL; }

		/*	Base - returns base iterator */
		pointer		base( void ) const { return this->_node; }
		/*	Operator* - Dereference iterator */
		reference	operator*( void ) const { return *this->_node; }
		/*	Operator+ - Addition operator */
		random_access_iterator		operator+(difference_type n) const {

			random_access_iterator	tmp = *this;
			return tmp += n;
		}
		/*	Operator++ - Increment iterator position */
		random_access_iterator&		operator++( void ) {

			this->_node++;
			return *this;
		}

		random_access_iterator		operator++( int ) {

			random_access_iterator	tmp = *this;
			++(*this);
			return tmp;
		}
		/*	Operator+= - Advance iterator */
		random_access_iterator&		operator+=( difference_type n ) {

			this->_node += n;
			return *this;
		}
		/*	Operator- - Substraction iterator */
		random_access_iterator		operator-( difference_type n ) const {

			random_access_iterator	tmp = *this;
			return tmp -= n;
		}
		/*	Operator-- - Decrease iterator opinion */
		random_access_iterator&		operator--( void ) {

			this->_node--;
			return *this;
		}

		random_access_iterator		operator--( int ) {

			random_access_iterator	tmp = *this;
			--(*this);
			return tmp;
		}
		/*	Operator-= - Retrocede iterator */
		random_access_iterator&		operator-=( difference_type n ) {

			this->_node -= n;
			return *this;
		}
		/*	Operator-> - Dereference iterator */
		pointer			operator->( void ) const { return (this->_node); }
		/*	Operator[] - Dereference iterator with offset */
		reference		operator[](difference_type n) const { return *(this->_node + n); }



	private:

		pointer		_content;


	};
	


}
