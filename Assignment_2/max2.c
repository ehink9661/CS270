/* max2.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 3 October, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the maximum value function for assigment 2, when the array
 * is declaired within main
 *--------------------------------------------------------------------
 */

#include <stdio.h>

void max(int arr[]){
    int i = 0;
    int max;
    max = arr[0];
    while(arr[i+1] != '\0'){ /* find end of array if size unknown */
        if (max < arr[i]){ /* +1 avoids error of reading to far */
            max = arr[i];
        }
        i++;
    }
    printf("Max Value in Array: %d\n", max);
}