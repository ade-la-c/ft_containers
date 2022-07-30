#pragma once

#include <iostream>
#include <memory>
#include <limits>
// #include <iterator>//!  <<<================ must remove include

#include "../utils/utils.hpp"
#include "../utils/random_access_iterator.hpp"

namespace	ft {


	template< class T, class Alloc = std::allocator<T> >
	class	vector {


	public:

		//	Type definers

		typedef T														value_type;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;

		typedef ft::random_access_iterator<value_type>					iterator;
		typedef ft::random_access_iterator<const value_type>			const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename allocator_type::size_type						size_type;
		typedef typename ft::iterator_traits::difference_type			difference_type;

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
		vector &	operator=( const vector & rhs ) {					//?

			if (this != &rhs) {
				this->_capacity = rhs._capacity;
				this->_size = rhs._size;
				this->_alloc.allocate(rhs._capacity);					//?	not sure ab this line
				for (int i = 0; i < this->_size; i++)
					this->_valueArray[i] = rhs._valueArray[i];
			}
			return *this;
		}
		~vector( void ) {

			clear();
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

				for (size_type i = _size - n; n > 0; n--) {
					pop_back();
				}
			} else if (n > _size) {

				for (size_type i = _size; i < n; i++) {
					push_back(&val);
				}
			}
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
		void		assign( InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr ) {

			clear();
			for (first < last; first++) {

				push_back(first);
			}
		}
		void		assign( size_type n, const value_type & val ) {

			clear();

			while (n--) {

				push_back(val);
			}
		}
		//*	Adds element at the end of the vector
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
		//*	The vector is extended by inserting new elements before the element at the specified position
		iterator	insert( iterator position, const value_type & val ) {			//* single element

			size_type	pos = position - this->begin() + 1;

			reserve(++_size);
			for (size_type i = _size; i; --i) {

				if (i > pos) {
					_valueArray[i] = _valueArray[i - 1];
				} else if (i == pos) {
					_alloc.construct(&(_valueArray[i]), val);
				}
			}
			return this->begin()[pos]; //? -1 ou +1 ?
		}
		void		insert( iterator position, size_type n, const value_type & val ) {	//* fill

			size_type	pos = position - this->begin() + 1;

			reserve(_size += n);
			for (size_type i = _size; i; --i) {

				if (i > pos + n) {
					_valueArray[i] = _valueArray[i - n];
				} else if (i >= pos) {
					_alloc.construct(&(_valueArray[i]), val);
				}
			}
		}
		template< class InputIterator > //* range
		void		insert( iterator position, InputIterator first, InputIterator last
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) {

			size_type	pos = position - this->begin() + 1;
			size_type	dist = ft::distance(first, last);

			reserve(_size += dist);
			for (siez_type i = _size; i && first != last; --i) {

				if (i > pos + dist) {
					_valueArray[i] = _valueArray[i - dist];
				} else if (i >= pos) {
					_alloc.construct(&(_valueArray[i]), &first++);
				}
			}
		}
		//*	Removes from the vector a single element (position).
		iterator	erase( iterator position ) {

/*.
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
// */

			size_type	pos = position - this->begin() + 1;

			_alloc.destroy(_valueArray[pos]);
			for (size_type i = pos; i + 1 < _size; ++i) {
				_valueArray[i] = _valueArray[i + 1];
			}
			return this->begin() + pos;
		}
		//*	Removes from the vector a range of elements (first - last).
		iterator	erase( iterator first, iterator last ) {		//? 

/**
			while (first != last) {

				if (first == last)
					break;
				_alloc.destroy(first); //? first or *first ?
				++first;
				--_size;
			}
			if (++last)
			return last;
*/

			size_type	pos = position - this->begin() + 1;
			size_type	dist = distance(first, last);

			while (first != last) {
				_alloc.destroy(first++);
			}
			for (size_type i = pos; i + dist < _size; i++) {
				_valueArray[i] = _valueArray[i + dist];
			}
			return this->begin() + pos + dist;		//?
		}
		//*	Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
		void		swap( vector & x ) {

			vector	tmp;

			tmp.reserve(this->_capacity);
			tmp._valueArray = this->_valueArray;
			tmp._size = this->_size;
			tmp._capacity = this->_capacity;

			this->reserve(x.capacity);
			this->_valueArray = x._valueArray;
			this->_size = x._size;
			this->_capacity = x._capacity;

			x.reserve(tmp._capacity);
			x._valueArray = tmp._valueArray;
			x._size = tmp._size;
			x._capacity = tmp._capacity;
		}
		//*	Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
		void		clear( void ) {

			while (_size) {
				pop_back();
			}
		}

		//	Allocator

		allocator_type		get_allocator( void ) const { return this->_alloc; }


	private:

		size_type			_capacity;		//* number of cells allocated
		size_type			_size;			//* number of cells filled
		// iterator
		pointer				_valueArray;	//* array of T
		allocator_type		_alloc;

		// pointer				_start;			//TODO yet to initialize
		// pointer				_end;			//TODO yet to initialize
	
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
	bool	operator==( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs )
	{ return lhs == rhs; }
	template < class T, class Alloc >
	bool	operator!=( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs )
	{ return lhs != rhs; }
	template < class T, class Alloc >
	bool	operator<( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs )
	{ return lhs < rhs; }
	template < class T, class Alloc >
	bool	operator<=( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs )
	{ return lhs <= rhs; }
	template < class T, class Alloc >
	bool	operator>(const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs)
	{ return lhs > rhs; }
	template < class T, class Alloc >
	bool	operator>=( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs )
	{ return lhs >= rhs; }
	template< class T, class Alloc >
	void	swap( vector<T,Alloc> & x, vector<T,Alloc> & y ) { x.swap(y); }

}
