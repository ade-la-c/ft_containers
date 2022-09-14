#pragma once

#include <iostream>
#include <memory>
#include <limits>

#include "../utils/utils.hpp"
#include "../utils/random_access_iterator.hpp"
#include "../utils/reverse_iterator.hpp"

namespace	ft {


	template< class T, class Alloc = std::allocator<T> >
	class   vector {


	public:

		//	Type definers

		typedef T															value_type;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;

		typedef ft::random_access_iterator< value_type >					iterator;
		typedef ft::random_access_iterator< const value_type >				const_iterator;
		typedef ft::reverse_iterator< iterator >							reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >						const_reverse_iterator;

		typedef size_t														size_type;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;

		//	MEMBER FUNCTIONS	//

		//* default constructor
		explicit vector( const allocator_type & alloc = allocator_type() )
		: _capacity(0), _size(0), _alloc(alloc) {
		
			this->_valueArray = this->_alloc.allocate(0, 0);
		}
		//*	fill constructor
		explicit vector( size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type() )
		: _capacity(0), _size(0), _alloc(alloc) {

			this->_valueArray = this->_alloc.allocate(n, 0);
			for (size_type i = 0; i < n; i++) {
				_alloc.construct(_valueArray + i, val);
			}
		}
		//*	range constructor 
		template< class InputIterator >
		vector( InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
		typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type * = NULL ) {
			
			_size = ft::distance(first, last);
			_capacity = _size;
			_alloc = alloc;
			this->_valueArray = this->_alloc.allocate(_size, 0);

			for (size_type i = 0; i < _size; i++) {
				_alloc.construct(_valueArray + i, *(first + i));
			}
		}
		//*	copy constructor
		vector( const vector & x ) : _capacity(x._capacity), _size(x._size), _alloc(x._alloc) {

			this->_valueArray = this->_alloc.allocate(0);
			*this = x;
		}
		//*	assignation operator
		vector &	operator=( const vector & rhs ) {

			if (this != &rhs) {

				this->_capacity = rhs._capacity;
				this->_size = rhs._size;
				this->_alloc.deallocate(this->_valueArray, this->_capacity);
				this->_alloc = rhs._alloc;
				this->_valueArray = this->_alloc.allocate(rhs._capacity, 0);
				for (size_type i = 0; i < rhs._size; ++i) {

					this->_alloc.construct(this->_valueArray + i, rhs.at(i));
				}
			}
			return *this;
		}
		~vector( void ) {

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
		void			reserve( size_type n ) {

			if (n <= _capacity) {
				return;
			}
			if (n > max_size()) {
				throw std::length_error("Vector reserve, input is bigger than max size.");
			}
			pointer		tmp = _alloc.allocate(n);

			for (size_type i = 0; i < _size; ++i) {
				std::cout<<(tmp+i)<<" - "<<_valueArray + i<<" i: "<<i<<" size: "<<_size<<" cap: "<<_capacity<<" n: "<<n<<std::endl;//!debug
				_alloc.construct(tmp + i, _valueArray[i]);
			}
			_alloc.deallocate(_valueArray, _capacity);
			_capacity = n;
			_valueArray = tmp;
		}

		//	Element access

		reference			operator[]( size_type n ) { return *(_valueArray + n); }
		const_reference		operator[]( size_type n ) const { return *(_valueArray + n); }
		reference			at( size_type n ) {

			if (n >= _size) {
				throw std::out_of_range("Vector at.");
			}
			return *(this->_valueArray + n);
		}
		const_reference		at( size_type n ) const {

			if (n >= _size) {	
				throw std::out_of_range("Vector const at.");
			}
			return *(this->_valueArray + n);
		}
		reference			front( void ) { return this->_valueArray[0]; }
		const_reference		front( void ) const { return this->_valueArray[0]; }
		reference			back( void ) { return this->_valueArray[_size - 1]; }
		const_reference		back( void ) const { return this->_valueArray[_size - 1]; }

		//	Modifiers

		template < class InputIterator >
		void	assign(InputIterator first, InputIterator last,
		typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type * = NULL ) {
		
			clear();
			for (; first < last; ++first) {
				push_back(*first);
			}
		}
		void		assign( size_type n, const value_type & val ) {

			clear();
			for (size_type i = 0; i < n; ++i) {
				push_back(val);
			}
		}
		void		push_back( const value_type & val ) {

			if (_size + 1 >= _capacity) {
				if (!_capacity) {
					// std::cout<<"ee"<<std::endl;//!debug
					reserve(2);
					// std::cout<<"/ee"<<std::endl;//!debug
				} else {
					reserve(_capacity * 2);
				}
			}
			_size += 1;
			_alloc.construct(_valueArray + (_size - 1), val);
		}
		void		pop_back( void ) {

			if (_size) {
				_alloc.destroy(_valueArray + _size);
			}
			_size -= 1;
		}
		iterator	insert( iterator position, const value_type & val ) {

			size_type	pos = position - begin();
			size_type	i = _size;

			reserve(++_size);
			for (;i > pos; --i) {
				_valueArray[i] = _valueArray[i - 1];
			}
			_valueArray[i] = val;
			return begin() + pos;
		}
		void		insert( iterator position, size_type n, const value_type & val ) {

			iterator	it = position;
			for (size_type i = 0; i < n; ++i, ++it) {
				it = insert(it, val);
			}
		}
		template< class InputIterator >
		void		insert( iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator >::type * = NULL ) {

			for (; first != last; ++first) {

				position = insert(position, *first) + 1;
			}
		}
		iterator	erase( iterator position ) {

			size_type	pos = position - begin();
std::cout << position.base() << " - " << &_valueArray[pos] << std::endl;//! not yet tested (debug)
			_alloc.destroy(_valueArray + pos);
			for (size_type i = pos; i + 1 < _size; ++i) {
				_valueArray[i] = _valueArray[i + 1];
			}
			return position;
		}
		iterator	erase( iterator first, iterator last ) {

			iterator	it = first;
			for (; it != last; ++it) {

				erase(it);
			}
			return first;//! not sure ab this function
		}
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
		void		clear( void ) {

			while (_size) {
				pop_back();
			}
		}

		//	Allocator

		allocator_type	get_allocator( void ) const { return this->_alloc; }

		void	print_vector( std::string str ) const {		//!debug function

			std::cout << str << ":" << std::endl;
			for (size_type i = 0; i < _size; ++i) {

				std::cout << _valueArray[i] << " " << std::flush;
			}
			std::cout<<std::endl<<std::endl;;
		}

	private:

		size_type			_capacity;		//* number of cells allocated
		size_type			_size;			//* number of cells filled

		pointer				_valueArray;	//* array of T
		allocator_type		_alloc;			//*	allocator

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
