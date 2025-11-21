#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

const float TOL = 0.001;
float func(float parameter) { // this is the function given, to implement the bisection method 
	
	return (pow(parameter, 3) + 2 * sqrt(parameter) - 1) / (pow(parameter, 2) + 1);
}

float g(float parameter) {// this is g(x) used in fixed-point method 
	
	return pow((1 - pow(parameter, 3)), 2) / 4;
}

float deriv(float parameter) {// used in newtons method where the nomerator represents f(p[n-1]) and the denominator represent the derivative of the same point 
	
	float numerator = (pow(parameter, 3) + 2 * sqrt(parameter) - 1);
	float denominator = (3 * pow(parameter, 2) + 1 / sqrt(parameter));
	
	return parameter - (numerator / float(denominator));
}

void bisection(float a, float b);
void fixed_point(float a, float b);
void newtons(float a, float b);

int main() {
	
	//defining the interval
	float a, b;
	a = 0.0;
	b = 1.0;

	//calling Bisection method
	bisection(a, b);
	//calling fixed-point method
	fixed_point(a, b);
	// calling newton's method
	newtons(a, b);
}

void bisection(float a, float b) {
	
	int n = 0;
	vector<float>c;// vector of bisectors 
	c.push_back((a + b) / 2.0);

	while (abs(func(c[n])) > TOL) { // algorithm 
		if (func(a) * func(c[n]) < 0)
			b = c[n];
		else
			a = c[n];
		c.push_back((a + b) / 2.0);
		++n;
	}

	cout << "-----------------   Bisection Method -----------------\n"
		<< c.size() << " Iterations\n";

	cout << "\nApproximate Solution= " << c[n] << endl;
	cout << "\nError= " << func(c[n]);

	cout << "\n\nSequence of Bisectors until convergence: \n";
	for (float a : c) {
		cout << a << ", ";
	}
	cout << "\n";

}

void fixed_point(float a, float b) {
	
	vector<float> p; // to store the sequence until convergence 
	p.push_back((a + b) / 2.0);

	int n = 1;
	p.push_back(g(p[0]));

	while (abs(p[n] - p[n - 1]) > TOL) {// algorithm 
		++n;
		p.push_back(g(p[n - 1]));
	}


	cout << "\n-----------------   Fixed-Point Method -----------------\n"
		<< p.size() - 1 << " Iterations\n";

	cout << "\nApproximate Solution= " << p[n] << endl;
	cout << "\nError= " << abs(p[n] - p[n - 1]);

	cout << "\n\nSequence of Bisectors until convergence: \n";
	for (float a : p) {
		cout << a << ", ";
	}
	cout << "\n";
}

void newtons(float a, float b) {
	
	vector <float> p;
	p.push_back((a + b) / 2.0);
	p.push_back(deriv(p[0]));
	
	int n = 1;
	while (abs(p[n] - p[n - 1]) > TOL) {// algorithm 
		++n;
		p.push_back(deriv(p[n - 1]));
	}

	cout << "\n-----------------   Newton's Method -----------------\n"
		<< p.size() - 1 << " Iterations\n";

	cout << "\nApproximate Solution= " << p[n] << endl;
	cout << "\nError= " << abs(p[n] - p[n - 1]);

	cout << "\n\nSequence of Bisectors until convergence: \n";
	for (float a : p) {
		cout << a << ", ";
	}
	cout << "\n";

}