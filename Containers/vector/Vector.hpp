/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:35:09 by ade-la-c          #+#    #+#             */
/*   Updated: 2022/06/28 16:12:46 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <iostream>
# include <memory>
# include <iterator>		//! must remove include

//! # include <../iterator/random_access_iterator.hpp>

namespace	ft {


	template< class T, class Alloc = std::allocator<T> >
	class	vector {


	public:

		//	Type definers

		typedef T													value_type;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;

		typedef typename std::__wrap_iter<pointer>						iterator;				//!-------------------------------/
		typedef typename std::__wrap_iter<const_pointer>				const_iterator;			//!			TEMPORAIRE			 /
		typedef typename std::reverse_iterator<iterator>				reverse_iterator;		//!								/
		typedef typename std::reverse_iterator<const_iterator>		const_reverse_iterator;		//!----------------------------/


		// typedef typename ft::wrap_iter<pointer>						iterator;
		// typedef typename ft::wrap_iter<const_pointer>				const_iterator;
		// typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
		// typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename allocator_type::size_type					size_type;
		typedef typename allocator_type::difference_type			difference_type;

		//	MEMBER FUNCTIONS	//

		explicit vector( const allocator_type & alloc = allocator_type() )
		: _capacity(0), _size(0), _alloc(alloc) {}		//* default constructor
		explicit vector( size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type() )	//?
		: _capacity(n), _size(n), _alloc(alloc) {
		
			_alloc.allocate(n, 0);
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(_valueArray[i], val);			//? not sure ab this line
			}
		}		//* fill constructor
		template< class InputIterator >		//* range constructor constructs with as many elements as the range (first, last)
		vector( InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type() ) 
		: _capacity(0), _size(0), _alloc(alloc) {

			while (first != last) {
				push_back(*first);
				++first;
			}
		}
		vector( const vector & x ) { *this = x; }		//* copy constructor
		vector &	operator=( const vector & x ) {					//?

			if (this != &rhs) {
				this->_capacity = x._capacity;
				this->_size = x._size;
				this->_alloc.allocate(x._capacity);					//?	not sure ab this line
				for (int i = 0; i < this->_size; i++)
					this->_valueArray[i] = x._valueArray[i];
			}
			return *this;
		}
		~vector( void ) {

			for (size_type i = 0; i < _size; i++) {
				_alloc.destroy(_valueArray[i]);
			}
			_alloc.deallocate(_valueArray, _capacity);
		} //* destructor

		//	Iterators

		iterator				begin( void ) { return iterator(this->_valueArray); }
		const_iterator			begin( void ) const { return const_iterator(this->_valueArray); }
		iterator				end( void ) { return iterator(this->_valueArray + this->_size); }
		const_iterator			end( void ) const { return const_iterator(this->_valueArray + this->_size); }
		reverse_iterator		rbegin( void ) { return reverse_iteraotr(this->end()); }
		const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(this->end()); }
		reverse_iterator		rend( void ) { return revese_iterator(this->begin()); }
		const_reverse_iterator	rend( void ) const { return const_reverse_iterator(this->begin()); }

		//	Capacity

		size_type		size( void ) const { return this->_size; }
		size_type		max_size( void ) const { return std::numeric_limits<size_type>::max; }
		void			resize( size_type n, value_type val = value_type() ) {

			size_type	x = 0;

			if (n < _size) {
				for (size_type i = n - 1; i < _size; i++ && x++) {
					_alloc.destroy(_valueArray[i]);
				}
				_alloc.deallocate(_valueArray[n - 1], x);
			} else {
				_reallocate(n, false);
				for (size_type i = 0; i < n; i++) {
					_alloc.construct(_valueArray[i], val);
				}
			}
		}
		size_type		capacity( void ) const { return this->_capacity; }
		bool			empty( void ) const { return this->_size == 0 ? true : false; }
		void			reserve( size_type n ) {

			if (n > _capacity) {
				_reallocate(n, true);
			}
		}

		//	Element access

		reference			operator[]( size_type n ) { return this->_valueArray[n]; }
		const_reference		operator[]( size_type n ) const { return this->_valueArray[n]; }
		reference			at( size_type n ) {

			if (n >= _size)
				throw std::out_of_range();
			return this->_valueArray[n];
		}
		const_reference		at( size_type n ) const {

			if (n >= _size)
				throw std::out_of_range();
			return this->_valueArray[n];
		}
		reference			front( void ) { return this->_valueArray[0]; }
		const_reference		front( void ) const { return this->_valueArray[0]; }
		reference			back( void ) { return this->_valueArray[_size - 1]; }
		const_reference		back( void ) const { return this->_valueArray[_size - 1]; }

		//	Modifiers

		template< class InputIterator >	//* range
		void		assign( InputIterator first, InputIterator last ) {//TODO wip

			_reallocate(n, false)
		}
		void		assign( size_type n, const value_type & val ) {//TODO wip

			_reallocate(n, false);
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(_valueArray[i], val);
			}
		}
		void		push_back( const value_type & val ) {

			if (_size + 1 >= _capacity) {
				_reallocate(_capacity * 2, false);
			}
			_alloc.construct(_valueArray[size], val);
			_size++;
			_capacity *= 2;
		}
		void		pop_back( void ) {

			_alloc.destroy(_valueArray[_size - 1]);
			_size--;
		}
		iterator	insert( iterator position, const value_type & val ){			//* single element
		
			ft::vector<int>		tmp_vector();

		}
		void		insert( iterator position, size_type n, const value_type & val );	//* fill
		template< class InputIterator > //* range
		void		insert( iterator position, InputIterator first, InputIterator last );
		iterator	erase( iterator position );
		iterator	erase( iterator first, iterator last ) {		//? 

			while (first != last) {

				if (first == last)
					break;
				_alloc.destroy(first); //? first or *first ?
				++first;
				--_size;
			}
			return last;
		}
		void		swap( vector & x );
		void		clear( void );

		//	Allocator

		allocator_type		get_allocator( void ) const { return this->_alloc; }


	private:

		size_type			_capacity;		//* number of cells allocated
		size_type			_size;			//* number of cells filled
		// iterator
		pointer				_valueArray;	//* array of T
		allocator_type		_alloc;

		pointer				_start;
		pointer				_end;
	
		// _reallocate destroys everything to do a new allocation from scratch, it can construct the elements depending on boolean
		void		_reallocate( size_type new_size, bool construct ) {

			pointer		new_ptr = _alloc.allocate(new_size);

			for (size_type i = 0; i < _size; i++) {
				if (construct == true)
					_alloc.construct(new_ptr + i, _valueArray[i]);
				_alloc.destroy(_valueArray[i]);
			}
			_alloc.deallocate(_valueArray, _size);
			_valueArray = new_ptr;
			_size = n;
		}

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
