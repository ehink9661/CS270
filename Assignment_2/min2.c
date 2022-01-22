/* min2.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 3 October, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the minimum value function for assigment 2, when the array
 * is declaired within main
 *--------------------------------------------------------------------
 */

#include <stdio.h>

void min(int arr[]){
    int i = 0;
    int min;
    min = arr[0];
    while(arr[i+1] != '\0'){ /* find end of array if size unknown */
        if (min > arr[i]){ /* +1 avoids error from reading empty memory */
            min = arr[i];
        }
        i++;
    }
    printf("Min Value in Array: %d\n", min);
}