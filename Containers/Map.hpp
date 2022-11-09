#pragma once

#include <iostream>
#include <limits>
#include <memory>
#include <iterator>
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
		class Compare = std::less< ft::pair< const Key, T> >,					//*	key_compare
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

		typedef typename	ft::pair<const key_type, mapped_type>					value_type;
		typedef	typename	std::size_t												size_type;
		typedef typename	std::ptrdiff_t											difference_type;
		typedef 			value_type &											reference;
		typedef 			const value_type &										const_reference;
		typedef typename	allocator_type::pointer									pointer;
		typedef typename	allocator_type::const_pointer							const_pointer;

		typedef				ft::reverse_iterator< value_type >						reverse_iterator;		   //???????
		typedef				ft::reverse_iterator< const value_type >				const_reverse_iterator;	  //???????
		typedef 			ft::bidirectional_iterator< value_type >				iterator;				 //???????
		typedef 			ft::bidirectional_iterator< const value_type >			const_iterator;			//???????

	private:

		typedef 			ft::RBTree< key_type, mapped_type >						Tree;
		typedef typename	allocator_type::template rebind<Tree>::other			tree_allocator;
		typedef typename	ft::Node<value_type> *									node_pointer;
		typedef typename	ft::Node<value_type>									node_type;


//	##    ## ########  ######  ######## ######## ########      ######  ##          ###     ######   ######
//	###   ## ##       ##    ##    ##    ##       ##     ##    ##    ## ##         ## ##   ##    ## ##    ##
//	####  ## ##       ##          ##    ##       ##     ##    ##       ##        ##   ##  ##       ##
//	## ## ## ######    ######     ##    ######   ##     ##    ##       ##       ##     ##  ######   ######
//	##  #### ##             ##    ##    ##       ##     ##    ##       ##       #########       ##       ##
//	##   ### ##       ##    ##    ##    ##       ##     ##    ##    ## ##       ##     ## ##    ## ##    ##
//	##    ## ########  ######     ##    ######## ########      ######  ######## ##     ##  ######   ######

	protected:

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

//	##     ## ######## ######## ##     ##  #######  ########   ######
//	###   ### ##          ##    ##     ## ##     ## ##     ## ##    ##
//	#### #### ##          ##    ##     ## ##     ## ##     ## ##
//	## ### ## ######      ##    ######### ##     ## ##     ##  ######
//	##     ## ##          ##    ##     ## ##     ## ##     ##       ##
//	##     ## ##          ##    ##     ## ##     ## ##     ## ##    ##
//	##     ## ########    ##    ##     ##  #######  ########   ######

	public:

		//*	empty
		explicit	map( const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() )
		: _size(0), _alloc(alloc), _treeAlloc(alloc), _comp(comp) {

			this->_rbt = _treeAlloc.allocate(1);
		}
		//*	range
		template <class InputIterator>
		map( InputIterator first, InputIterator last, const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() )
		: _size(0), _alloc(alloc), _treeAlloc(alloc), _comp(comp) {		//todo add kv_compare

			this->insert(first, last);
		}
		//*	copy
		map( const map & x ) { *this = x; }
		//*	assignation operator
		map &		operator=( const map & rhs ) {

			if (*this == rhs) {

				this->_size = rhs._size;
				this->_alloc = rhs._alloc;
				this->_treeAlloc = rhs._treeAlloc;

				this->_treeAlloc.destroy(this->_rbt);
				this->_treeAlloc.allocate(this->rbt, 1);
				this->insert(rhs.begin(), rhs.end());
				this->_comp = rhs._comp;
			}
			return *this;
		}
		//*	destructor
		~map( void ) {

			this->_treeAlloc.destroy(_rbt);
			this->_treeAlloc.deallocate(_rbt, 1);
		}

		//* iterators

		// iterator				begin( void );
		// const_iterator			begin( void ) const;
		// iterator				end( void );
		// const_iterator			end( void );
		// reverse_iterator		rbegin( void );
		// const_reverse_iterator	rbegin( void );
		// reverse_iterator		rend( void );
		// const_reverse_iterator	rend( void ) const;

		//* size

		bool			empty( void ) const { return !_size; }	//! allowed ?
		size_type		size( void ) const { return _size; }
		size_type		max_size( void ) const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

		//* element access

		mapped_type &	operator[]( const key_type & k ) {

			node_pointer	find = _rbt->search(k);

			if (!find) {
				//	insert new node
				find = _rbt->insertNode(ft::make_pair(k, mapped_type()));
				// _rbt->insertNode(ft::make_pair<key_type, mapped_type>(k, mapped_type()));
			}
			return find->data.second;
		}

		//* modifiers

		//*	single element

// /*

		ft::pair<iterator, bool>	insert( const value_type & val ) {

			ft::Node<value_type> *		ptr = _rbt->search(val.first);
			// ft::pair<iterator, bool>	ret = ft::make_pair<iterator, bool>(NULL, false);		//todo remove line if it works ;)

			if (!ptr) {
				ptr = _rbt->insertNode(val);
				return ft::pair<iterator, bool>(iterator(ptr, _rbt->getEnd()), true);			//?
			} else {
				return ft::pair<iterator, bool>(iterator(ptr, _rbt->getEnd()), false);
			}
		}
// */

/*	//!	insert v2 ?
		ft::pair<iterator, bool>	insert( const value_type & val ) {

			ft::Node<value_type> *		ptr = _rbt->search(val.first);
			ft::pair<iterator, bool>	ret = ft::make_pair(ptr, false);		//todo remove line if it works ;)

			if (!ptr) {
				// return ft::make_pair(_rbt->insertNode(val), true);			//?
				ret.first = iterator(_rbt->insertNode(val));
				ret.second = true;
			} else {
				ret.first = ptr;
				ret.second = false;
				// return ft::make_pair(ptr, false);
			}
			return ret;
		}
// */

/*

		//	with hint
		iterator					insert( iterator position, value_type & val ) {

			// value_type *	ptr = _rbt.search(val);

			std::cout << "position " << position << std::endl;
		}
		//	range
		template<class InputIterator>
		void						insert( InputIterator first, InputIterator last );
		void						erase( iterator position );
		size_type					erase( const key_compare & k );
		void						erase( iterator first, iterator last );
		void						swap( map & x );
		void						clear( void );

		//	observers

		key_compare				key_comp( void ) const;
		value_compare			value_comp( void ) const;

		//	operations

		iterator				find( const key_type & k );
		const_iterator			find( const key_type &k ) const;

		size_type				count( const key_type & k ) const;

		iterator				lower_bound( const key_type & k );
		const_iterator			lower_bound( const key_type & k ) const;

		iterator				upper_bound( const key_type & k );
		const_iterator			upper_bound( const key_type & k ) const;

		pair<const_iterator, const_iterator>	equal_range( const key_type & k );
		pair<iterator, iterator>				equal_range( const key_type & k );

		//	allocator

		allocator_type	get_allocator( void ) const { return _alloc; }

*/

	private:

		size_type					_size;
		allocator_type				_alloc;
		tree_allocator				_treeAlloc;
		Tree *						_rbt;
		key_compare					_comp;

	};



}
