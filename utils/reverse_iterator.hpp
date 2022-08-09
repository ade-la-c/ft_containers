#pragma once

#include "utils.hpp"

namespace	ft {


	template<class Iterator>
	class	reverse_iterator {


		public:

			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;

			reverse_iterator( void ) : _content() {}
			explicit reverse_iterator( iterator_type it ) : _content(it) {}
			template<class Iter>
			reverse_iterator( const reverse_iterator<Iter> & rev_it )
			: _content(rev_it.base()) {}
			virtual	~reverse_iterator( void ) {}

			iterator_type		base( void ) const { return _content; }
			reference			operator*( void ) const {

				Iterator	tmp = this->_content;
				return *--tmp;
			}
			reverse_iterator	operator+( difference_type n ) const { return reverse_iterator(_content - n); }
			reverse_iterator &	operator++( void ) {

				this->_content--;
				return *this;
			}
			reverse_iterator	operator++( int ) {

				reverse_iterator	tmp = *this;
				this->_content--;
				return tmp;
			}
			reverse_iterator &	operator+=( difference_type n ) {

				this->_content -= n;
				return *this;
			}
			reverse_iterator	operator-( difference_type n ) const { return reverse_iterator(_content + n); }
			reverse_iterator &	operator--( void ) {

				this->_content++;
				return *this;
			}
			reverse_iterator	operator--( int ) {

				reverse_iterator	tmp = *this;
				this->_content++;
				return tmp;
			}
			reverse_iterator	operator-=( difference_type n ) {

				this->_content += n;
				return *this;
			}
			pointer				operator->( void ) const { return & (reverse_iterator::operator*()); }
			reference			operator[]( difference_type n ) const { return this->base()[-n - 1]; }


		private:

			iterator_type	_content;

	};

	template<class Iterator>
	bool 	operator==( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator> & rhs )
	{ return lhs.base() == rhs.base(); }

	template<class Iterator, class Iterator2>
	bool 	operator==( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator2> & rhs )
	{ return lhs.base() == rhs.base(); }

	template<class Iterator>
	bool 	operator!=( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator> & rhs )
	{ return lhs.base() != rhs.base(); }

	template<class Iterator, class Iterator2>
	bool 	operator!=( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator2> & rhs )
	{ return lhs.base() != rhs.base(); }

		template<class Iterator>
	bool 	operator<( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator> & rhs )
	{ return lhs.base() > rhs.base(); }

	template<class Iterator, class Iterator2>
	bool 	operator<( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator2> & rhs )
	{ return lhs.base() > rhs.base(); }

	template<class Iterator>
	bool 	operator>( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator> & rhs )
	{ return lhs.base() < rhs.base(); }

	template<class Iterator, class Iterator2>
	bool 	operator>( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator2> & rhs )
	{ return lhs.base() < rhs.base(); }

	template<class Iterator>
	bool 	operator<=( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator> & rhs )
	{ return lhs.base() >= rhs.base(); }

	template<class Iterator, class Iterator2>
	bool 	operator<=( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator2> & rhs )
	{ return lhs.base() >= rhs.base(); }

	template<class Iterator>
	bool 	operator>=( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator> & rhs )
	{ return lhs.base() <= rhs.base(); }

	template<class Iterator, class Iterator2>
	bool 	operator>=( const ft::reverse_iterator<Iterator> & lhs,
						const ft::reverse_iterator<Iterator2> & rhs )
	{ return lhs.base() <= rhs.base(); }

	template<class Iterator>
	bool	operator+( typename reverse_iterator<Iterator>::difference_type & n,
						const ft::reverse_iterator<Iterator> & rev_it )
	{ return rev_it + n; }

	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type
		operator-( const ft::reverse_iterator<Iterator> & lhs, const ft::reverse_iterator<Iterator> & rhs )
	{ return lhs.base() - rhs.base(); }

	template<class Iterator, class Iterator2>
	typename reverse_iterator<Iterator>::difference_type
		operator-( const ft::reverse_iterator<Iterator> & lhs, const ft::reverse_iterator<Iterator2> & rhs )
	{ return lhs.base() - rhs.base(); }

}
