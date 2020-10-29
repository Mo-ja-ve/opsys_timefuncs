#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

#include <math.h>

#define NO_ITERATIONS 1000000
#define NANOSECONDS_PER_SECOND 1000000000
#define REASONABLE_REPITIONS 100000//  new test number

typedef struct timespec timespec;

int dummyfunc(int x)
{
   int y=10;
   y=y+x;

   return y;
}

/* return the number of nanoseconds between two timestamps */
unsigned long diff(timespec start, timespec end)
{
        timespec temp;
        if ((end.tv_nsec-start.tv_nsec)<0) {
                temp.tv_sec = end.tv_sec-start.tv_sec-1;
                temp.tv_nsec = NANOSECONDS_PER_SECOND+end.tv_nsec-start.tv_nsec;
        } else {
                temp.tv_sec = end.tv_sec-start.tv_sec;
                temp.tv_nsec = end.tv_nsec-start.tv_nsec;
        }

        return (temp.tv_sec * NANOSECONDS_PER_SECOND + temp.tv_nsec);
}

double mean_syscall( double AV_syscall[]){

  double sum = 0;

  for(int i = 0; i < REASONABLE_REPITIONS; i++){

    sum += AV_syscall[i];

  }
  return (sum / REASONABLE_REPITIONS);
}

double mean_proccall( double AV_proccall[]){

  double sum = 0;

  for(int i = 0; i < REASONABLE_REPITIONS; i++){

    sum += AV_proccall[i];

  }
  return (sum / REASONABLE_REPITIONS);
}

double SD_syscall(double AV_syscall, double mean_sys){

  double SD_sys = 0.0;

  for(int i = 0; i < REASONABLE_REPITIONS; i++){
    SD_sys += pow(AV_syscall[i] - mean_sys, 2);
  }

  return sqrt(SD_sys / REASONABLE_REPITIONS);
}



int main()
{
        timespec time1, time2;
        double average_syscall, average_proccall;
        int a;
        double AV_syscall[REASONABLE_REPITIONS];
        double AV_proccall[REASONABLE_REPITIONS];

        //clock_gettime(CLOCK_MONOTONIC, &time1);

        printf("Average syscall time written below \n\n");
        printf("Average syscall time written below \n\n");
        printf("Average syscall time written below \n\n");

        for (int i = 0; i< REASONABLE_REPITIONS; i++){// new loop
            double temp = 0;
            clock_gettime(CLOCK_MONOTONIC, &time1);
            //a = getpid();
            //a = getpid();
            a = getpid();
            clock_gettime(CLOCK_MONOTONIC, &time2);
            temp = (double)diff(time1,time2)/(double)REASONABLE_REPITIONS;

            AV_syscall[i] = temp;
        }

        for (int i = 0; i<REASONABLE_REPITIONS; i++){
            printf("\n\n%lf", AV_syscall[i]);
        }

        /*
        for (int i = 0; i< NO_ITERATIONS; i++)// old loop
            a = getpid();
            */

        /*
        clock_gettime(CLOCK_MONOTONIC, &time2);
        average_syscall =  (double)diff(time1,time2)/(double)NO_ITERATIONS;

        printf("Average syscall time: %lf\n", average_syscall);
        */

        printf("Average procedure call time written below \n\n");
        printf("Average procedure call time written below \n\n");
        printf("Average procedure call time written below \n\n");


        for (int i = 0; i< REASONABLE_REPITIONS; i++){
          double temp = 0;
          clock_gettime(CLOCK_MONOTONIC, &time1);
          a = dummyfunc(20);
          clock_gettime(CLOCK_MONOTONIC, &time2);
          temp = average_proccall =  (double)diff(time1,time2)/(double)REASONABLE_REPITIONS;

          AV_proccall[i] = temp;
        }

        for (int i = 0; i<REASONABLE_REPITIONS; i++){
            printf("\n\n%lf", AV_proccall[i]);
        }

        double mean_sys = mean_syscall(AV_syscall);
        double mean_proc = mean_proccall(AV_proccall);

        printf("\n\nmean syscall time: %lf\n\n",mean_sys);
        printf("\n\nmean proccall time: %lf\n\n",mean_proc);

        //printf("Average procedure call time: %lf\n", average_proccall);


        double SD_sys = SD_syscall(AV_syscall, mean_sys);
        printf("\n\n\n\n\nSTANDARD DEVIATION FOR SYSCALL:  %lf", SD_sys);
        // double SD_procc = SD_proccall(AV_proccall, mean_proc);
        return 0;
}
