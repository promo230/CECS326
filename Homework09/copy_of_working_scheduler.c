/*
   The parser piece for the scheduler assignment
*/
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
/* You will need the integer queue */
#include "IQueue.h"
int main(int argc, char* argv[])
{
  int fd;
  FILE *f;
  char line[80];
  int start_time, duration;
  int i;

  struct process_struct
  {
    int process_id;
    int start_time;
    int duration;
    int time_left;
  };
  struct process_struct process_list[80];
  int process_count;

  if (argc !=2)
  {
    printf("usage a.out file_name\n");
    return 0;
  };
  f = fopen(argv[1],"r");
  process_count = 0;

  while(fgets(line,sizeof(line),f) != NULL)
  {
    sscanf(line, "%d %d", &start_time, &duration);
    process_list[process_count].process_id = process_count;
    process_list[process_count].start_time = start_time;
    process_list[process_count].duration = duration;
    process_list[process_count].time_left = duration;
    process_count++ ;
  }
/*  for (i = 0 ; i < process_count ; i++)
  {
      printf("process %d, start  %d, duration %d, left %d \n",
      process_list[i].process_id,
      process_list[i].start_time,
      process_list[i].duration,
      process_list[i].time_left);
  }
*/


  int current_time = 0;
  int process = 0;
  int process_completed = 0;

  printf("Time  Action\n");
  //IQueueStore IQueueRetrieve IQueueSize
    for(i = 0; i < process_count; i++){
        if(process_list[i].start_time == current_time){
                IQueueStore(process_list[i].process_id);
        }

        if(IQueueSize() == 0){
                printf("%d      idle\n", current_time);
        }
        else{
                process = IQueueRetrieve();
                printf("%d      Process %d\n", current_time, process);
                process_list[i].time_left -= 5;
                if(process_list[i].time_left > 0){
                        IQueueStore(process);
                        process_completed +=1;
                }
        }
        current_time += 5;
  }  





  printf("DONE\n");
  close(fd);
};
