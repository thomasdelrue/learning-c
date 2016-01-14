#include <stdio.h>
#include <stdlib.h>

int global;

void func1()
{
    int local2 = 3;
    printf("Address of local2 is %p\n", &local2);
}

int times_called()
{
    static int counter = 0;
    counter++;

    printf("Address of counter is %p\n", &counter);
    return counter;
}

int main()
{
    int local = 5;
    void *p = malloc(128);
    void *p2 = malloc(64);

    printf("Address of main is %p\n", main);
    printf("Address of global is %p\n", &global);
    printf("Address of local is %p\n", &local);

    func1();
    printf("Address of p is %p\n", p);
    printf("Address of p2 is %p\n", p2);

    times_called();
    times_called();

    return 0;
}
