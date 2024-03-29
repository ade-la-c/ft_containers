#pragma once

#include <iostream>
#include <limits>
#include <memory>
#include <functional>

#include "../utils/utils.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/rbt_n.hpp"
#include "../utils/pair.hpp"
#include "../utils/bidirectional_iterator.hpp"

namespace	ft {


	template <

		class Key,																//*	key_type
		class T,																//*	mapped_type
		class Compare = std::less< Key >,										//*	key_compare
		class Allocator = std::allocator< ft::pair< const Key, T > >			//*	allocator_type

	> class map {


//	########  ######## ######## #### ##    ## ######## ########   ######
//	##     ## ##       ##        ##  ###   ## ##       ##     ## ##    ##
//	##     ## ##       ##        ##  ####  ## ##       ##     ## ##
//	##     ## ######   ######    ##  ## ## ## ######   ########   ######
//	##     ## ##       ##        ##  ##  #### ##       ##   ##         ##
//	##     ## ##       ##        ##  ##   ### ##       ##    ##  ##    ##
//	########  ######## ##       #### ##    ## ######## ##     ##  ######



		public:

			typedef				T														mapped_type;		//*	DEFINITION
			typedef				Key														key_type;			//*	KEY
			typedef				Allocator												allocator_type;
			typedef				Compare													key_compare;

			typedef typename	ft::pair< const key_type, mapped_type >					value_type;
			typedef	typename	std::size_t												size_type;
			typedef typename	std::ptrdiff_t											difference_type;
			typedef 			value_type &											reference;
			typedef 			const value_type &										const_reference;
			typedef typename	allocator_type::pointer									pointer;
			typedef typename	allocator_type::const_pointer							const_pointer;

			typedef 			ft::bidirectional_iterator< value_type >				iterator;
			typedef 			ft::bidirectional_iterator< const value_type >			const_iterator;
			typedef				ft::reverse_iterator< iterator >						reverse_iterator;
			typedef				ft::reverse_iterator< const_iterator >					const_reverse_iterator;

		private:

			typedef 			ft::RBTree< key_type, mapped_type, key_compare >		Tree;
			typedef typename	ft::Node< value_type > *								node_pointer;
			typedef typename	ft::Node< value_type >									node_type;


//	##    ## ########  ######  ######## ######## ########      ######  ##          ###     ######   ######
//	###   ## ##       ##    ##    ##    ##       ##     ##    ##    ## ##         ## ##   ##    ## ##    ##
//	####  ## ##       ##          ##    ##       ##     ##    ##       ##        ##   ##  ##       ##
//	## ## ## ######    ######     ##    ######   ##     ##    ##       ##       ##     ##  ######   ######
//	##  #### ##             ##    ##    ##       ##     ##    ##       ##       #########       ##       ##
//	##   ### ##       ##    ##    ##    ##       ##     ##    ##    ## ##       ##     ## ##    ## ##    ##
//	##    ## ########  ######     ##    ######## ########      ######  ######## ##     ##  ######   ######

		public:

			class	value_compare : public std::binary_function< value_type, key_type, bool > {
				friend class	map< key_type, mapped_type, key_compare, allocator_type >;

				public:

					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					typedef bool		result_type;

					bool	operator() ( const value_type & x, const value_type & y ) const { return comp(x.first, y.first); }

				protected:

					Compare				comp;

					value_compare( Compare c ) : comp(c) {}

			};


//  ######   #######  ##    ##  ######  ######## ########  ##     ##  ######  ########  #######  ########   ######
// ##    ## ##     ## ###   ## ##    ##    ##    ##     ## ##     ## ##    ##    ##    ##     ## ##     ## ##    ##
// ##       ##     ## ####  ## ##          ##    ##     ## ##     ## ##          ##    ##     ## ##     ## ##
// ##       ##     ## ## ## ##  ######     ##    ########  ##     ## ##          ##    ##     ## ########   ######
// ##       ##     ## ##  ####       ##    ##    ##   ##   ##     ## ##          ##    ##     ## ##   ##         ##
// ##    ## ##     ## ##   ### ##    ##    ##    ##    ##  ##     ## ##    ##    ##    ##     ## ##    ##  ##    ##
//  ######   #######  ##    ##  ######     ##    ##     ##  #######   ######     ##     #######  ##     ##  ######

		public:

			//*	empty
			explicit	map( const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() )
			: _alloc(alloc), _rbt(comp), _comp(comp) {
			}
			//*	range
			template <class InputIterator>
			map( InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() )
			: _alloc(alloc), _rbt(comp), _comp(comp) {
				this->insert(first, last);
			}
			//*	copy
			map( const map & x ) { *this = x; }
			//*	assignation operator
			map &		operator=( const map & rhs ) {

				if (this != &rhs) {

					this->clear();
					this->insert(rhs.begin(), rhs.end());
					this->_alloc = rhs._alloc;
					this->_comp = rhs._comp;
				}
				return *this;
			}
			//*	destructor
			~map( void ) {

				_rbt.clear(_rbt.getRoot());
			}

// #### ######## ######## ########     ###    ########  #######  ########   ######
//  ##     ##    ##       ##     ##   ## ##      ##    ##     ## ##     ## ##    ##
//  ##     ##    ##       ##     ##  ##   ##     ##    ##     ## ##     ## ##
//  ##     ##    ######   ########  ##     ##    ##    ##     ## ########   ######
//  ##     ##    ##       ##   ##   #########    ##    ##     ## ##   ##         ##
//  ##     ##    ##       ##    ##  ##     ##    ##    ##     ## ##    ##  ##    ##
// ####    ##    ######## ##     ## ##     ##    ##     #######  ##     ##  ######


			iterator				begin( void ) { return iterator(_rbt.firstNode(), _rbt.getEnd()); }
			// const_iterator			begin( void ) const { return iterator(_rbt.firstNode(), _rbt.getEnd()); }
			const_iterator			begin( void ) const { return static_cast<const_iterator>(iterator(_rbt.firstNode(), _rbt.getEnd())); }
			iterator				end( void ) { return iterator(_rbt.getEnd(), _rbt.getEnd()); }
			// const_iterator			end( void ) const { return iterator(_rbt.getEnd(), _rbt.getEnd()); }
			const_iterator			end( void ) const { return static_cast<const_iterator>(iterator(_rbt.getEnd(), _rbt.getEnd())); }
			reverse_iterator		rbegin( void ) { return reverse_iterator(iterator(_rbt.getEnd(), _rbt.getEnd())); }
			const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(iterator(_rbt.getEnd(), _rbt.getEnd())); }
			reverse_iterator		rend( void ) { return reverse_iterator(begin()); }
			const_reverse_iterator	rend( void ) const { return const_reverse_iterator(begin()); }


//  ######  #### ######## ########
// ##    ##  ##       ##  ##
// ##        ##      ##   ##
//  ######   ##     ##    ######
//       ##  ##    ##     ##
// ##    ##  ##   ##      ##
//  ######  #### ######## ########


			bool			empty( void ) const { return !(_rbt.getSize()); }
			size_type		size( void ) const { return _rbt.getSize(); }
			size_type		max_size( void ) const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }


// ######## ##       ######## ##     ## ######## ##    ## ########       ###     ######   ######  ########  ######   ######
// ##       ##       ##       ###   ### ##       ###   ##    ##         ## ##   ##    ## ##    ## ##       ##    ## ##    ##
// ##       ##       ##       #### #### ##       ####  ##    ##        ##   ##  ##       ##       ##       ##       ##
// ######   ##       ######   ## ### ## ######   ## ## ##    ##       ##     ## ##       ##       ######    ######   ######
// ##       ##       ##       ##     ## ##       ##  ####    ##       ######### ##       ##       ##             ##       ##
// ##       ##       ##       ##     ## ##       ##   ###    ##       ##     ## ##    ## ##    ## ##       ##    ## ##    ##
// ######## ######## ######## ##     ## ######## ##    ##    ##       ##     ##  ######   ######  ########  ######   ######


			mapped_type &	operator[]( const key_type & k ) {

				node_pointer	find = _rbt.search(k);

				if (!find) {

					find = _rbt.insertNode(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
				}
				return find->data.second;
			}

// ##     ##  #######  ########  #### ######## #### ######## ########   ######
// ###   ### ##     ## ##     ##  ##  ##        ##  ##       ##     ## ##    ##
// #### #### ##     ## ##     ##  ##  ##        ##  ##       ##     ## ##
// ## ### ## ##     ## ##     ##  ##  ######    ##  ######   ########   ######
// ##     ## ##     ## ##     ##  ##  ##        ##  ##       ##   ##         ##
// ##     ## ##     ## ##     ##  ##  ##        ##  ##       ##    ##  ##    ##
// ##     ##  #######  ########  #### ##       #### ######## ##     ##  ######

			//	single element
			ft::pair<iterator, bool>	insert( const value_type & val ) {

				node_pointer				ptr = _rbt.search(val.first);
				ft::pair<iterator, bool>	ret = ft::make_pair(iterator(ptr, _rbt.getEnd()), false);

				if (!ptr) {
					// return ft::make_pair(_rbt.insertNode(val), true);			//?
					ret.first = iterator(_rbt.insertNode(val), _rbt.getEnd());
					ret.second = true;
				}
				return ret;
			}
			//	with hint
			iterator			insert( iterator position, const value_type & val ) {

				node_pointer		ptr = _rbt.search(val.first);

				(void)position;
				if (!ptr) {

					ptr = _rbt.insertNode(val);
				}
				return iterator(ptr, _rbt.getEnd());
			}
			//	range
			template<class InputIterator>
			void				insert( InputIterator first, InputIterator last ) {
				while (first != last) {
					_rbt.insertNode(*first);
					first++;
				}
			}
			void				erase( iterator position ) {

				value_type		val = position.base()->data;
				node_pointer	ptr = _rbt.search(val.first);

				// _rbt.deleteNode(ptr, val.first);
				if (ptr) {
					erase(val.first);
				}
			}
			size_type			erase( const key_type & k ) {

				return _rbt.deleteNode(_rbt.getRoot(), k);
			}
			void				erase( iterator first, iterator last ) {

				while (first != last ) {

					erase(first++);
				}
			}
			void				swap( map & x ) {

				_rbt.swap(x._rbt);
			}
			void				clear( void ) {

				erase(begin(), end());
			}

//	 #######  ########   ######  ######## ########  ##     ## ######## ########   ######
//	##     ## ##     ## ##    ## ##       ##     ## ##     ## ##       ##     ## ##    ##
//	##     ## ##     ## ##       ##       ##     ## ##     ## ##       ##     ## ##
//	##     ## ########   ######  ######   ########  ##     ## ######   ########   ######
//	##     ## ##     ##       ## ##       ##   ##    ##   ##  ##       ##   ##         ##
//	##     ## ##     ## ##    ## ##       ##    ##    ## ##   ##       ##    ##  ##    ##
//	 #######  ########   ######  ######## ##     ##    ###    ######## ##     ##  ######


			key_compare			key_comp( void ) const { return _comp; }
			value_compare		value_comp( void ) const { return value_compare(key_compare()); }

			//	operations

			iterator			find( const key_type & k ) {

				node_pointer	ptr = _rbt.search(k);

				if (!ptr) {
					return end();
				} else {
					return iterator(ptr, _rbt.getEnd());
				}
			}
			const_iterator		find( const key_type & k ) const {

				node_pointer	ptr = _rbt.search(k);

				if (!ptr) {
					return end();
				} else {
					return iterator(ptr, _rbt.getEnd());
				}
			}
			size_type			count( const key_type & k ) const {

				return !(!(_rbt.search(k)));
				// return _rbt.search(k) == NULL ? 0 : 1;	//* equivalent
			}
			iterator			lower_bound( const key_type & k ) {

				iterator	it = begin();

				while (it != end()) {
					if (_comp(it->first, k) == false)
						break ;
					it++;
				}
				return it;
			}
			const_iterator		lower_bound( const key_type & k ) const {

				const_iterator	it = begin();

				while (it != end()) {
					if (_comp(it->first, k) == false)
						break ;
					it++;
				}
				return it;
			}
			iterator			upper_bound( const key_type & k ) {

				iterator	it = begin();

				while (it != end()) {
					if (_comp(k, it->first) == true)
						break ;
					it++;
				}
				return it;
			}
			const_iterator		upper_bound( const key_type & k ) const {

				const_iterator	it = begin();

				while (it != end()) {
					if (_comp(k, it->first) == true)
						break ;
					it++;
				}
				return it;
			}

			ft::pair<const_iterator, const_iterator>	equal_range( const key_type & k ) const {

				return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			}
			pair<iterator, iterator>					equal_range( const key_type & k ) {

				return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}


//	   ###    ##       ##        #######   ######     ###    ########  #######  ########
//	  ## ##   ##       ##       ##     ## ##    ##   ## ##      ##    ##     ## ##     ##
//	 ##   ##  ##       ##       ##     ## ##        ##   ##     ##    ##     ## ##     ##
//	##     ## ##       ##       ##     ## ##       ##     ##    ##    ##     ## ########
//	######### ##       ##       ##     ## ##       #########    ##    ##     ## ##   ##
//	##     ## ##       ##       ##     ## ##    ## ##     ##    ##    ##     ## ##    ##
//	##     ## ######## ########  #######   ######  ##     ##    ##     #######  ##     ##


			allocator_type	get_allocator( void ) const { return _alloc; }


		private:

			allocator_type				_alloc;
			Tree						_rbt;
			key_compare					_comp;

	};

	template< class Key, class T, class Compare, class Alloc >
	bool	operator==( const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs )
	{ return lhs.size() == rhs.size(); }

	template< class Key, class T, class Compare, class Alloc >
	bool	operator!=( const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs )
	{ return !(lhs.size() == rhs.size()); }

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<( const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs )
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<=( const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs )
	{ return !(rhs < lhs); }

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>( const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs )
	{ return rhs < lhs; }

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>=( const map< Key, T, Compare, Alloc >& lhs,
						const map< Key, T, Compare, Alloc >& rhs )
	{ return !(lhs < rhs); }

	template< class Key, class T, class Compare, class Alloc >
	void	swap( map< Key, T, Compare, Alloc >& lhs,
					map< Key, T, Compare, Alloc >& rhs )
	{ lhs.swap(rhs); }


}
