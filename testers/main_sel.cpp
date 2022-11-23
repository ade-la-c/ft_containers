#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include <stack>
#include <list>
#include "../Containers/vector.hpp"
#include "../Containers/map.hpp"
#include "../Containers/stack.hpp"
// #include </Users/ade-la-c/Desktop/cont_namenega/map/map.hpp>
// #include </Users/ade-la-c/Desktop/cont_namenega/vector/vector.hpp>
// #include </Users/ade-la-c/Desktop/cont_namenega/stack/stack.hpp>
void test_vector();
void test_map();
void test_stack();

#ifndef FT
#define FT std
#endif

/*
** 531-m31c's tester for ft_containers
** Feel free to comment lines in main to test containers one by one
*/
int main()
{
test_vector();
test_map();
test_stack();
}

void test_stack()
{
	std::cout << "******STARTING TO TEST FT::STACK******" << std::endl;

std::cout << "----------TEST_CONSTRUCTORS-----------" << std::endl;
{
	  FT::vector<int> myvector (2,200);        // vector with 2 elements
  FT::stack<int> first;                    // empty stack
  FT::stack<int,FT::vector<int> > third;  // empty stack using vector
  FT::stack<int,FT::vector<int> > fourth (myvector);
  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';
}

std::cout << "----------TEST_SIZE-----------" << std::endl;
{
	  FT::stack<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<5; i++) myints.push(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.pop();
  std::cout << "2. size: " << myints.size() << '\n';

}

std::cout << "----------TEST_EMPTY-----------" << std::endl;
{
	FT::stack<int> mystack;
  int sum (0);

  for (int i=1;i<=10;i++) mystack.push(i);

  while (!mystack.empty())
  {
     sum += mystack.top();
     mystack.pop();
  }

  std::cout << "total: " << sum << '\n';

}

std::cout << "----------TEST_TOP-----------" << std::endl;
{ FT::stack<int> mystack;

  mystack.push(10);
  mystack.push(20);

  mystack.top() -= 5;

  std::cout << "mystack.top() is now " << mystack.top() << '\n';
}
std::cout << "----------TEST_PUSH_POP-----------" << std::endl;
{
	  FT::stack<int> mystack;

  for (int i=0; i<5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  while (!mystack.empty())
  {
     std::cout << ' ' << mystack.top();
     mystack.pop();
  }
  std::cout << '\n';

}

std::cout << "------------TEST_REL_OPERATOR--------" << std::endl;
{
  std::list<int> a;
  a.push_back(10);
  a.push_back(20);
  a.push_back(30);
  std::list<int> b;
  b.push_back(10);
  b.push_back(20);
  b.push_back(30);
  std::list<int> c;
  c.push_back(30);
  c.push_back(20);
  c.push_back(10);
	FT::stack<int, std::list<int> > d(a);
	FT::stack<int, std::list<int> > e(b);
	FT::stack<int, std::list<int> > f(c);
  if (d==e) std::cout << "a and b are equal\n";
  if (e!=f) std::cout << "b and c are not equal\n";
  if (e<f) std::cout << "b is less than c\n";
  if (f>e) std::cout << "c is greater than b\n";
  if (d<=e) std::cout << "a is less than or equal to b\n";
  if (d>=e) std::cout << "a is greater than or equal to b\n";
}

}


void test_map()
{
	std::cout << "******STARTING TO TEST FT::MAP******" << std::endl;
std::cout << "----------TEST_INSERT-----------" << std::endl;
{
	FT::map<char,int> mymap;

  // first insert function version (single parameter):
  mymap.insert ( FT::pair<char,int>('a',100) );
  mymap.insert ( FT::pair<char,int>('z',200) );

  FT::pair<FT::map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( FT::pair<char,int>('z',500) );
  if (ret.second==false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }
  FT::map<char, int>::iterator it = mymap.begin();
 mymap.insert (it, FT::pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, FT::pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  FT::map<char,int> anothermap;
  anothermap.insert(mymap.begin(), mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
 std::cout << "anothermap contains:\n";
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}

std::cout << "----------TEST_OPERATOR[]-----------" << std::endl;
{
  FT::map<char,std::string> mymap;

  mymap['a']="an element";
  mymap['b']="another element";
  mymap['c']=mymap['b'];

  std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  std::cout << "mymap now contains " << mymap.size() << " elements.\n";

}

std::cout << "----------TEST_SIZE-----------" << std::endl;
{  
	FT::map<char,int> mymap;
  mymap['a']=101;
  mymap['b']=202;
  mymap['c']=302;

  std::cout << "mymap.size() is " << mymap.size() << '\n';
  }
std::cout << "----------TEST_EMPTY-----------" << std::endl;
  {
	   FT::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  while (!mymap.empty())
  {
    std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
    mymap.erase(mymap.begin());
  }
  }
std::cout << "----------TEST_SWAP-----------" << std::endl;
 {
	   FT::map<char,int> foo,bar;

  foo['x']=100;
  foo['y']=200;

  bar['a']=11;
  bar['b']=22;
  bar['c']=33;

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (FT::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (FT::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

 }

std::cout << "----------TEST_ERASE-----------" << std::endl;
{  FT::map<char,int> mymap;
  FT::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  mymap.erase (it);                   // erasing by iterator

  mymap.erase ('c');                  // erasing by key

  it=mymap.find ('e');
  mymap.erase ( it, mymap.end() );    // erasing by range

  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}

std::cout << "----------TEST_KEY__COMP-----------" << std::endl;
{
	FT::map<char,int> mymap;

  FT::map<char,int>::key_compare mycomp = mymap.key_comp();

  mymap['a']=100;
  mymap['b']=200;
  mymap['c']=300;

  std::cout << "mymap contains:\n";

  char highest = mymap.rbegin()->first;     // key value of last element

  FT::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mycomp((*it++).first, highest) );

  std::cout << '\n';
  }
 
std::cout << "----------TEST_VALUE__COMP-----------" << std::endl;
 {
	  FT::map<char,int> mymap;

  mymap['x']=1001;
  mymap['y']=2002;
  mymap['z']=3003;

  std::cout << "mymap contains:\n";

  FT::pair<char,int> highest = *mymap.rbegin();          // last element

  FT::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );

 }
std::cout << "----------TEST_COUNT-----------" << std::endl;
 {
	   FT::map<char,int> mymap;
  char c;

  mymap ['a']=101;
  mymap ['c']=202;
  mymap ['f']=303;

  for (c='a'; c<'h'; c++)
  {
    std::cout << c;
    if (mymap.count(c)>0)
      std::cout << " is an element of mymap.\n";
    else 
      std::cout << " is not an element of mymap.\n";
  }
 }
std::cout << "----------TEST_LOWER__BOUND-----------" << std::endl;
{
	  FT::map<char,int> mymap;
  FT::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;


  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)
//   FT::map<char,int>::iterator s = itlow;
//   FT::map<char,int>::iterator e = itup;
//  for (; s != itup; s++)
//	std::cout << s->first << std::endl;
  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (FT::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}

std::cout << "----------TEST_EQUAL__RANGE-----------" << std::endl;
{
	 FT::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  FT::pair<FT::map<char,int>::iterator,FT::map<char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';

}
}

void test_vector()
{
	std::cout << "******STARTING TO TEST ft::VECTOR******" << std::endl;
std::cout << "----------TEST_CONSTRUCTORS-----------" << std::endl;
{
		  // constructors used in the same order as described above:
  FT::vector<int> first;                                // empty vector of ints
  FT::vector<int> second (4,100);                       // four ints with value 100
  FT::vector<int> third (second.begin(),second.end());  // iterating through second
  FT::vector<int> fourth (second);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};

  FT::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (FT::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
      std::cout << "The contents of second are:";
  for (FT::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
      std::cout << "The contents of third are:";
    for (FT::vector<int>::iterator it = third.begin(); it != third.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}
std::cout << "----------TEST_OPERATOR==-----------" << std::endl;
{
	  FT::vector<int> foo (3,0);
  FT::vector<int> bar (5,0);

  bar = foo;
  foo = FT::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

std::cout << "----------TEST_REND_RBEGIN-----------" << std::endl;
{
	  FT::vector<int> myvector (5);  // 5 default-constructed ints

  int i=0;

  FT::vector<int>::reverse_iterator rit = myvector.rbegin();
  for (; rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (FT::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}
std::cout << "----------TEST_SIZE-----------" << std::endl;
{  FT::vector<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<10; i++) myints.push_back(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert (myints.end(),10,100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.pop_back();
  std::cout << "3. size: " << myints.size() << '\n';
}


std::cout << "----------TEST_PUSH__BACK-----------" << std::endl;
{
  FT::vector<int> myvector;
 


  for (int i = 19; i <= 42; i++)
    myvector.push_back (i);

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
	std::cout << "vector contains:";
	for (FT::vector<int>::iterator it=myvector.begin(); it != myvector.end() ; it++)
		std::cout << " " << *it;
	std::cout << std::endl;
}

std::cout << "----------TEST_INSERT-----------" << std::endl;
{
  FT::vector<int> myvector (3,100);
  FT::vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );
  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  FT::vector<int> anothervector (2,400);
  myvector.insert(it+2,anothervector.begin(),anothervector.end());

FT::vector<int> vec;
vec.push_back(19);
vec.push_back(21);
vec.push_back(42);
  myvector.insert (myvector.begin(), vec.begin(), vec.end()-1);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

std::cout << "----------TEST_IT_OP[]_OP+_OP-_OP+=_OP-=()-----------" << std::endl;
{
	    FT::vector<int>v1;
		v1.push_back(1); 
		v1.push_back(2); 
		v1.push_back(3); 
		v1.push_back(4); 
		v1.push_back(5); 
    int i; 
  
	FT::vector<int>::iterator itx = v1.begin();
    for(i=0;i<5;++i) 
        std::cout << itx[i] << " "; 
	std::cout << std::endl;
	FT::vector<int>::iterator it = v1.begin() + 1;
	std::cout << it[-1] << std::endl;
	it = v1.end() - 1;
	std::cout << it[-1] << std::endl;
	it -= 4;
	std::cout << it[0] << std::endl;
	it += 2;
	std::cout << it[0] << std::endl;

}
std::cout << "----------TEST_SPECIAL---------" << std::endl;
{
FT::vector<int> lst;
lst.push_back(1);
lst.push_back(2);
lst.push_back(3);
FT::vector<int>::iterator it = lst.end();
lst.erase(--lst.end());
lst.insert(lst.end(), lst.begin(), (++lst.begin()));
lst.insert(--(--lst.end()), 19);
while (it != lst.begin())
	std::cout << *--it << std::endl;
}

std::cout << "----------TEST_RESIZE-----------" << std::endl;
{ 
	FT::vector<int> myvector;
  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (size_t i=0;i<myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}		
std::cout << "----------TEST_OP[]-----------" << std::endl;
{
	  FT::vector<int> myvector (10);   // 10 zero-initialized elements

  
  size_t sz = myvector.size();

  // assign some values:
  for (unsigned i=0; i<sz; i++) myvector[i]=i;

  // reverse vector using operator[]:
  for (unsigned i=0; i<sz/2; i++)
  {
    int temp;
    temp = myvector[sz-1-i];
    myvector[sz-1-i]=myvector[i];
    myvector[i]=temp;
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<sz; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}
std::cout << "----------TEST_EMPTY-----------" << std::endl;
{
	  FT::vector<int> myvector;
  int sum (0);

  for (int i=1;i<=10;i++) myvector.push_back(i);

  while (!myvector.empty())
  {
     sum += myvector.back();
     myvector.pop_back();
  }

  std::cout << "total: " << sum << '\n';
}
std::cout << "----------TEST_FRONT-----------" << std::endl;
{
	  FT::vector<int> myvector;

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';

}
std::cout << "----------TEST_RESERVE-----------" << std::endl;
{
  FT::vector<int> foo;
  foo.reserve(19);
  std::cout << foo.capacity() << std::endl;
  foo.reserve(42);
  std::cout << foo.capacity() << std::endl;
}
std::cout << "----------TEST_AT-----------" << std::endl;
{
FT::vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';
  
}
std::cout << "----------TEST_ASSIGN-----------" << std::endl;
{
  FT::vector<int> first;
  FT::vector<int> second;
  FT::vector<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  FT::vector<int>::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
}
std::cout << "----------TEST_SWAP-----------" << std::endl;
{
	FT::vector<int> foo (3,100);   // three ints with a value of 100
  FT::vector<int> bar (5,200);   // five ints with a value of 200

  foo.swap(bar);

  std::cout << "foo contains:";
  for (unsigned i=0; i<foo.size(); i++)
    std::cout << ' ' << foo[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i=0; i<bar.size(); i++)
    std::cout << ' ' << bar[i];
  std::cout << '\n';
}
std::cout << "----------TEST_NMO_REL_OP-----------" << std::endl;
{
	FT::vector<int> foo (3,100);   // three ints with a value of 100
  FT::vector<int> bar (2,200);   // two ints with a value of 200

  if (foo==bar) std::cout << "foo and bar are equal\n";
  if (foo!=bar) std::cout << "foo and bar are not equal\n";
  if (foo< bar) std::cout << "foo is less than bar\n";
  if (foo> bar) std::cout << "foo is greater than bar\n";
  if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
  if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";

}
std::cout << "----------TEST_NMO_SWAP-----------" << std::endl;
{
  FT::vector<int> foo (3,100);   // three ints with a value of 100
  FT::vector<int> bar (5,200);   // five ints with a value of 200

  foo.swap(bar);

  std::cout << "foo contains:";
  for (FT::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "bar contains:";
  for (FT::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}
}

