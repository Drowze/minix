#include <stdio.h>
#include <stdlib.h>
#include <lib.h>

#include <fcntl.h>
#include <string.h>

/* O_RDONLY; // "r"
 * O_WRONLY | (O_CREAT | O_TRUNC); // "w"
 * O_WRONLY | (O_CREAT | O_APPEND); // "a"
 * O_RDWR | (O_CREAT | O_APPEND); // "a+"
 * O_RDWR | (O_CREAT | O_TRUNC); // w+
 * O_RDWR | O_CREAT; // r+
 */
#define OPEN_FILE_FLAGS (O_RDWR | O_CREAT)

/* function prototypes */
int custom_open(const char *name, int flags);
int check_arguments(char *argv[], int i); /* verify if argument is valid based on command */
int check_fd(int fd); /* verify for a valid file descriptor */

int custom_open(const char *name, int flags) {
  umask(0); // https://stackoverflow.com/questions/12489525/file-permission-issue-with-open-system-call-linux
  message m;
  memset(&m, 0, sizeof(m)); // 0s the memory space

  /* if flags contain O_CREAT, call VFS_CREAT */
  if (flags & O_CREAT) {
    m.m_lc_vfs_creat.len = strlen(name) + 1;
    m.m_lc_vfs_creat.flags = flags;
    m.m_lc_vfs_creat.mode = 0777;
    m.m_lc_vfs_creat.name = (vir_bytes)name;

    return(_syscall(VFS_PROC_NR, VFS_CREAT, &m));
  }

  /* else, call VFS_OPEN */
  _loadname(name, &m);
  m.m_lc_vfs_path.flags = flags;

  return(_syscall(VFS_PROC_NR, VFS_OPEN, &m));
}

int check_arguments(char* argv[], int i) {
  if(strcmp(argv[i], "open") == 0) {
    if(argv[i++] == NULL) {
      fprintf(stderr, "Invalid file name\n");
      exit(-1);
    }
  }
  return 0;
}

int check_fd(int fd) {
  if(fd < 0) {
    fprintf(stderr, "Invalid file descriptor\n");
    exit(-1);
  }
  return 0;
}

int main(int argc, char* argv[]) {
  int i = 0;
  int fd = -1; // file descriptor initially set to -1

  for(i = 0; i < argc; i++) {
    if(strcmp(argv[i], "open") == 0) {
      check_arguments(argv, i);
      fd = custom_open(argv[++i], OPEN_FILE_FLAGS);
    }
    else if(strcmp(argv[i], "seek") == 0) {
      printf("Implementar seek\n");
    }
    else if(strcmp(argv[i], "read") == 0) {
      printf("Implementar read\n");
    }
    else if(strcmp(argv[i], "write") == 0) {
      printf("Implementar write\n");
    }
    else if(strcmp(argv[i], "close") == 0) {
      printf("Implementar close\n");
    }
  }

  return 0;
}
