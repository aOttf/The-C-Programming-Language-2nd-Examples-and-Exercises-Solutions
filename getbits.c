#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

unsigned getbits(unsigned x, int p, int n){
	return (x >> (p+1-n)) & ~!(~0 << n);
}
