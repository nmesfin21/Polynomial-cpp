//------------------------------polynomial.cpp---------------------------------
// Author: Natnae Tezera
// Date Created: 3/29/2017
// Last Modified: 4/7/2017
// 
//-----------------------------------------------------------------------------
// Purpose: This is an implimentation file for polynomial.h
// It uses circular, doubley linked list with dummy header to store the 
// coefficient and power of a polynomial. 
//    
//	For instance, 4x^6 - 5x^3 + 9 can be stored in doubley linked list as shown
//	below 	
//	   dummy head			first Node		second node........ lastNode			
//	   .---.-.-.----.    .---.-.-.----.    .---.-.-.-----.    .---.-.-.----.
//	.->|pre|0|0|next|<-->|pre|4|6|next|<-->|pre|-5|3|next|<-->|pre|9|0|next|<-.
//	|  '---'-'-'----'    '---'-'-'----'    '---'-'-'-----'    '---'-'-'----'  |	
//	|																		  |
//	'-------------------------------------------------------------------------'
//	
// Assumption: rhs stands for "right hand side", lhs stand for "left hand side"
//		ex.  if a = b, a is lhs and b is rhs
//-----------------------------------------------------------------------------

#include <iostream>
#include <cmath>
#include "polynomial.h"

using namespace std;

//---------------------------Overload Operator<<-------------------------------
// operator <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
// Precondition: None
// Postconditon: if theres in no polynomial function prints " No Polynomial 
//			function" Other wise prints Cn * x^n + Cn-1 + ...C1 * X + C0
//-----------------------------------------------------------------------------
ostream& operator<<(ostream &output, const Polynomial& p) {
	
	Polynomial::Term *toBePrinted = p.head->next;		//set scope for Term	
	
	// Check if there functioin is empty 
	if (p.head->next == NULL && p.head->prev == NULL) {	
		output <<" No polynomial function! ";
	}
	else{
		bool hasZeroPower = false;		// A flag to indicate if the polynomial
										// has a zero expoenent component
		double zeroPowerCoef = 0.0;

		while (toBePrinted != p.head) {
			// Handles when the exponent of the variable in the function 
			// is exponent 0
			if (toBePrinted->power == 0 ) {
				if(toBePrinted->next == p.head){
					// print out the 0 power coeficient and exit
					output << toBePrinted->coeff;  							
					return output;
				}
				else{
					// Flag the variable with 0 power exponent 
					// Assign the coefficient to zeroPowerCoef
					hasZeroPower = true;	
					zeroPowerCoef = toBePrinted->coeff;
					toBePrinted = toBePrinted->next;	// skip to next
				}
			
			}
			// Handles when the exponent of the variable in the function 
			// is exponent 1
			else if (toBePrinted->power == 1) {
				if (toBePrinted->next != p.head) {
					if(toBePrinted->coeff > 0){
						output << "" << toBePrinted->coeff<< "x " << "+ ";
					}
					else {
						output << ""<< toBePrinted->coeff << "x " << "- ";
					}
				}
				else{
					if (toBePrinted->coeff > 0) {
						if(toBePrinted->coeff > 1){
							output << "" << toBePrinted->coeff << "x ";
						}
						else {
							output<< "" << "x ";
						}
					}
					else {
						if (toBePrinted->coeff < 1) {
							output << "" << toBePrinted->coeff << "x ";
						}
						else {
							output << "" << "-x ";
						}
					}
				}
				toBePrinted = toBePrinted->next;
			}
			// Handles when the exponent of the variable of in the functio
			// is not either 0 or 1, and this is not the last node.
			else if(toBePrinted->next != p.head) {
				if(toBePrinted->coeff != 1){
					if(toBePrinted->next->coeff > 0){
						output << toBePrinted->coeff <<"" << "x^" 
							<< toBePrinted->power << " " << "+ ";
					}
					else {
						output << toBePrinted->coeff << "" << "x^"
							<< toBePrinted->power;

					}
				 }
				else {
					if (toBePrinted->next->coeff > 0) {
						output << "" << "x^" << toBePrinted->power << 
														" " << "+ ";
					}
					else {
						output << ""<< "x^" << toBePrinted->power << " ";
					}
				 }
				toBePrinted = toBePrinted->next;
			}
			// Handles when the exponent of the variable of in the functio
			// is not either 0 or 1.
			else {
				output << toBePrinted->coeff << "" << "x^" << toBePrinted->power;
				toBePrinted = toBePrinted->next;
			}
		}
		// If the function has a variable with zero power, print the coefficent
		// at the end, other wise do nothing
		if(hasZeroPower == true){
			if(zeroPowerCoef >= 0){
				output << " + " << zeroPowerCoef;
			}
			else {
				output << " - " << zeroPowerCoef;
			}
		}
		return output;
	}

}
// end of operator<<

//----------------------------Default Constructor------------------------------
// Defaulat Constructor: construct a polynomial of degree- 0 and coefficent 0.0 
// Precondtion: None
// Postcondition: A 0-degree Polynomial with coefficent 0.0 constructed
//-----------------------------------------------------------------------------
Polynomial::Polynomial() {
	size = 0;
	head = new Term;
	head->coeff = 0.0;
	head->power = 0;
	head->prev = NULL;
	head->next = NULL;
}
// end of Default Constructor

//------------------------------Copy Constructor-------------------------------
// Copy Constructor: 
// Precondtion: p is defined by the convention in polynomial.h
// Postcondition: A copy of Polynomial p  is constructed
//-----------------------------------------------------------------------------
Polynomial::Polynomial(const Polynomial &rhs) {

	// copy the dummy head
	head = new Term; 
	head->coeff = rhs.head->coeff;
	head->power = rhs.head->power;

	// check if the original linked list is empty
	if (rhs.head->next == NULL && rhs.head->prev == NULL) {
		head->next = NULL;
		head->prev = NULL;
		size = 0;
	}
	else {
		// Iterate through p and copy each node
		Term *curr = rhs.head->next;
		Term *currCopy = head;
		while (curr != rhs.head) {
			Term *temp = new Term;			// temporary node
			temp->coeff = curr->coeff;
			temp->power = curr->power;
			temp->next = head;
			temp->prev = currCopy;
			head->prev = temp;
			currCopy->next = temp;
			currCopy = temp;
			curr = curr->next;	
			size++;				// increment size
		}
	
	}
}
// end of copy constructor

//------------------------------Destructor------------------------------------
// Destructor: Deallocate the memory occupied by *this
// Precondtion: Node
// Postcondition: Deallocate the program used by the 
//-----------------------------------------------------------------------------
Polynomial::~Polynomial() {
	
	// if the linked list is empty delete the dummy node
	if (head->next == NULL && head->prev == NULL) {

		delete head;

	}
	else {
		
		// Go through the linked list and delte all the data and
		// Assign the prev and next pointers to NULL
		while (head->next != head) {
			Term *junk =  head;
			head = head->next;
			junk->prev->next = head;
			head->prev = junk->prev;
			delete junk;
			junk = NULL;
			
			size--;
		}
		//delete head;
		//head = NULL;
		

	}
}
// end of Destructor

//---------------------------Overload Operator=--------------------------------
// operator=: overload operator=
// precondition: None
// Postondition: rhs is assigned to this
//-----------------------------------------------------------------------------
Polynomial& Polynomial::operator=(const Polynomial& rhs) {

	// check for self assignmet
	if (this == &rhs) {
		return *this;
	}
	else 
	{
		// if lhs is not empty deallocate memory and copy p to lhs, otherwise
		// copy p to lhs
		if (head->next == NULL && head->prev == NULL){
			Term *curr = rhs.head->next;
			Term *currCopy = head;
			while (curr != rhs.head) {
				Term *temp = new Term;
				temp->coeff = curr->coeff;
				temp->power = curr->power;
				temp->next = head;
				temp->prev = currCopy;
				head->prev = temp;
				currCopy->next = temp;
				currCopy = temp;
				curr = curr->next;
				size++;
			}
		}
		else{
			Term *temp = head;
			
			// Remove all the elements from lhs
			while (size != 0) {
				Term *junk = head->next;
				temp->next = junk->next;
				junk->next->prev = temp;
				size--;
				junk->next = NULL;
				junk->prev = NULL;
				delete junk;
				
			}	
			if ((rhs.head->next == NULL && rhs.head->prev == NULL)) {
				return *this;
			}
			else{
				Term *curr = rhs.head->next;
				Term *pos = head;
			
				while (curr != rhs.head){	
					Term *temp = new Term;
					temp->coeff = curr->coeff;
					temp->power = curr->power;
					temp->prev = pos;
					pos->next = temp;
					temp->next = head;
					pos = pos->next;
					curr = curr->next;
				}
				return *this;
			}
		}
			
	}
	return *this;
}
// end of operator=

//---------------------------Overload Operator+--------------------------------
// operator+: overload operator+
// precondition: rhs is a polynomial
// Postondition: Adds lhs and p and return the sum of the two polynomial
//-----------------------------------------------------------------------------
Polynomial Polynomial::operator+(const Polynomial& rhs) const {
	Polynomial sum;		// create a variable to hold the sum
	
	if (head->next == NULL && head->prev == NULL) {	  //Check if lhs is empty
		sum = rhs;	
	}
	// Check if rhs is empty
	else if (rhs.head->next == NULL && rhs.head->prev == NULL) { 
		sum = *this;
	}
	else {
		Term *firstNode = head->next;		// Points to the first node of lhs 
		Term *secondNode = rhs.head->next;	// Points to the first node of rhs

		while (firstNode != head || secondNode != rhs.head) {
			if (firstNode->power == secondNode->power) {
				sum.changeCoefficient(firstNode->coeff + secondNode->coeff
										, firstNode->power);
				firstNode = firstNode->next;	// Both advance to next node
				secondNode = secondNode->next; 
			}
			else if (firstNode->power > secondNode->power) {
				sum.changeCoefficient(firstNode->coeff, firstNode->power);
				firstNode = firstNode->next; // firstNOde advance to next node
			}
			else {
				sum.changeCoefficient(secondNode->coeff, secondNode->power);
				secondNode = secondNode->next; //secondNode advace to next node
			}
		}
		// if lhs is empty, hand only rhs, other wise handle the rhs
		if (firstNode == head && secondNode != rhs.head) {
			while (secondNode != rhs.head) {
				sum.changeCoefficient(secondNode->coeff, secondNode->power);
				secondNode = secondNode->next;
			}
		}
		else {
			while (firstNode != head) {
				sum.changeCoefficient(firstNode->coeff, firstNode->power);
				firstNode = firstNode->next;
			}
		}	
	}
	return sum;
}
// end of operator+

//---------------------------Overload Operator---------------------------------
// operator+: overload operator-
// precondition: rhs is a polynomial
// Postondition: subtract rhs from lhs and return the diferrence of the two
//				polynomial
//-----------------------------------------------------------------------------
Polynomial Polynomial::operator-(const Polynomial& rhs) const {
	Polynomial difference;

	if (head->next == NULL && head->prev == NULL) {	// check if lhs is empty
		difference = rhs;
	}
	else if (rhs.head->next == NULL && rhs.head->prev == NULL) {
		difference = *this;
	}
	else{

		Term *firstNode = head->next;		// Points to the first node of lhs 
		Term *secondNode = rhs.head->next;	// Points to the first node of rhs

		while (firstNode != head || secondNode != rhs.head) {
			if (firstNode->power == secondNode->power) {
				difference.changeCoefficient(firstNode->coeff - 
					secondNode->coeff, firstNode->power);
				firstNode = firstNode->next;	// Both advance to the next 
				secondNode = secondNode->next;
			}
			else if (firstNode->power > secondNode->power) {
				difference.changeCoefficient(firstNode->coeff,firstNode->power);
				firstNode = firstNode->next;	// firstNode advance to next
			}
			else {
				difference.changeCoefficient(secondNode->coeff,secondNode->power);
				secondNode = secondNode->next; // secondNode advance to next
			}
		}
		// if lhs is empty, hand only rhs, other wise handle the rhs
		if (firstNode == head && secondNode != rhs.head) {
			while (secondNode != rhs.head) {
				difference.changeCoefficient(secondNode->coeff,secondNode->power);
				secondNode = secondNode->next;
			}
		}
		else {
			while (firstNode != head) {
				difference.changeCoefficient(firstNode->coeff, firstNode->power);
				firstNode = firstNode->next;
			}
		}
	}
	return difference;
}
// end operator-

//---------------------------Overload Operator==-------------------------------
// operator==: overload operator==
// precondition: rhs is a polynomial
// Postondition: return true if lhs and rhs are equal or false other wise
//
//-----------------------------------------------------------------------------

bool Polynomial::operator==(const Polynomial& rhs) const {
	if (rhs.head->next == NULL && rhs.head->prev == NULL) {
		return false;
	}

	else {
		Term * firstNode =  head->next;
		Term * secondNode = rhs.head->next;

		while (firstNode != head) {
			if (firstNode->coeff != secondNode->coeff || firstNode->power !=
														secondNode->power) {
				return false;
			}
			firstNode = firstNode->next;
			secondNode = secondNode->next;
		}
	}
	return true;

}
// end operator==

//---------------------------Overload Operator!=-------------------------------
// operator!=: overload operator!=
// precondition: rhs is a polynomial
// Postondition: return false if lhs and rhs are equal or true other wise
//-----------------------------------------------------------------------------
bool Polynomial::operator!=(const Polynomial& p) const {
	if (*this == p) {
		return false;
	}
	else {
		return true;
	}
}
// end operator!=

//---------------------------Overload Operator+=-------------------------------
// operator+=: overload operator+=
// precondition: rhs is a polynomial
// Postondition: Adds lhs and rhs and assign the result to lhs
//-----------------------------------------------------------------------------
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {

		*this = *this + rhs;
		return *this;
	
}
//end operator+=

//---------------------------Overload Operator-=-------------------------------
// operator-=: overload operator-=
// precondition: rhs is a polynomial
// Postondition: subtract rhs and lhs and assign the result to lhs
//-----------------------------------------------------------------------------
Polynomial& Polynomial:: operator-=(const Polynomial& rhs) {
	
	*this = *this - rhs;
	return *this;

}
//end operator-=

//-------------------------------degree()--------------------------------------
// degree: Returns the degree of the polynomial
// precondition: None
// Postondition: The degree of the polynomial returned
//-----------------------------------------------------------------------------
int Polynomial::degree() const{
	
	int largestPower = 0;
	if (head->next == NULL && head->prev == NULL) {
		largestPower = 0;
	}
	else {
		Term *temp = head->next;
		largestPower = temp->power;
			while (temp != head) {
				if (temp->power > largestPower) {
					largestPower = temp->power;
				}
				temp = temp->next;
			}
		
	}
	return largestPower;
}
// end degree

//---------------------------coefficient()-------------------------------------
// coefficient: Returns the coefficient of the x^power term
// precondition: power is an integer number
// Postondition: Returnt the coefficient of given x^power term
//-----------------------------------------------------------------------------
double Polynomial::coefficient(const int power) const {
	Term *temp = head->next;
	double coeff = 0.0;
	while (temp != head) {
		if (temp->power == power) {
			coeff = temp->coeff;
		}
		temp = temp->next;
	}
	return coeff;
}
// end of coefficient()

//------------------------changeCoefficient------------------------------------
// changeCoefficient: replaces the coefficient of the x^power term
// Precondtion: newcoefficient is a rational number, and power is 
//			a non-negative integer number.
//
// PostCondition: replaces the coefficient of the x^power term
//
//-----------------------------------------------------------------------------
bool Polynomial::changeCoefficient(const double newCoefficient,const int power){
	
	// check if the linked list is empty
	if (head->next == NULL && head->prev == NULL) {
		insert(head, newCoefficient, power);
		return true;
	}
	// if it is bigger than the highest degree, make it the first element
	// in the linked list
	else if (power > degree()) {		
		insert(head->next, newCoefficient, power);		// Call insert function
		return true;
	}
	else 
	{
		// Check if if there is variable with the exponent equal to power,
		// if there is one, change the coefficient, otherwise create a new node
		// and add newCoefficient with new exponent power in the linked list
		Term *temp = head->next; 
		while (temp != head) {
			if (temp->power == power) {
				insert(temp->next, newCoefficient, power); // Call insert
				remove(temp);		// remove the term with equal power
				temp = NULL;
				delete temp;
				return true;
			}
			temp = temp->next;		// Advance to next term
		}
		temp = head->next;
		while(temp != head){
			 if (temp->next->power < power) {
				insert(temp->next, newCoefficient, power);
				temp = NULL;
				delete temp;
				return true;
			}
			temp = temp->next;
		}
		insert(temp, newCoefficient, power); // call insert
		temp = NULL;
		delete temp;
	}
	return true;
}
// end of changeCoefficient()

//------------------------------insert-----------------------------------------
// insert: inserts a new Term node with newCoefficient and power just before 
//			the existing Term pointed by the next pointer. The insert function 
//			will be used bychangeCoefficient to insert a new term.
// Precondtion: power is a non negative integer, newCoefficient is a whole
//			number
//
// PostCondition: a new Term node with newCoefficient and power added to 
//			the existing term pointed by next
//
//-----------------------------------------------------------------------------
bool Polynomial::insert(Term* next,const double newCoefficient,const int power){
	
	// Create a new node and assign value
	Term *toBeInserted = new Term;
	toBeInserted->coeff = newCoefficient;
	toBeInserted->power = power;

	if (toBeInserted->coeff == 0) {
		toBeInserted->next = NULL;
		toBeInserted->prev = NULL;
		toBeInserted = NULL;
		delete toBeInserted;
		return false;
	}
	else if (head->next == NULL && head->prev == NULL) {
		head->next = toBeInserted;
		toBeInserted->prev = head;
		head->prev = toBeInserted;
		toBeInserted ->next = head;
		size++;
		return true;
	}
	
	else
	{
		// Insert the new node in the linked list
		toBeInserted->next = next;
		toBeInserted->prev = next->prev;
		next->prev->next = toBeInserted;
		next->prev = toBeInserted;
		size++;
		return true;
	}
	
}
// end of insert

//-------------------------------remove----------------------------------------
// remove: deletes the existing Term node pointed by the pos pointer. 
//			The remove function will be used by changeCoefficient to delete an 
//			existing term when its coefficient is changed in 0. In addition, 
//			it will be used by a destructor and the operator= to de-allocates 
//			all Term nodes.
// Precondtion: None
//
// PostCondition: The node pointed by pos pointer is deleted
//
//-----------------------------------------------------------------------------
bool Polynomial::remove(Term* pos) {
	
	//Check if the linked list is empty
	if (head->next == NULL && head->prev == NULL) {
		return false;
	}
	else{
		Term *temp = pos->prev;
		temp->next = pos->next;
		pos->next->prev = temp;
		size--;
		pos->next = NULL;
		pos->prev = NULL;
		delete pos;

	}
	
	return true;
}
// end of remove


