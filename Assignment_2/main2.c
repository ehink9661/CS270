/* main2.c
 *
 * CS 270-01.Bolden..........Ethan Hinkle
 * 3 October, 2021........hink9661@vandals.uidaho.edu
 *
 * This is the main() for assigment 2, with the array local to main
 *--------------------------------------------------------------------
 */

#include <stdio.h>

void sum_avg(int arr[]);
void max(int arr[]);
void min(int arr[]);

int main(){
    int arr[5] = {1, 27, -3, 256, -16};
    sum_avg(arr);
    max(arr);
    min(arr);
    return 0;
}
