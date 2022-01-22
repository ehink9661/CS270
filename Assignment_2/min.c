/* min.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 3 October, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the minimum value function for assigment 2
 *--------------------------------------------------------------------
 */

#include <stdio.h>

extern int arr[5]; /* looks for external array, gloabl var in main */

void min(){
    int i = 0;
    int min;
    min = arr[0];
    while(arr[i] != '\0'){ /* find end of array if size unknown */
        if (min > arr[i]){
            min = arr[i];
        }
        i++;
    }
    printf("Min Value in Array: %d\n", min);
}