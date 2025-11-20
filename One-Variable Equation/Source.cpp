#include<iostream>
#include<cmath>
#include<vector>
#include<string>
using namespace std;

const float TOL = 0.0001;
float func(float parameter) {
	return (pow(parameter, 3) + 2 * sqrt(parameter) - 1) / (pow(parameter, 2) + 1);
}

float g(float parameter) {
	return pow((1 - pow(parameter, 3)), 2) / 4;
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
	fixed_point(a, b);
}

void bisection(float a, float b) {
	int n = 0;
	vector<float>c;
	c.push_back((a + b) / 2.0);

	while (abs(func(c[n])) > TOL) {
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
	vector<float> p;
	p.push_back((a + b) / 2.0);

	int n = 1;
	p.push_back(g(p[0]));

	while (abs(p[n] - p[n - 1]) > TOL) {
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