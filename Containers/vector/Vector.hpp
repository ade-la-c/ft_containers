#pragma once

#include <iostream>
#include <memory>
#include <limits>
#include <iterator>		//! must remove include

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
				push_back(*first);			//?
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

		//*	Returns an iterator pointing to the first element in the vector.
		iterator				begin( void ) { return iterator(this->_valueArray); }
		const_iterator			begin( void ) const { return const_iterator(this->_valueArray); }
		//*	Returns an iterator referring to the past-the-end element in the vector container.
		iterator				end( void ) { return iterator(this->_valueArray + this->_size); }
		const_iterator			end( void ) const { return const_iterator(this->_valueArray + this->_size); }
		//*	Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
		reverse_iterator		rbegin( void ) { return reverse_iterator(this->end()); }
		const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(this->end()); }
		//*	Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (reverse end).
		reverse_iterator		rend( void ) { return revese_iterator(this->begin()); }
		const_reverse_iterator	rend( void ) const { return const_reverse_iterator(this->begin()); }

		//	Capacity

		size_type		size( void ) const { return this->_size; }
		size_type		max_size( void ) const { return std::numeric_limits<size_type>::max(); }
		//*	Resizes the container so it contains n elements
		void			resize( size_type n, value_type val = value_type() ) {

			if (n < _size) {
				for (size_type i = n; i < _size; i++) {
					alloc.destroy(_valueArray[i]);
				}
			} else if (n > _size) {

				for (size_type i = _size; i < n; i++) {
					push_back(&val);
					_alloc.construct(_valueArray[i], val);
				}
			}
			_size = n;
		}
		size_type		capacity( void ) const { return this->_capacity; }
		bool			empty( void ) const { return this->_size == 0 ? true : false; }
		//*	Requests that the vector capacity be at least enough to contain n elements.
		void			reserve( size_type n ) {

			if (n > _capacity) {
				_reallocate(n, true);
			}
		}

		//	Element access

		reference			operator[]( size_type n ) { return *(_valueArray + n); }
		const_reference		operator[]( size_type n ) const { return *(_valueArray + n); }
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
		//*	Returns a reference to the first element in the vector.
		reference			front( void ) { return this->_valueArray[0]; }
		const_reference		front( void ) const { return this->_valueArray[0]; }
		//*	Returns a reference to the last element in the vector.
		reference			back( void ) { return this->_valueArray[_size - 1]; }
		const_reference		back( void ) const { return this->_valueArray[_size - 1]; }

		//	Modifiers

		//* Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		template< class InputIterator >	//* range
		void		assign( InputIterator first, InputIterator last ) {

/*
			clear();

			for (int i = 0; first != last; i++) {
				_alloc.construct(_valueArray[i], first++);
				size++;
			}
			_capacity = _size;
*/

		}
		void		assign( size_type n, const value_type & val ) {

			clear();

			for (size_type i = 0; i < n; i++) {
				_alloc.construct(_valueArray[i], val);
			}
			_size = n;
			_capacity = n;
		}
		void		push_back( const value_type & val ) {

			if (_size + 1 >= _capacity) {
				_reallocate(_capacity * 2, true);
			}
			_alloc.construct(_valueArray[_size], val);
			_size++;
			_capacity *= 2;
		}
		void		pop_back( void ) {

			_alloc.destroy(_valueArray[_size - 1]);
			_size--;
		}
		iterator	insert( iterator position, const value_type & val ) {			//* single element

			size_type		i;

			for (i = 0; i < _size; ++i) {
				if (_valueArray[i] == position) {
					reserve(++_size);
					break;
				}
			}
			for (size_type j = _size; j > i; j--) {	//? -1 +1 a tweak si nécessaire
				_valueArray[j] = _valueArray[j - 1];
			}
			_valueArray[i] = val;
			return position;	//?
		}
		void		insert( iterator position, size_type n, const value_type & val ) {	//* fill

			size_type		i;

			for (i = 0; i < _size; ++i) {
				if (_valueArray[i] == position) {
					_size += n;
					reserve(_size);
					break;
				}
			}
			for (size_type j = _size; j - 1 > i; j--) {	//? -1 +1 a tweak si nécessaire
				_valueArray[j] = _valueArray[j - 1];
			}
			while (i < _size) {
				_valueArray[i++] = val;
			}
		}
		template< class InputIterator > //* range
		void		insert( iterator position, InputIterator first, InputIterator last ) {

			size_type		i;
			InputIterator	tmp = first;

			for (i = 0; i < _size; ++i) {
				if (_valueArray[i] == position) {
					while (tmp != last && i < size) {// increasing capacity
						reserve(++_size);
						tmp++;
					}
					break;
				}
			}
			for (size_type j = _size; j - 1 > i; j--) {	//? -1 +1 a tweak si nécessaire
				_valueArray[j] = _valueArray[j - 1];
			}
			while (first != last) {					//? a tester
				_valueArray[i--] = last--;
			}
		}
		//*	Removes from the vector a single element (position).
		iterator	erase( iterator position ) {

			size_type	i;
			iterator	it;

			for (i = 0; i < _size; ++i) {
				if (_valueArray[i] == position) {	// position found
					_alloc.destroy(_valueArray[i]);	// position erased
					break;
				}
			}
			for (; i + 1 < _size; ++i) {
				_valueArray[i] = _valueArray[i + 1];	//	relink vextor
			}
			
			return it;
		}
		//*	Removes from the vector a range of elements (first - last).
		iterator	erase( iterator first, iterator last ) {		//? 

			while (first != last) {

				if (first == last)
					break;
				_alloc.destroy(first); //? first or *first ?
				++first;
				--_size;
			}
			if (++last)
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

		pointer				_start;			//TODO yet to initialize
		pointer				_end;			//TODO yet to initialize
	
		// _reallocate destroys everything to do a new allocation from scratch, it can construct the elements depending on boolean
		void		_reallocate( size_type new_size, bool construct ) {

			pointer		new_ptr = _alloc.allocate(new_size);

			for (size_type i = 0; i < _size; i++) {
				if (construct == true)
					_alloc.construct(new_ptr + i, _valueArray[i]);
				_alloc.destroy(_valueArray[i]);
				_alloc.deallocate(_valueArray[i], 1);
			}
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
