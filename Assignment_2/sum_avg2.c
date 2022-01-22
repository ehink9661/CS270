/* sum_avg2.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 3 October, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the summing and averaging function for assigment 2, when
 * the array is local to main
 *--------------------------------------------------------------------
 */

#include <stdio.h>

void sum_avg(int arr[]){
    int i = 0;
    int sum = 0;
    double avg;
    while(arr[i+1] != '\0'){ /* find end of array if size unknown */
        sum += arr[i]; /* +1 needed to avoid reading nonexistant value */
        i++;
    }
    avg = (double)sum/i; /* forces decimal arithmetic */
    printf("Sum of Array Values: %d\n", sum);
    printf("Average of Array Values: %f\n", avg);
}