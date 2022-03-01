/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:35:09 by ade-la-c          #+#    #+#             */
/*   Updated: 2022/03/01 19:18:39 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <iostream>
# include <memory>
# include <iterator>

namespace	ft {


template< class T, class Alloc = std::allocator<T> >
class	vector {


public:

	//	Type definers

	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef typename ft::wrap_iter<pointer> iterator;
	typedef typename ft::wrap_iter<const_pointer> const_iterator;
	typedef typename ft::reverse_iterator<iterator> reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename allocator_type::size_type size_type;
	typedef typename allocator_type::difference_type difference_type;

	//	MEMBER FONCTIONS

	explicit vector( const allocator_type & Alloc = allocator_type() )
	: _len(0), _size(0) {} // fill constructor, n elements of value val
	explicit vector( size_type n, const value_type & val = value_type(), const allocator_type & Alloc = allocator_type() )
	: _len(0), _size(0) {

		// write a private function to allocate the correct size of cells 1 by 1, growing the size progressively...
	}
	template< class InputIterator > // range constructor constructs with as many elements as the range (first, last)
	vector( InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type() );
	vector( const vector & x );
	vector &	operator=( const vector & x );
	~vector( void );

	//	Iterators

	iterator				begin( void );
	const_iterator			begin( void ) const;
	iterator				end( void );
	const_iterator			end( void ) const;
	reverse_iterator		rbegin( void );
	const_reverse_iterator	rbegin( void ) const;
	reverse_iterator		rend( void );
	const_reverse_iterator	rend( void ) const;

	//	Capacity

	size_type		size( void ) const;
	size_type		max_size( void ) const;
	void			resize( size_type n, value_type val = value_type() );
	size_type		capacity( void ) const;
	bool			empty( void ) const;
	void			reserve( size_type n );

	//	Element access

	reference			operator[]( size_type n );
	const_reference		operator[]( size_type n ) const;
	reference			at( size_type n );
	const_reference		at( size_type n ) const;
	reference			front( void );
	const_reference		front( void ) const;
	reference			back( void );
	const_reference		back( void ) const;

	//	Modifiers

	template< class InputIterator >
	void		assign( InputIterator first, InputIterator last );
	void		assign( size_type n, const value_type & val );
	void		push_back( const value_type & val );
	void		pop_back( void );
	iterator	insert( iterator position, const value_type & val ); // single element
	void		insert( iterator position, size_type n, const value_type & val ); // fill
	template< class InputIterator > // range
	void		insert( iterator position, InputIterator first, InputIterator last );
	iterator	erase( iterator position );
	iterator	erase( iterator first, iterator last );
	void		swap( vector & x);
	void		clear( void );

	//	Allocator

	allocator_type	get_allocator( void ) const;


private:

	int				_size;	// number of cells allocated
	int				_len;	// number of cells filled
	value_type *	_valueArray;

};

	template < class T, class Alloc >
	bool	operator==( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs );
	template < class T, class Alloc >
	bool	operator!=( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs );
	template < class T, class Alloc >
	bool	operator<( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs );
	template < class T, class Alloc >
	bool	operator<=( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs );
	template < class T, class Alloc >
	bool	operator>(const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs);
	template < class T, class Alloc >
	bool	operator>=( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs );
	template< class T, class Alloc >
	void	swap( vector<T,Alloc> & x, vector<T,Alloc> & y );

}

#endif
