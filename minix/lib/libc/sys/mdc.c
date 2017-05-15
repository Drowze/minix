#include <lib.h>

int mdc(int n1, int n2) {
	message m;
	m.m1_i1 = n1;
	m.m1_i2 = n2;
	return _syscall(PM_PROC_NR, MDC, &m);
}
