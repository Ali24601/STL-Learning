// vector_demo_vc6.cpp : Defines the entry point for the console application.
//
// This demo will illustrate how to use the std::vector container.


// using pre-compiled header
//#include "stdafx.h"

// include the proper STL header files 
// we will need for the demo
#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <vector>
#include <tchar.h>

// declare the std namespace at file scope
// for the STL classes we will use in this 
// implementation
using std::cout;            // from <iostream>
using std::exception;       // from <exception>
using std::for_each;        // from <algorithm>
using std::remove_if;       // from <algorithm>
using std::unary_function;  // from <functional>
using std::vector;          // from <vector>

							// declare any constants
const static int NUMBER_OF_WIDGETS = 10;
const static int NUMBER_TO_RESERVE = 1000;

// declare a demo widget class
class Widget
{
public:
	Widget(const int& ID) { m_ID = ID; }
	const int& GetID() { return m_ID; }
	const int& GetCode() { return m_iCode; }

	void SetCode(const int& iCode) { m_iCode = iCode; }

	// declare a function object to use as a 
	// predicate for remove_if().
	class WidgetCodeIs :
		public unary_function<Widget, bool>
	{
	public:
		WidgetCodeIs(const int& value) : m_value(value) {}

		bool operator()(Widget& w) const
		{
			return (w.GetCode() == m_value);
		}

	private:
		int m_value;
	};

	// declare a function object to set a Widget code
	class SetWidgetCodeTo :
		public unary_function<Widget, void>
	{
	public:
		SetWidgetCodeTo(const int& value) : m_value(value) {}

		void operator()(Widget& w) const
		{
			w.SetCode(m_value);
		}

	private:
		int m_value;
	};

private:
	int m_ID;
	int m_iCode;

}; // end demo Widget class



   // our demo app entry point
int _tmain(int /*argc*/, _TCHAR* /*argv[]*/)
{

	cout << "Create a vector to hold Widgets...\n";

	// The first thing we will do is declare a vector
	// to hold Widgets.  There are several ways to construct
	// a vector.  Here are some of the most common:
	//
	// create a vector to hold 500 Widgets:
	//
	//     vector<Widget> vWidgets(500);
	//
	// create a vector to hold 500 Widgets initialized to 0:
	//
	//     vector<Widget> vWidgets(500, Widget(0));
	//
	// create a vector of Widgets from another vector of Widgets
	//
	//     vector<Widget> vWidgetsFromAnother(vWidgets);


	// in this example we will first create an empty vector of Widgets:	

	vector<Widget> vWidgets;
	//     ------
	//      |
	//      |- Since vector is a container, it's member functions
	//         operate on iterators and the container itself so
	//         it can hold objects of any type.

	cout << "Reserve space for " << NUMBER_TO_RESERVE << " Widgets...\n";

	// Sometimes it may be necessary to allocate
	// some space for your vector up front if you know 
	// that a large number of push_back()s may be comming.
	// This may eliminate the need for more memory allocations.
	// To do this, we call reserve()
	vWidgets.reserve(NUMBER_TO_RESERVE);

	int i = 0;

	cout << "Add " << NUMBER_OF_WIDGETS << " Widgets to the vector...\n";

	// The most common member function of the vector is push_back().  This
	// function is responsible for adding an element to the end of
	// the vector and allocating memory as needed.

	for (i = 0; i<NUMBER_OF_WIDGETS; ++i)
	{
		vWidgets.push_back(Widget(i));

		// Sometimes it may be useful to perform an operation
		// on the new element right away.  In this case, the
		// back() member function is useful.  back() returns
		// a reference to the last element in the vector.  Here
		// we will use back() to call SetCode() on our alloated
		// Widget.

		vWidgets.back().SetCode(i % 4);
	}

	// Another useful member of vector is size().  size() returns
	// the number of elements in the vector.  It is sometimes
	// useful to cast the size_type returned by size() to type int
	// if you intend to use it for comparison and arithmatic operations.
	// This will eliminate level 4 comparison warnings.

	int nWidgets = static_cast<int>(vWidgets.size());

	cout << nWidgets << " widgets created.\n";
	cout << "Widget capacity: " << static_cast<int>(vWidgets.capacity()) << "\n\n";

	// The next obvious thing one would want to do is to get
	// at the objects in the vector.  This can be accomplished
	// in two ways.  
	//               1. operator[]
	//               2. at()
	//
	// The operator[] is supported mainly for compatibility with 
	// a legacy C code base.  It operates the same way a standard
	// C-style array [] works.  It is always preferred to use 
	// the at() member function however, as at() is bounds-checked
	// and will throw an exception if we attempt to access a location
	// beyond the vector limits.  operator[] could care less and 
	// can cause some serious bugs as we will now demonstrate.

	cout << "List vector contents:\n";

	for (i = 0; i < nWidgets; ++i)
		//        --
		//        |- uh-oh!  A novice coder mistakenly put '<=' for
		//           comparison instead of '<'.  Let's see what happens...
	{
		try
		{
			cout << "vWidgets[" << i << "].GetCode(): " << vWidgets[i].GetCode() << "\t\t";
			cout << "vWidgets.at(" << i << ").GetCode(): " << vWidgets.at(i).GetCode() << "\n";
		}

		// Remember, exceptions are a good thing. If i is 
		// out of bounds, at() will throw an exception.

		catch (const exception& e)
		{
			// Here we can handle the exception.  In this
			// case, we will simplify notify the user of his
			// error via cout.
			cout << "\n\nException caught!\n  details: " << e.what()
				<< "\n     line: " << __LINE__
				<< "\n     file: " << __FILE__;
		}
	}

	// OK, here is where we will start to get into some fun stuff.
	// Say now that we want to get rid of all the Widgets whose 
	// code == 2.  To do this, we will employ the remove_if() algorithm
	// paired with our function object as a predicate.  
	// 
	// <aside>
	//   I don't intend to get all into the design and implementation of 
	//   predicates in this example, but I do feel it's worth an honorable 
	//   mention.  In the case of remove_if(), the predicate is a 
	//   function object derived from unary_function<Widget, bool>.  This
	//   means that the object takes a Widget as an argument and returns 
	//   a bool.  The Widget is passed through a dereferenced iterator via 
	//   remove_if() as it operates on the specified iterative range (in this 
	//   case from begin() to end(), i.e.  all vector elements).  If the 
	//   predicate evaluates to true, the element is "removed", otherwise it 
	//   stays.
	// </aside>
	//
	// As explained in the article, it is important to remember that 
	// remove_if() operates on a range of iterators and not on the 
	// container itself.  Thus we call erase() to actually get rid of the
	// "removed" elements.

	vWidgets.erase(
		remove_if(vWidgets.begin(), vWidgets.end(), Widget::WidgetCodeIs(2)),
		vWidgets.end());

	nWidgets = static_cast<int>(vWidgets.size());

	cout << "\n\nList vector contents after remove:\n";

	for (i = 0; i<nWidgets; ++i)
	{
		try
		{
			cout << "vWidgets.at(" << i << ").GetCode(): " << vWidgets.at(i).GetCode() << "\n";
		}

		catch (const exception& e)
		{
			cout << "\n\nException caught!\n  details: " << e.what()
				<< "\n     line: " << __LINE__
				<< "\n     file: " << __FILE__;
		}
	}

	// Now say that we want another vector with 3 elements to insert
	// before the 4th element in vWidgets.  To do this we first create 
	// a new vector...

	vector<Widget> vInsert(3, Widget(1111));

	// Consider now that we want to assign a code of 9999 to each element.
	// In this case it is preferable to use the for_each() algorithm.  for_each()
	// takes a range of iterators and applies the specified function pointer
	// to each one.  
	for_each(vInsert.begin(), vInsert.end(), Widget::SetWidgetCodeTo(9999));

	// Now we insert our vector into the existing one at the specified location
	// using insert().
	vWidgets.insert(vWidgets.begin() + 3, vInsert.begin(), vInsert.end());

	nWidgets = static_cast<int>(vWidgets.size());

	cout << "\n\nList vector contents after insert:\n";

	for (i = 0; i<nWidgets; ++i)
	{
		try
		{
			cout << "vWidgets.at(" << i << ").GetCode(): " << vWidgets.at(i).GetCode() << "\n";
		}

		catch (const exception& e)
		{
			cout << "\n\nException caught!\n  details: " << e.what()
				<< "\n     line: " << __LINE__
				<< "\n     file: " << __FILE__;
		}
	}

	cout << "\n\nTrim excess vector capacity...\n";

	// Now that we have all of the data we will need for this example,
	// it turns out that we have allocated way too much space for vWidgets.
	// In order to reclaim that memory, we will need to "shrink" the vector.
	// Unfortunately the vector doesn't have a GetRidOfUnusedSpace() member
	// function.  (Remember, reserve() and resize() can only increase the 
	// capacity of the vector, not decrease it.) Refer to the article to 
	// understand the details of how the following code works.

	int capacity_before = static_cast<int>(vWidgets.capacity());

	vector<Widget>(vWidgets).swap(vWidgets);

	int capacity_after = static_cast<int>(vWidgets.capacity());

	cout << "\n capacity_before = " << capacity_before << "\n";
	cout << " capacity_after  = " << capacity_after << "\n\n";

	return 0;
}


