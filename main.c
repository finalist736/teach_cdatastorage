#include <stdio.h>
#include <stdlib.h>
#include "datastorage.h"

int main(int argc, char *argv[])
{
    //DynamicArray * array = StorageNew();

    //int price, count;

    DynamicArray * array = StorageLoad("products.bin");

//    for (int i=0; i<1001; i++)
//    {
//        price = rand() % 100;
//        count = rand() % 20;
//        Product * p = ProductNew("a15", "kofta", "ochen teplaya kofta", price, count);
//        StorageAdd(array, p);
//    }

    StorageDisplay(array);
    //StorageSave("products.bin", array);

    printf("done!\n");
    return 0;
}
