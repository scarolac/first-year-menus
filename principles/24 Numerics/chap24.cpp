#include <std_lib_facilities.h>
#include <limits>
#include <limits.h>
#include <float.h>
#include "Matrix.h"
#include "MatrixIO.h"
#include <complex>
#include <cmath>
#include <cerrno>
#include <iomanip>
using namespace Numeric_lib;

namespace notes
{
	using Numeric_lib::Index;

	void f(int i, double fpd)
	{
		cout << std::setprecision(15);
		char c = i;
		cout << "c = i: " << int(c) << '\n';
		short s = i;
		cout << "s = i: " << s << '\n';
		i = i + 1;
		cout << "i + 1: " << i << '\n';
		long lg = i*i;
		cout << "lg = i*i: " << lg << '\n';
		float fps = fpd;
		cout << "fps = fpd: " << fps << '\n';
		i = fpd;
		cout << "i = pfd: " << i << '\n';
		fps = i;
		cout << "fps = i: " << fps << '\n';
	}

	void g()
	{
		char ch = 0;
		for (int i = 0; i<500; ++i)
			cout << int(ch++) << '\t';
	}

	void trythis1()
	{
		float x = 1.0 / 10;
		float sum = 0;
		for (int i = 0; i<10; ++i) sum += x;
		std::cout << std::setprecision(15) << sum << '\n';
	}

	void trythis2()
	{
		g();
		cout << "\n\n";
		f(127, 5.7);
		cout << '\n';
		f(33000, 3.4e39);
		cout << '\n';
		f(2147483647, 21.00000009e8);
	}

	void numeric_limits()
	{
		cout << "number of bytes in an int: " << sizeof(int) << endl;
		cout << "largest int: " << INT_MAX << endl;
		cout << "smallest int value: " << std::numeric_limits<int>::min() << endl;

		if (std::numeric_limits<char>::is_signed)
			cout << "char is signed\n";
		else
			cout << "char is unsigned\n";

		cout << "char with min value: " << std::numeric_limits<char>::min() << endl;
		cout << "min char value: " << int(std::numeric_limits<char>::min()) << endl;
	}

	void f2(int n1, int n2, int n3)
	{
		Numeric_lib::Matrix<double, 1> ad1(n1);	//elements are doubles, 1 dimension
		Numeric_lib::Matrix<int, 1> ai1(n1);		//elements are ints
		ad1(7) = 0;		//subscript with () or []
		ad1[7] = 8;

		Numeric_lib::Matrix<double, 2> ad2(n1, n2);
		Numeric_lib::Matrix<double, 3> ad3(n1, n2, n3);
		ad2(3, 4) = 7.5;
		ad3(3, 4, 5) = 9.2;
	}

	template<class T>string to_string(const T& t)
	{
		ostringstream os;
		os << t;
		return os.str();
	}

	//------------------------------------------------------------------------------

	// An exception of this type is thrown when elimination fails.
	struct Elim_failure : std::domain_error {
		Elim_failure(std::string s) : std::domain_error(s) { }
	};

	//------------------------------------------------------------------------------

	// An exception of this type is thrown when back substitution fails.
	struct Back_subst_failure : std::domain_error {
		Back_subst_failure(std::string s) : std::domain_error(s) { }
	};

	typedef Numeric_lib::Matrix<double, 2> Matrix;
	typedef Numeric_lib::Matrix<double, 1> Vector;

	void classical_elimination(Matrix& A, Vector& b)
	{
		const Index n = A.dim1();

		//traverse from the 1st column to the next to list, filling zeros in all elements under the diagonal
		for (Index j = 0; j < n - 1; ++j)
		{
			const double pivot = A(j, j);
			if (pivot == 0) throw Elim_failure("Elimination failure in row " + to_string(j));

			//fill zeros into each element under the diagonal of the ith row
			for (Index i = 0; i < n; ++i)
			{
				const double mult = A(i, j) / pivot;
				A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
				b(i) -= mult *b(j);		//make the correspodning change to b
			}
		}
	}

	void elim_with_partial_pivot(Matrix& A, Vector& b)
	{
		const Index n = A.dim1();

		for (Index j = 0; j < n; ++j) {
			Index pivot_row = j;

			// look for a suitable pivot:
			for (Index k = j + 1; k < n; ++k)
				if (abs(A(k, j)) > abs(A(pivot_row, j))) pivot_row = j;

			// swap the rows if we found a better pivot:
			if (pivot_row != j) {
				A.swap_rows(j, pivot_row);
				std::swap(b(j), b(pivot_row));
			}

			// elimination:
			for (Index i = j + 1; i < n; ++i) {
				const double pivot = A(j, j);
				if (pivot == 0) error("can't solve: pivot==0");
				const double mult = A(i, j) / pivot;
				A[i].slice(j) = scale_and_add(A[j].slice(j), -mult,
					A[i].slice(j));
				b(i) -= mult * b(j);
			}
		}
	}

	Vector back_substitution(const Matrix& A, const Vector& b)
	{
		const Index n = A.dim1();
		Vector x(n);

		for (Index i = n - 1; i >= 0; --i) {
			double s = b(i) - dot_product(A[i].slice(i + 1), x.slice(i + 1));

			if (double m = A(i, i))
				x(i) = s / m;
			else
				error("can't solve: diagonal element is zero during back substitution");
		}

		return x;
	}

	Vector classical_gaussian_elimination(Matrix A, Vector b)
	{
		classical_elimination(A, b);
		return back_substitution(A, b);
	}

	Vector pivotal_elimination(Matrix A, Vector b)
	{
		elim_with_partial_pivot(A, b);
		return back_substitution(A, b);
	}

	Vector random_vector(Index n)
	{
		Vector v(n);

		for (Index i = 0; i < n; ++i)
			v(i) = 1.0 * n * rand() / RAND_MAX;

		return v;
	}

	Matrix random_matrix(Index n)
	{
		Matrix m(n, n);

		for (Index i = 0; i < n; ++i)
			m[i] = random_vector(n);

		return m;
	}

	Vector operator*(const Matrix& m, const Vector& u)
	{
		const Index n = m.dim1();
		Vector v(n);
		for (Index i = 0; i < n; ++i) v(i) = dot_product(m[i], u);
		return v;
	}

	void solve_linear_eq()
	{
		double a[3][3] =
		{
			{ 1,2,3 },
			{ 2,3,4 },
			{ 3,4,1 }
		};
		double b[3] = { 14,20,14 };

		Matrix A(a);
		Vector B(b);

		cout << "Solving A*x=B" << endl;
		cout << "A=\n" << A << endl;
		cout << "B=" << B << endl;

		Vector x = pivotal_elimination(A, B);
		cout << "x=" << x << endl;
	}

	void solve_random_system(Index n)
	{
		Matrix A = random_matrix(n);    // see §24.6
		Vector b = random_vector(n);

		cout << "A = " << A << endl;
		cout << "b = " << b << endl;

		try {
			Vector x = classical_gaussian_elimination(A, b);
			cout << "classical elim solution is x = " << x << endl;
			Vector v = A * x;
			cout << " A * x = " << v << endl;
		}
		catch (const exception& e) {
			cerr << e.what() << std::endl;
		}
	}

}

void ex04()
{
	int i;
	cout << "\nEnter ints (char to exit): ";
	//errno = 0;<<
	while (cin >> i) {
		errno = 0;
		double d = sqrt(i);
		if (errno == EDOM)
			cout << "no square root\n";
		else
			cout << "sqrt(" << i << ") = " << d << '\n';
	}
}

void ex05()
{
	cin.clear();
	cin.ignore();
	cout << "\nEnter 10 floating point values: ";
	Matrix<double> m(10);
	double d;
	for (int i = 0; i<m.size(); ++i) {
		cin >> d;
		if (!cin) throw runtime_error("Problem reading from cin");
		m[i] = d;
	}
	cout << "Matrix:\n" << m << '\n';
}

void ex06()
{
	cout << "\nMultiplication table\nEnter n: ";
	int n;
	cin >> n;
	cout << "Enter m: ";
	int m;
	cin >> m;
	Matrix<int, 2> mtable(n, m);
	for (Index i = 0; i<mtable.dim1(); ++i) {
		for (Index j = 0; j<mtable.dim2(); ++j) {
			mtable(i, j) = (i + 1)*(j + 1);
			cout << setw(5) << mtable(i, j);
		}
		cout << '\n';
	}
}

void ex07()
{
	Matrix<complex<double>> m(10);
	cout << "\nEnter 10 complex numbers (Re,Im): ";
	complex<double> c;
	for (int i = 0; i<10; ++i) {
		cin >> c;
		if (!cin) throw runtime_error("problem reading complex number");
		m[i] = c;
	}
	complex<double> sum;
	for (Index i = 0; i<m.size(); ++i)
		sum += m[i];
	cout << "Sum: " << sum << '\n';
}

void ex08()
{
	Matrix<int, 2> m(2, 3);
	cout << "\nEnter six ints: ";
	int n;
	for (int i = 0; i<m.dim1(); ++i)
		for (int j = 0; j<m.dim2(); ++j) {
			cin >> n;
			m(i, j) = n;
		}
	cout << "Matrix:\n" << m << '\n';
}

void drill()
{
	//1
	cout << "number of bytes in a char: " << sizeof(char) << endl;
	cout << "number of bytes in a short: " << sizeof(short) << endl;
	cout << "number of bytes in an int: " << sizeof(int) << endl;
	cout << "number of bytes in a long: " << sizeof(long) << endl;
	cout << "number of bytes in a float: " << sizeof(float) << endl;
	cout << "number of bytes in a double: " << sizeof(double) << endl;
	cout << "number of bytes in an int*: " << sizeof(int*) << endl;
	cout << "number of bytes in a double*: " << sizeof(double*) << endl;

	//2
	Matrix<int> a(10);
	Matrix<int> b(100);
	Matrix<double> c(10);
	Matrix<int, 2> d(10, 10);
	Matrix<int, 3> e(10, 10, 10);
	cout << "\nnumber of bytes in a(10): " << sizeof(a) << endl;
	cout << "number of bytes in b(100): " << sizeof(b) << endl;
	cout << "number of bytes in c(10): " << sizeof(c) << endl;
	cout << "number of bytes in d(10, 10): " << sizeof(d) << endl;
	cout << "number of bytes in e(10, 10, 10): " << sizeof(e) << endl;

	//3
	cout << "\nNumber of elements (same order):\n";
	cout << "a:\t" << a.size() << '\n';
	cout << "b:\t" << b.size() << '\n';
	cout << "c:\t" << c.size() << '\n';
	cout << "d:\t" << d.size() << '\n';
	cout << "e:\t" << e.size() << '\n';

	//4 - ints from cin, and output sqrt of no square root if illegal
	ex04();

	// 5: read ten floating-point values from input and put them into a
	// Matrix<double>; print out the Matrix
	ex05();

	// 6: compute a multiplication table for [0,n)*[0,m), represent it as a 2D
	// Matrix. Take n and m from cin and print the table nicely
	ex06();

	// 7: read ten complex<double> from cin, put them into a Matrix, calculate
	// and output the sum of the ten complex numbers
	ex07();

	// 8: read six ints into a Matrix<int,2> m(2,3) and print them out
	ex08();

}

int main()
{
	try
	{
		drill();

		keep_window_open();
		return 0;
	}
	catch (Range_error& re)
	{
		cerr << "Error: " << re.what() << endl;
		keep_window_open("~~");
		return 1;
	}
	catch (exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		keep_window_open("~~");
		return 2;
	}
	catch (...)
	{
		cerr << "Error unknown" << endl;
		keep_window_open("~~");
		return 3;
	}
}