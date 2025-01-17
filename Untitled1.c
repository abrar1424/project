#include <stdio.h>

int main() {
    int a, b, c, d;


    printf("Enter four distinct integers: ");
    scanf("%d %d %d %d", &a, &b, &c, &d);


    int largest = a;
    int smallest = a;

    if (b > largest) largest = b;
    if (c > largest) largest = c;
    if (d > largest) largest = d;

    if (b < smallest) smallest = b;
    if (c < smallest) smallest = c;
    if (d < smallest) smallest = d;

    printf("Largest: %d\n", largest);
    printf("Smallest: %d\n", smallest);

    return 0;
}
