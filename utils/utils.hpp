#pragma once


#include <>

//*	enable_if structures
template<bool Cond, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };


