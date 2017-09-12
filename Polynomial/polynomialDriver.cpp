//-------------------------polynomialDriver.cpp--------------------------------
// Author: Natnael Tezera
// Date Created: 3/29/2017
// Last Modified: 4/7/2017
// 
//-----------------------------------------------------------------------------
// Purpose: This is the driver class for polynomial.cpp.
//			It tests the function in polynomial.cpp.
// Assumption: Since insert and remove functions are private, they has been 
//			tested in through changeCoefficiet fumctopm  
//-----------------------------------------------------------------------------
#include <iostream> 
using namespace std;

#include "polynomial.h" 
int main()
{
	
	Polynomial p1;		
	
	
	// testing1: changeCoefficient
	cout<< "  test1: changeCoefficient() "<< endl;
	p1.changeCoefficient(4, 1);		// inserting in empty lins
	cout<< "p1 = " << p1 << endl;

	
	
	p1.changeCoefficient(4.3, 0);	// inserting a 0-degree term
	cout << "p1 = " << p1 << endl;

	p1.changeCoefficient(1, 1);		// changing coefficient
	p1.changeCoefficient(4, 4);		// inserting more terms
	p1.changeCoefficient(2.2, 2);
	p1.changeCoefficient(-3.8, 3);
	cout << "p1 = " << p1 << endl;

	p1.changeCoefficient(0, 0);		// deleting coifficint 0-term
	cout << "p1 = " << p1 << endl;
	cout<< endl;

	// testing2:operator=
	cout << "  test2: operator=" << endl;
	cout<< "p2 = p1"<< endl;
	Polynomial p2 = p1;
	p2.changeCoefficient(9.5, 2);
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	cout<< endl;

	// testing3:operator+
	cout << "  test3: operator+" << endl;
	cout << "p3 = p1 + p2" << endl;
	Polynomial p3 = p1 + p2;
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	cout << "p3 = " << p3 << endl;
	cout << endl;

	// testing4:operator-
	cout << "  test4: operator-" << endl;
	cout << "p3 = p1 - p2" << endl;
	p3 = p1 - p2;
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	cout << "p3 = " << p3 << endl;
	cout << endl;

	// testing5:operator!=
	cout << "  test5: operator!=" << endl;
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	if (p1 == p2) {
		cout<< "Are p1 equal to p2? Yes" << endl;
	}
	else {
		cout << "are p1 equal to p2? No" << endl;
	}
	cout << endl;
	
	// testing6:operator==
	p2.changeCoefficient(2.2, 2);
	cout << "  test6: operator==" << endl;
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	
	if (p1 == p2) {
		cout << "Are p1 equal to p2? Yes" << endl;
	}
	else {
		cout << "are p1 equal to p2? No" << endl;
	}
	cout << endl;

	
	// testing7:operator+=
	cout << "  test7: operator+=" << endl;
	cout << "p1 += p2" << endl;
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	p1+= p2;
	cout <<"p1 = " << p1 << endl;
	cout << endl;

	// testing8:operator-=
	cout << "  test8: operator-=" << endl;
	cout << "p1 -= p2" << endl;
	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	p2 -= p1;
	cout << "p2 = " << p2 << endl;
	cout << endl;

	//testing9:degree()
	cout << "  test9: degree()"<< endl;
	cout << "p1 = " << p1 << endl;
	cout << "degree of p1 is: " << p1.degree()<< endl;
	cout << endl;
	cout << "p2 = " << p2 << endl;
	cout << "degree of p2 is: " << p2.degree()<< endl;
	cout << endl;

	//testing10:coefficient()
	cout << "  test10: coefficient()" << endl;
	cout << "p1 = " << p1 << endl;
	cout << "coefficient of power 4 in p1 is: " << p1.coefficient(4) << endl;
	cout << endl;
	cout << "p2 = " << p2 << endl;
	cout << "coefficient of power 2 in p2 is: " << p2.coefficient(2) << endl;
	cout << endl;
	

	system("pause");
	
}