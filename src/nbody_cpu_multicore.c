#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
#include "timer.h"

#ifdef PAPI
#include<papi.h>
#endif

#define SOFTENING 1e-9f

typedef struct { float x, y, z, vx, vy, vz; } Body;

void randomizeBodies(float *data, int n) {
  for (int i = 0; i < n; i++) {
    data[i] = 2.0f * (rand() / (float)RAND_MAX) - 1.0f;
  }
}

void bodyForce(Body *p, float dt, int n) {
#pragma omp parallel for schedule(dynamic)
  for (int i = 0; i < n; i++) { 
    float Fx = 0.0f; float Fy = 0.0f; float Fz = 0.0f;

    for (int j = 0; j < n; j++) {
      float dx = p[j].x - p[i].x;
      float dy = p[j].y - p[i].y;
      float dz = p[j].z - p[i].z;
      float distSqr = dx*dx + dy*dy + dz*dz + SOFTENING;
      float invDist = 1.0f / sqrtf(distSqr);
      float invDist3 = invDist * invDist * invDist;

      Fx += dx * invDist3; Fy += dy * invDist3; Fz += dz * invDist3;
    }

    p[i].vx += dt*Fx; p[i].vy += dt*Fy; p[i].vz += dt*Fz;
  }
}

int main(const int argc, const char** argv) {
  FILE *datafile;  
  int nBodies = 30000;
  int nthreads = 2;

  if (argc > 1) nBodies = atoi(argv[1]);
  if (argc > 2) nthreads = atoi(argv[2]);

  const float dt = 0.01f; // time step
  const int nIters = 20;  // simulation iterations

  int bytes = nBodies*sizeof(Body);
  float *buf = (float*)malloc(bytes);
  Body *p = (Body*)buf;

  omp_set_num_threads(nthreads);
  randomizeBodies(buf, 6*nBodies); // Init pos / vel data

  double totalTime = 0.0;

  //PAPI
  long_long *values;
  int Events[] = {PAPI_TLB_DM, PAPI_BR_MSP, PAPI_BR_INS, PAPI_RES_STL};
  int num_events = sizeof(Events) / sizeof(int);
  PAPI_start_counters(Events, num_events);
  event_name = (char*)malloc(128);

  values = (long_long*)malloc(num_events*sizeof(long_long));

  /* ------------------------------*/
  /*     MAIN LOOP                 */
  /* ------------------------------*/
  for (int iter = 1; iter <= nIters; iter++) {
    printf("iteration:%d\n", iter);
    
    StartTimer();

    bodyForce(p, dt, nBodies);           // compute interbody forces

    for (int i = 0 ; i < nBodies; i++) { // integrate position
      p[i].x += p[i].vx*dt;
      p[i].y += p[i].vy*dt;
      p[i].z += p[i].vz*dt;
    }

    const double tElapsed = GetTimer() / 1000.0;
    if (iter > 1) {                      // First iter is warm up
      totalTime += tElapsed; 
    }
  }

  PAPI_stop_counters(values, num_events);

  double avgTime = totalTime / (double)(nIters-1); 

  printf("avgTime: %f   totTime: %f \n", avgTime, totalTime);

  free(buf);
}