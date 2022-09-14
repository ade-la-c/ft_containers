#pragma once

#include <iostream>
#include <memory>
#include <limits>

#include "../utils/utils.hpp"
#include "../utils/random_access_iterator.hpp"
#include "../utils/reverse_iterator.hpp"

namespace	ft {


	template< class T, class Alloc = std::allocator<T> >
	class	vector {


	public:

		//	Type definers

		typedef T															value_type;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;

		typedef ft::random_access_iterator< value_type >						iterator;
		typedef ft::random_access_iterator< const value_type >				const_iterator;
		typedef ft::reverse_iterator< iterator >								reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >						const_reverse_iterator;

		typedef typename allocator_type::size_type														size_type;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;

		//	MEMBER FUNCTIONS	//

		//* default constructor
		explicit vector( const allocator_type & alloc = allocator_type() )
		: _capacity(0), _size(0), _alloc(alloc) {

			// std::cout<<"default constructor called"<<std::endl;//!debug

			this->_valueArray = this->_alloc.allocate(0, 0);
		}
		//* fill constructor
		explicit vector( size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type() )
		: _capacity(n), _size(n), _alloc(alloc) {
		
			// std::cout<<"fill constructor called"<<std::endl;//!debug

			this->_valueArray = this->_alloc.allocate(n, 0);
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(_valueArray + i, val);
			}
		}
		//* range constructor constructs with as many elements as the range (first, last)
		template< class InputIterator >
		vector( InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {

			// std::cout<<"range constructor called"<<std::endl;//!debug

			_size = ft::distance(first, last);
			_capacity = _size;
			_alloc = alloc;
			this->_valueArray = this->_alloc.allocate(_size, 0);

			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_valueArray + i, *(first + i));
			}
		}
		//* copy constructor
		vector( const vector & x ) : _capacity(x._capacity), _size(x._size), _alloc(x._alloc) {

			// std::cout<<"copy constructor called"<<std::endl;//!debug
			this->_valueArray = this->_alloc.allocate(0);
			// std::cerr<<"this capacity = "<<_capacity<<" "<<"rhs size = "<<x._size<<std::endl;//!debug
			*this = x;
		}
		//*	assignation operator
		vector &	operator=( const vector & rhs ) {

			// std::cout<<"assignation operator called"<<std::endl;//!debug
			// std::cerr<<"_size="<<_size<<" rhs._size="<<rhs._size<<std::endl;//!debug

			if (this != &rhs) {

				// std::cerr<<"----"<<std::endl;//!debug
				this->clear();
				this->_alloc.deallocate(this->_valueArray, this->_capacity);
				this->_valueArray = this->_alloc.allocate(rhs._capacity);
				for (size_type i = 0; i < rhs._size; i++) {

					// std::cerr<<"-_"<<"_valueArray["<<*(rhs._valueArray + i)<<"] (i="<<i<<")"<<std::endl;//!debug
					this->_alloc.construct(this->_valueArray + i, *(rhs._valueArray + i));
					// push_back(*(rhs._valueArray + i));
				}
				this->_size = rhs._size;
				this->_capacity = rhs._capacity;
			}

			return *this;
		}
		//*	destructor
		~vector( void ) {

			// std::cout<<"destructor called"<<std::endl;//!debug

			this->clear();
			if (this->_valueArray)
				this->_alloc.deallocate(this->_valueArray, this->_capacity);
		}

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
		reverse_iterator		rend( void ) { return reverse_iterator(this->begin()); }
		const_reverse_iterator	rend( void ) const { return const_reverse_iterator(this->begin()); }

		//	Capacity

		size_type		size( void ) const { return this->_size; }
		size_type		max_size( void ) const { return std::numeric_limits<size_type>::max(); }
		//*	Resizes the container so it contains n elements
		void			resize( size_type n, value_type val = value_type() ) {

			if (n <= _size) {

				while (_size != n) {
					pop_back();
				}
			} else if (n > _size) {

				while (_size != n) {
					push_back(val);
				}
			}
		}
		size_type		capacity( void ) const { return this->_capacity; }
		bool			empty( void ) const { return this->_size == 0 ? true : false; }
		//*	Requests that the vector capacity be at least enough to contain n elements.
		void			reserve( size_type n ) {
			// std::cout<<n<<std::endl;//!debug

			if (n > max_size()) {
				throw std::length_error("Vector reserve, input is bigger than max size.");
			}
			if (n <= _capacity) {
				return;
			}
			vector	tmp;

			// std::cerr<<"_capacity"<<_capacity<<std::endl;//!debug
			tmp = *this;
			clear();
			_alloc.deallocate(_valueArray, _capacity);
			_valueArray = _alloc.allocate(n);
			for (size_type i = 0; i < tmp._size; i++) {
				_alloc.construct(_valueArray + i, *(tmp._valueArray + i));
			}
			_size = tmp._size;
			_capacity = n;
		}

		//	Element access

		reference			operator[]( size_type n ) { return *(_valueArray + n); }
		const_reference		operator[]( size_type n ) const { return *(_valueArray + n); }
		reference			at( size_type n ) {

			if (n > _size) {
				throw std::out_of_range("Vector at.");
			}
			return *(this->_valueArray + n);
		}
		const_reference		at( size_type n ) const {

			if (n > _size)
				throw std::out_of_range("Vector const at.");
			return *(this->_valueArray + n);
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
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL ) {

			clear();
			for (;first < last; first++) {

				push_back(*first);
			}
		}
		void		assign( size_type n, const value_type & val ) {

			clear();
			for (size_type i = 0; i < n; ++i) {

				push_back(val);
			}
		}
		//*	Adds element at the end of the vector
		void		push_back( const value_type & val ) {

			if (_size + 1 >= _capacity) {

				if (_capacity == 0) {
					reserve(1);
				} else {
					reserve(_capacity * 2);
				}
			}
			_alloc.construct(_valueArray + _size, val);
			_size++;
		}
		void		pop_back( void ) {

			_alloc.destroy(_valueArray + (_size));
			_size--;
		}
		//*	The vector is extended by inserting new elements before the element at the specified position
		iterator	insert( iterator position, const value_type & val ) {			//* single element

			size_type	pos = position - this->begin() + 1;

			/*.
			reserve(++_size);
			for (size_type i = _size - 1; i; --i) {

				// std::cout<<"i : "<<i<<std::endl;//!debug
				if (i > pos) {
					_valueArray[i] = _valueArray[i - 1];
				} else if (i == pos) {
					_alloc.construct(_valueArray + i, val);
				}
			}
			return this->begin() + pos; //? -1 ou +1 ?
			// */

			reserve(_size + 1);
			++_size;
			size_type i = _size - 1;
			while (i > pos) {
				_valueArray[i] = _valueArray[i - 1];
				i--;
			}
			_valueArray[i] = val;
			return begin() + pos;

		}
		void		insert( iterator position, size_type n, const value_type & val ) {	//* fill
			/*.
			size_type	pos = position - this->begin() + 1;

			reserve(_size += n);
			for (size_type i = _size; i; --i) {

				if (i > pos + n) {
					_valueArray[i] = _valueArray[i - n];
				} else if (i >= pos) {std::cout<<"i "<<i;
					_alloc.construct(&(_valueArray[i]), val);
				}
			}
			// */

			iterator	it = position;
			for (size_type i = 0; i < n; ++i, ++it) {
				it = insert(it, val);
			}
		}
		template< class InputIterator > //* range
		void		insert( iterator position, InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {

			size_type	pos = position - this->begin() + 1;
			size_type	dist = ft::distance(first, last);

			reserve(_size += dist);
			for (size_type i = _size - 1; i && first != last; --i) {

				if (i > pos + dist) {
					_valueArray[i] = _valueArray[i - dist];
				} else if (i >= pos) {
					_alloc.construct(&(_valueArray[i]), *first);
					first++;
				}
			}
		}
		//*	Removes from the vector a single element (position).
		iterator	erase( iterator position ) {

			size_type	pos = position - this->begin() + 1;

			_alloc.destroy(_valueArray + pos);
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

			size_type	pos = ft::distance(first, last);
			size_type	dist = ft::distance(first, last);

			while (first != last) {
				_alloc.destroy(&(*first));
				first++;
			}
			for (size_type i = pos; i + dist < _size; i++) {
				_valueArray[i] = _valueArray[i + dist];
			}
			return this->begin() + pos + dist;		//?
		}
		//*	Exchanges the content of the container by the content of x, which is another vector object of the same type. Sizes may differ.
		void		swap( vector & x ) {

			size_type		cap;
			size_type		siz;
			pointer			values;
			allocator_type	allo;

			cap = this->_capacity;
			siz = this->_size;
			values = this->_valueArray;
			allo = this->_alloc;

			this->_capacity = x._capacity;
			this->_size = x._size;
			this->_valueArray = x._valueArray;
			this->_alloc = x._alloc;

			x._capacity = cap;
			x._size = siz;
			x._valueArray = values;
			x._alloc = allo;
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

		pointer				_valueArray;	//* array of T
		allocator_type		_alloc;


	};

	template < class T, class Alloc >
	bool	operator==( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs ) { return lhs == rhs; }
	template < class T, class Alloc >
	bool	operator!=( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs ) { return lhs != rhs; }
	template < class T, class Alloc >
	bool	operator<( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs ) { return lhs < rhs; }
	template < class T, class Alloc >
	bool	operator<=( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs ) { return lhs <= rhs; }
	template < class T, class Alloc >
	bool	operator>(const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs) { return lhs > rhs; }
	template < class T, class Alloc >
	bool	operator>=( const vector<T,Alloc> & lhs, const vector<T,Alloc> & rhs ) { return lhs >= rhs; }
	template< class T, class Alloc >
	void	swap( vector<T,Alloc> & x, vector<T,Alloc> & y ) { x.swap(y); }


}

	void	vector_testing( void );

