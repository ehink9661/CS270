/* sum_avg.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 3 October, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the summing and averaging function for assigment 2
 *--------------------------------------------------------------------
 */

#include <stdio.h>

extern int arr[5]; /* looks for external array, gloabl var in main */

void sum_avg(){
    int i = 0;
    int sum = 0;
    double avg;
    while(arr[i] != '\0'){ /* find end of array if size unknown */
        sum += arr[i];
        i++;
    }
    avg = (double)sum/i; /* forces decimal arithmetic */
    printf("Sum of Array Values: %d\n", sum);
    printf("Average of Array Values: %f\n", avg);
}