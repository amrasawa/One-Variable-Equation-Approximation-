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

float gprime(float parameter) {// finding the 1st derivative of g(x) in order to show there's exactly one solution in the algorithm. 
	return (-3 / 2.0) * (pow(parameter, 2.0)) * (1 - pow(parameter, 3.0));
}

float deriv(float parameter) {// used in newtons method where the nomerator represents f(p[n-1]) and the denominator represent the derivative of the same point 
	
	float numerator = (pow(parameter, 3) + 2 * sqrt(parameter) - 1);
	float denominator = (3 * pow(parameter, 2) + 1 / sqrt(parameter));
	
	return parameter - (numerator / float(denominator));
}

void bisection(float a, float b);
void fixed_point(float a, float b);
void newtons(float a, float b);
void existence(float a, float b);
bool uniquenss(float a, float b);

int main() {
	
	//defining the interval
	float a, b;
	a = 0.0;
	b = 1.0;
	float maxima;
	
	//show the existence of at least one solution of f(x)
	existence(a, b);
	
	//show the uniqueness of this solution in (a,b)
	if (uniquenss(a, b)) {
		
		maxima = fmax(g(a), g(b));// to find the maxima of g(x) in (0,1).
	
		cout << "|g(x)| <= " << maxima << " < " << 1
			<< "\twhich shows that the equation has exactly one solution in (a,b)\n\n";
	
	}
	else {
		cout << "it is not unique\n\n";
	}
	
	cout << "---------------------------------------------------------------------------------------------------------\n\n";
	//calling Bisection method
	bisection(a, b);
	
	//calling fixed-point method
	fixed_point(a, b);
	
	// calling newton's method
	newtons(a, b);

	return 0;
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

void existence(float a, float b) {
	float ga = g(a);
	float gb = g(b);
	// first we need to show that 0<=g(x)<=1
	if ((ga <= 1 && ga >= 0) && (gb >= 0 && gb <= 1))
		cout << "there's a fixed point in (0,1)\n"
			<< "since g(0)= "<<ga<<" and g(1)= "<< gb<<", which verifies that 0<=g(x)<=1\n\n";
	else {
		cout << "there's no fixed point in (0,1)";
	}

}

bool uniquenss(float a, float b) {
	//using bisection method to prove that there's no solution in (a, b) for dg(x)/dx in other words it diverges 
	// hence we show the uniqueness of the fixed point and the equation has only one soltion in (0,1)

	int n = 0;
	vector<float>c;// vector of bisectors 
	c.push_back((a + b) / 2.0);
	a = 0.01;
	b = 0.9;
	while (abs(gprime(c[n])) > TOL) { // algorithm 
		if (gprime(a) * gprime(c[n]) < 0)
			b = c[n];
		else
			a = c[n];
		c.push_back((a + b) / 2.0);
		++n;
		if (n > 100)// the sequence doesn't converge to a solution so it verifies that g(x) is either strictly increasing or strictly decreasing in (0,1).
			return true;
	}
	return false;	// the sequence converges, therefore it's not unique.
}

