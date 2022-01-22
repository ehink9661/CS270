/* max.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 3 October, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the maximum value function for assigment 2
 *--------------------------------------------------------------------
 */

#include <stdio.h>

extern int arr[5]; /* looks for external array, gloabl var in main */

void max(){
    int i = 0;
    int max;
    max = arr[0];
    while(arr[i] != '\0'){ /* find end of array if size unknown */
        if (max < arr[i]){
            max = arr[i];
        }
        i++;
    }
    printf("Max Value in Array: %d\n", max);
}