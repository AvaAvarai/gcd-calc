/*
* file: gcd.c
* author: Alice Williams
* Finds the gcd of two user-entered positive integer numbers,
* and two linear combinations that satisfy ax + by = gcd(a,b)
*/

#include <stdio.h>

#define title "[gcd calculator v1.0]"
#define prompt "input numbers (press enter after each number):"
#define uint unsigned int
#define len(x) (sizeof(x) / sizeof((x)[0]))

// custom types
typedef enum{false, true} bool;

typedef struct Tuple {
	uint a, b;
} Tuple;

typedef struct Quartet {
	int a, b, c, d;
} Quartet;

// calculate linear combinations
Quartet gcdLinearCombo(Tuple in) {
	Tuple inCopy = in;
	
	// count coefficients
	uint co[64];
	size_t i = 0;
	while (in.b != 0) {
		uint temp = in.b;
		co[i++] = in.a / in.b;
		in.b = in.a % in.b;
		in.a = temp;
	}

	// define 2x2 + 2xi matrix
	uint matrix[2][i+2];
 	
	// plug in identity matrix
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[0][1] = 0;
	matrix[1][0] = 0;

	// sliding 2x1 matrix window
	size_t j = 2;
	bool sign = false;
	while (j <= i) {
		
		// calculate matrix cells
		matrix[0][j] = matrix[0][j-2] + matrix[0][j-1] * co[j-2];
		matrix[1][j] = matrix[1][j-2] + matrix[1][j-1] * co[j-2];
		
		// flip sign
		sign = !sign;
		
		j++;
	}
	j--;

	// return final entry
	if (sign) {
		return (Quartet){matrix[0][j], -matrix[1][j], matrix[0][j]-inCopy.b, -matrix[1][j]+inCopy.a};
	}
    return (Quartet){-matrix[0][j], matrix[1][j], -matrix[0][j]+inCopy.b, matrix[1][j]-inCopy.a};
}

// iteratively apply the Euclidean algorithm
uint gcdIterative(Tuple in) {
    while (in.b != 0) {
        uint temp = in.b;
        in.b = in.a % in.b;
        in.a = temp;
    }
    return in.a;
}

// recursively apply the Euclidean algorithm
uint gcdRecursive(Tuple in) {
    if (in.b == 0) {
        return in.a;
    }
    return gcdRecursive((Tuple){in.b, in.a % in.b});
}

int main(void) {
    // introduce program and prompt user
	printf("%s\n%s\n", title, prompt);
    
	uint values[2];
	char buf[64];
	
	// get user values
	size_t i = 0;
	while (i < len(values) && fgets(buf, sizeof(buf), stdin) != NULL) {
		int value;

		if (sscanf(buf, "%d", &value) != 1) {
			fprintf(stderr, "Only numbers please.\n");
			continue;
		}

		if (value <= 0) {
			fprintf(stderr, "Only positive integers please.\n");
			continue;
		}

		values[i] = value;
		i++;	
	}

	// pack user values
	Tuple in = {values[0], values[1]};

	// gcd calculate and print
        printf("The gcd is: %d\n", gcdIterative(in));

	// calculate linear combo
	Quartet lc = gcdLinearCombo(in);

	// linear combination vectors
	printf("First solution vector: %d %d\n", lc.a, lc.b);
        printf("Sign-flipped solution: %d %d\n", lc.c, lc.d);

	return 0;
}
