#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include "../include/lu_test.h"
#include <stdbool.h>

int main(int argc, char const *argv[])
{
	test_all_lu_functions(0);
	return 0; 
//return 0;
}