#include <iostream>
using namespace std;

#define P(A) printf("%s:%d\n", #A, A)
#define SQUARE(x) printf("the square of " #x " is %d\n", x *x)
#define CONNECT(a, b) a##b
#define MY_PRINT1(...) printf(__VA_ARGS__)
#define MY_PRINT2(fmt, ...) printf(fmt, ##__VA_ARGS__)

int main(int argc, const char *argv[])
{
	int a = 1, b = 2, ab = 3;
	P(a);
	P(a + b);
	SQUARE(4);
	MY_PRINT1("i=%d,j=%d\n");
	MY_PRINT2("iiiiiii\n");
	MY_PRINT1("ab=%d\n", CONNECT(a, b));
	
	return 0;
}
