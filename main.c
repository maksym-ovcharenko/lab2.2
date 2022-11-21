#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define Name "Maksym"
#define LastName "Ovcharenko"
#define GroupName "RS-21"
#define Faculty "REF"
#define University "Igor Sikorsky Kyiv Polytechnic Institute"

unsigned int method_select(void);
double f(double x);
void print_result(double a, double b, unsigned int n, double I);
void receive_variables(double* a, double* b, int* n);
double left_rectangle(double a, double b, unsigned int n);
double right_rectangle(double a, double b, unsigned int n);
double trapezoid(double a, double b, unsigned int n);
double simpson(double a, double b, unsigned int n);

int main()
{
	const double eps = 0.0001;
	unsigned int num_of_method; // 1 = left , 2 = right , 3 = trap, 4 = Simpson
	double a, b;
    int n;
	unsigned int N = 0;
	double I, I1, I2;


	receive_variables(&a, &b, &n);

    num_of_method = method_select();


	if (num_of_method == 1)
	{
		I = left_rectangle(a, b, n);
		print_result(a, b, n, I);

		do {
			N += 2;
			I1 = left_rectangle(a, b, N);
			I2 = left_rectangle(a, b, N + 2);
		} while (fabs(I2 - I1) > eps);

		printf("\nN = %u I1(N) = %lf\n\n", N, I1);
	}
	else if (num_of_method == 2)
	{
		I = right_rectangle(a, b, n);
		print_result(a, b, n, I);

		do {
			N += 2;
			I1 = right_rectangle(a, b, N);
			I2 = right_rectangle(a, b, N + 2);
		} while (fabs(I2 - I1) > eps);

		printf("\nN = %u I1(N) = %lf\n\n", N, I1);
	}
	else if (num_of_method == 3)
	{
		I = trapezoid(a, b, n);
		print_result(a, b, n, I);

		do {
			N += 2;
			I1 = trapezoid(a, b, N);
			I2 = trapezoid(a, b, N + 2);
		} while (fabs(I2 - I1) > eps);

		printf("\nN = %u I1(N) = %lf\n\n", N, I1);
	}
	else if (num_of_method == 4)
	{
		I = simpson(a, b, n);
		print_result(a, b, n, I);

		do {
			N += 2;
			I1 = simpson(a, b, N);
			I2 = simpson(a, b, N + 2);
		} while (fabs(I2 - I1) > eps);

		printf("\nN = %u I1(N) = %lf\n\n", N, I1);
	}

	return 0;
}

//------------------------------------------------------------

unsigned int method_select(void)
{
	unsigned int var;

	printf("\n\n Choose your method:\n 1 - left \n 2 - right \n 3 - trap \n 4 - Simpson\n> ");
	scanf("%u", &var);

	while (var < 1 || var > 4)
	{
		printf("\n!!!Invalid data. Method : 1, 2, 3 or 4: ");
		scanf("%u", &var);
	}

	switch (var)
	{
	case 1:
			printf("\nYou choose method of LEFT RECTANGLE\n");
			break;

	case 2:
			printf("\nYou choose method of RIGHT RECTANGLE\n");
			break;

	case 3:
			printf("\nYou choose method of TRAPEZOID\n");
			break;

	case 4:
			printf("\nYou choose method of SIMPSON\n");
		    break;
	}

	return var;
}

//------------------------------------------------------------

double f(double x)
{
	return pow(x, 2);
}

//------------------------------------------------------------

void print_result(double a, double b, unsigned int n, double I)
{
	system("cls");
	printf("\n\n\n*******************************************");
	printf("\n*                 Results                 *");
	printf("\n*******************************************\n");

	printf("a = %.2lf  b = %.2lf  n = %u  I = %lf\n", a, b, n, I);
}

 void receive_variables(double* a, double* b, int* n)
{
	double decay_a, decay_b;
    int decay_n;

    printf("\n Enter your variables : \n");
	printf("\n a (low limit)     = ");
	scanf("%lf", &decay_a);

	printf("\n b (high limit)    = ");
	scanf("%lf", &decay_b);

	do {
		printf("\n n (intervals)     = ");
		scanf("%u", &decay_n);
		if (decay_n <= 0)
			printf("\n !!!Invalid input (n > 0) \n");
	} while (decay_n <= 0);
	*a = decay_a;
	*b = decay_b;
	*n = decay_n;

}

//------------------------------------------------------------

double left_rectangle(double a, double b, unsigned int n)
{
	double h, x, sum = 0;

	h = (b - a) / n;
	x = a;

	for (int k = 0; k <= (n - 1); k++)
	{
		sum += f(x);
		x += h;
	}
	return h * sum;
}
double right_rectangle(double a, double b, unsigned int n)
{
	double h, x, sum = 0;

	h = (b - a) / n;
	x = a + h;

	for (int k = 0; k <= n; k++)
	{
		sum += f(x);
		x += h;
	}
	return h * sum;
}
double trapezoid(double a, double b, unsigned int n)
{
	double h, x, sum = 0;

	h = (b - a) / n;
	x = a;

	for (int k = 0; k <= (n - 1); k++)
	{
		sum += (f(x) + f(x + h)) / 2;
		x += h;
	}
	return h * sum;
}
double simpson(double a, double b, unsigned int n)
{
	double h, x, sum = 0;
	unsigned int coef;

	h = (b - a) / n;
	x = a;
	for (int k = 0; k <= (n- 1); k++)
	{
		coef = (k % 2 == 0) ? 2 : 4;
		sum += coef * f(x);
 		x += h;
	}
	return h / 3 * ( sum + f(a) + f(b) );
}
