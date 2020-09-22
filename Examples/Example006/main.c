/*FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <string.h>
#include "basic_io.h"

#define N 5
#define ARRSIZE(arr) (sizeof(s_arr)/sizeof(*(s_arr)))

int compareR(const void* a, const void* b);
int compareA(const void* a, const void* b);
	
int n;
int r =0;

int i;
int a=0;
float f;

float**s_arr;
int num=1;
float arv [N];  

int rands [N];
const char* pcTextForPeriodicTask = " ";   

/* The task functions. */
float getRandoms(int lower, int upper, int count);
void swap_rows(float **array, int row1, int row2) ;


void vTaskCode( void *pvParameters );
void vTaskCode1( void *pvParameters );
void vDeleteCode( void *pvParameters );

xTaskHandle xHandle0 ;
xTaskHandle xHandle1;
xTaskHandle hand [N];
char e_arr [5] = "Task";
char e = '0' ;
int ch = 0 ;

int main(void)
{
	
	float pr;
	int safe_mode = 1;
	
	float sum_cpu=0;
	int  i, j, z, l,d,k,e;
	srand(1);
	n = getRandoms(2, N, 1);
	
		//dynamic array	
	s_arr = (float**)malloc(n * sizeof(float*));
	for (i = 0; i < n; i++)
		s_arr[i] = (float*)malloc(7 * sizeof(float));
	
	for (i = 0; i < n; i++)
	{

		s_arr[i][0] = getRandoms(0, 15, 1); //a
		s_arr[i][1] = getRandoms(1, 8, 1); //c
		if (safe_mode) {
			s_arr[i][2] = getRandoms((3 * s_arr[i][1]), (17 * s_arr[i][1]), 1); //p  safe mode

		}
		else {

			s_arr[i][2] = getRandoms((3 * s_arr[i][1]), (10 * s_arr[i][1]), 1); //p  no gurantee mode
		}

	}

	// task1...............................................................

	for (z = 0; z < n; z++)
	{
		s_arr[z][3] = s_arr[z][1] / s_arr[z][2]; //CPU utilisation
		s_arr[z][4] = 1 / s_arr[z][2]; // rate
		sum_cpu += s_arr[z][3];
	}

	for (j = 0; j < n; j++)
	{
		printf(" a,%f ", s_arr[j][0]);
		printf(" c,%f ", s_arr[j][1]);
		printf(" p,%f ", s_arr[j][2]);
		printf(" cpu,%f ", s_arr[j][3]);
		printf(" rate,%f \n", s_arr[j][4]);

	}

	printf(" summation,%f \n", sum_cpu);
	
	if(sum_cpu <0.7){

	qsort(s_arr, n , sizeof(s_arr[0]), compareR);
	
	 pr = 1.0;
	for (d = 0; d < n; d++)
	{
	 	s_arr[d][5] = pr;
		pr++;
	}

	printf(" after sorting on rate \n");

	for (l = 0; l < n; l++)
	{
		printf(" a,%f ", s_arr[l][0]);
		printf(" c,%f ", s_arr[l][1]);
		printf(" p,%f ", s_arr[l][2]);
		printf(" cpu,%f ", s_arr[l][3]);
		printf(" rate,%f ", s_arr[l][4]);
		printf(" prio,%f \n", s_arr[l][5]);
		
	}
	
		qsort(s_arr,  n , sizeof(s_arr[0]), compareA);
	
 	  printf(" after sorting on arriv \n");

	
		for (e = 0; e < n; e++)
	{
	 	s_arr[e][6] = e+1.0;
	}
	
	
	for (k = 0; k < n; k++)
	{
		printf(" a,%f ", s_arr[k][0]);
		printf(" c,%f ", s_arr[k][1]);
		printf(" p,%f ", s_arr[k][2]);
		printf(" cpu,%f ", s_arr[k][3]);
		printf(" rate,%f ", s_arr[k][4]);
		printf(" prio,%f ", s_arr[k][5]);
		printf(" task_num,%f \n", s_arr[k][6]);
		
	}
		
	
		
	xTaskCreate( vTaskCode, "General_Task", configMINIMAL_STACK_SIZE, NULL,6, &xHandle0);
  xTaskCreate( vDeleteCode, "D_Task", configMINIMAL_STACK_SIZE, NULL,6, &xHandle1);


	vTaskStartScheduler();
	
	} else 
		{
			printf("ERROR! Ucpu > 0.7 ");
		}
	
}
 

float getRandoms(int lower, int upper, int count)
{
	int i;
	float num;
	for (i = 0; i < count; i++) {
		num = (rand() % (upper - lower + 1)) + lower;

	}
	return(num);
}


void vTaskCode( void *pvParameters )
{
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
 
	
 for( ;; )
 {
	   
	   char result[50];
	 
	   sprintf(result, "%d", num);
	
	  	    f = s_arr[0][0]; 
	   if(a!=0)
			 {
         f = s_arr[a][0]- s_arr[a-1][0];
	     }
			e_arr[0] = 'T'; 
			e_arr[1] = 'A'; 
			e_arr[2] = 'S'; 
			e_arr[3] = 'K'; 
      e_arr[4] = e;
			hand[a] = e_arr;
			 
			 vTaskDelayUntil(&xLastWakeTime,(f/portTICK_RATE_MS));			 

			 xTaskCreate( vTaskCode1, e_arr , configMINIMAL_STACK_SIZE, (void*) (int)s_arr[a][6] ,(int)s_arr[a][5], &hand[a]  );
			 


	    r++;
	    num++;
	    a++;
			e = e+1;
			   if( r==n )
				 { 
	         vTaskDelete( xHandle0 );
			   }
 }
}


void vTaskCode1( void *pvParameters )
	{
		portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
		i = (int) pvParameters;
		for( ;; )
		{
		  int j;
			int prio = uxTaskPriorityGet(NULL);
	
			for(j=0;j<n;j++)
			{
				if(prio== (int)s_arr[j][5])
					{
						 printf(" task number %f is running \n", s_arr[j][6]);
				  	 vTaskDelayUntil(&xLastWakeTime,(s_arr[j][2]/portTICK_RATE_MS));
						 
				  }
			}
  }
}


void vDeleteCode( void *pvParameters )
	{
		int count =0;
		int g;
		int new_pr = 0;
		int o;
		portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
		
		for( ;; )
		{
			
			int rand = getRandoms(1, n, 1);
			vTaskDelayUntil(&xLastWakeTime,(100/portTICK_RATE_MS));
			for(g = 0; g < N ; g++ )
			{
				if(rand == rands[g])
				{
					ch = 1;
				}
			}
				if(ch==0)
				{
					printf(" task number %f is deleted \n", s_arr[rand-1][6]);	
					vTaskDelete( hand[rand-1] );
					rands[count] = rand;
					count++;
					ch = 0;
					
					swap_rows( s_arr, rand-1 , n-1) ;
					n--;
					
							
					qsort(s_arr, n , sizeof(s_arr[0]), compareR);
					
					  new_pr = 1.0;
						for (o = 0; o < n; o++)
								{
										s_arr[o][5] = new_pr;
									  vTaskPrioritySet(hand[o],new_pr);
										new_pr++;
								}
					 printf(" after deleting \n");

					for (o = 0; o < n; o++)
							{
								printf(" a,%f ", s_arr[o][0]);
								printf(" c,%f ", s_arr[o][1]);
								printf(" p,%f ", s_arr[o][2]);
								printf(" cpu,%f ", s_arr[o][3]);
								printf(" rate,%f ", s_arr[o][4]);
								printf(" prio,%f ", s_arr[o][5]);
								printf(" task_num,%f \n", s_arr[o][6]);
							}
							
					vTaskDelayUntil(&xLastWakeTime,(100/portTICK_RATE_MS));
				}
		}
}




int compareR (const void * a, const void * b) {

  const float * const *z = a;
  const float * const *y = b;
  const float k = (*z+4)[0];
  const float m = (*y+4)[0];
  return k > m ? 1 : k < m ? -1 : 0;
}

int compareA (const void * a, const void * b) {

  const float * const *z = a;
  const float * const *y = b;
  const float k = (*z)[0];
  const float m = (*y)[0];
  return k > m ? 1 : k < m ? -1 : 0;
}

void swap_rows(float **array, int row1, int row2) {
    float *temp = array[row1];
    array[row1] = array[row2];
    array[row2] = temp;
}