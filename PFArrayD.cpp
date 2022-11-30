//Program to demonstrate the class PFArrayD.
#include <iostream>
using namespace std;

//Objects of this class are partially filled arrays of doubles.
class PFArrayD
{
public:
    PFArrayD( );
    //Initializes with a capacity of 50.

 	explicit PFArrayD(int capacityValue);	// CONVERSION CONSTRUCTOR: It takes a single parameter and converts this parameter into the class type. EXPLICIT YAPILMALIDIR !!

    PFArrayD(const PFArrayD& pfaObject);

    void addElement(double element);
    //Precondition: The array is not full.
    //Postcondition: The element has been added.

    bool full( ) const { return (capacity == used); }
    //Returns true if the array is full, false otherwise.

    int getCapacity( ) const { return capacity; }

    int getNumberUsed( ) const { return used; }

    void emptyArray( ){ used = 0; }
    //Empties the array.

    double& operator[](int index);
    //Read and change access to elements 0 through numberUsed - 1.

    PFArrayD& operator =(const PFArrayD& rightSide);

    ~PFArrayD( );

protected:
    double *a; //for an array of doubles.
    int capacity; //for the size of the array.
    int used; //for the number of array positions currently in use.

};

PFArrayD::PFArrayD(int size = 50) :capacity(size), used(0)
{
    a = new double[capacity];
}

PFArrayD::PFArrayD(const PFArrayD& pfaObject)
  :capacity(pfaObject.getCapacity( )), used(pfaObject.getNumberUsed( ))
{
    a = new double[capacity];
    for (int i =0; i < used; i++)
        a[i] = pfaObject.a[i];
}

void PFArrayD::addElement(double element)
{
    if (used >= capacity)
    {
        cout << "Attempt to exceed capacity in PFArrayD.\n";
        exit(0);
    }
    a[used] = element;
    used++;
}

double& PFArrayD::operator[](int index)
{
    if (index < 0 || index >= used)
    {
        cout << "Illegal index in PFArrayD.\n";
        exit(0);
    }

    return a[index];
}

PFArrayD& PFArrayD::operator =(const PFArrayD& rightSide)
{
    if (capacity != rightSide.capacity)
    {
        if (a != nullptr) delete [] a;
        a = new double[rightSide.capacity];
    }

    capacity = rightSide.capacity;
    used = rightSide.used;
    for (int i = 0; i < used; i++)
        a[i] = rightSide.a[i];

    return *this;
}

PFArrayD::~PFArrayD( )
{
    delete [] a;
}



class PFArrayDBak : PFArrayD {

public : 
	PFArrayDBak(int size = 50);
	PFArrayDBak(const PFArrayDBak& oth);
	~PFArrayDBak();
	PFArrayDBak& operator = (const PFArrayDBak& oth);
	
	void backup();
	void restore();

private : 
	double* b;	// for backup data
	int bCapacity; // backup data's capacity
};

PFArrayDBak::PFArrayDBak(int size) : PFArrayD(size), bCapacity(0), b(nullptr) {
	
}

PFArrayDBak::PFArrayDBak(const PFArrayDBak& oth) : PFArrayD(oth), bcapacity(oth.bCapacity), b(nullptr) {
	b = new double[bCapacity];
	for (int i = 0; i < bCapacity; ++i) b[i] = oth.b[i];
}

PFArrayDBak::~PFArrayDBak() {
	if (b != nullptr) delete [] b;
	b = nullptr;
}

PFArrayDBak& PFArrayDBak::operator =(const PFArrayDBak& oth) {
	if (this == &oth) return *this;

	PFArrayD::operator =(oth);
	if (b != nullptr) delete [] b;
	
	b = new double[oth.bCapacity];
	bCapacity = oth.bCapacity;
	for (int i = 0; i < bCapacity; ++i) b[i] = oth.b[i];
		
	return *this;
}

void PFArrayDBak::backup() {
	if (bCapacity != used) {
		if (b != nullptr) delete [] b;
		b = new double[used];
		bCapacity = used;
	}
	
	for (int i = 0; i < bCapacity; ++i) b[i] = a[i];
}

void PFArrayDBak::restore() {
	emptyArray();
	for (int i = 0; i < bCapacity; ++i) addElement(b[i]);
}


int main( )
{
    cout << "This program tests the class PFArrayD.\n";

    return 0;
}

