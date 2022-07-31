#pragma once

namespace ft { 					//?


	//* an input_iterator */
	struct	input_iterator_tag {};
	//* 	an output_iterator. */
	struct	output_iterator_tag {};
	//* a forward iterator */
	struct	forward_iterator_tag : public input_iterator_tag {};
	//* a bidirectional iterator */
	struct	bidirectional_iterator_tag : public forward_iterator_tag {};
	//* a random_access iterator */
	struct	random_access_iterator_tag : public bidirectional_iterator_tag {};

	//*	iterator_traits class defines properties of iterators
	template<class Iterator>
	struct	iterator_traits {

		//*	Type to express the result of subtracting one iterator from another.
		typedef typename Iterator::difference_type		difference_type;
		//*	The type of the element the iterator can point to.
		typedef typename Iterator::value_type			value_type;
		//*	The type of a pointer to an element the iterator can point to.
		typedef typename Iterator::pointer				pointer;
		//* The type of a reference to an element the iterator can point to.
		typedef typename Iterator::reference			reference;
		//*	The Iterator category
		typedef typename Iterator::iterator_category	iterator_category;

	};

	template<class T>
	struct	iterator_traits<T*> {

		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef ft::random_access_iterator_tag			iterator_category;
	};

	template<class T>
	struct	iterator_traits<const T*> {

		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef ft::random_access_iterator_tag			iterator_category;
	};



}
