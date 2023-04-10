#include "nmsp_test_proj-pch.h"


int main(int argc, char* argv[])
{
	int* p = NMSP_ALLOC_T(p, 10);
	p[0] = 10;

	return 0;
}