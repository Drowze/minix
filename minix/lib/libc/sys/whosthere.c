#include <lib.h>

int whosthere() {
	message m;
	_syscall(PM_PROC_NR, WHOSTHERE, &m);

	return 0;
}
