#include "datastorage.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_CAPACITY 1000

DynamicArray *StorageNew()
{
    DynamicArray *init = (DynamicArray*)malloc(sizeof(DynamicArray));
    init->len = 0;
    init->cap = 0;
    init->storage = NULL;
    return init;
}



Product *ProductNew(const char *art, const char *name, const char *desc, int price, int count)
{
    Product *init = (Product *)malloc(sizeof(Product));
    init->price = price;
    init->count = count;

    int len = strlen(art);
    init->art = (char*)malloc(len + 1);
    strcpy(init->art, art);

    len = strlen(name);
    init->name = (char*)malloc(len + 1);
    strcpy(init->name, name);

    len = strlen(desc);
    init->desc = (char*)malloc(len + 1);
    strcpy(init->desc, desc);
    return init;
}

void StorageAdd(DynamicArray *s, Product *p)
{
    // ensure free space available
    if (s->cap == s->len)
    {
        s->cap += DEFAULT_CAPACITY;
        Product ** tmp = (Product **)malloc(sizeof(Product*) * s->cap);
        for (int i=0; i<s->len; i++)
        {
            tmp[i] = s->storage[i];
        }
        if (s->storage != NULL)
        {
            free(s->storage);
        }
        s->storage = tmp;
    }
    s->storage[s->len++] = p;
}

void StorageDisplay(const DynamicArray *s)
{
    printf("cap: %d; len: %d\n", s->cap, s->len);
    for (int i=0; i<s->len; i++)
    {
        printf("{%s, %d}\n", s->storage[i]->art, s->storage[i]->price);
    }
}

void StorageSave(const char *filename, const DynamicArray *s)
{
    FILE * f = fopen(filename, "wb");
    if (f == NULL)
    {
        return;
    }
    int len = 0;
    for (int i=0; i<s->len; i++)
    {
        Product * tmp = s->storage[i];
        len = strlen(tmp->art);
        fwrite(&len, sizeof(len), 1, f);
        fwrite(tmp->art, sizeof(char), len, f);
        len = strlen(tmp->name);
        fwrite(&len, sizeof(len), 1, f);
        fwrite(tmp->name, sizeof(char), len, f);
        len = strlen(tmp->desc);
        fwrite(&len, sizeof(len), 1, f);
        fwrite(tmp->desc, sizeof(char), len, f);
        fwrite(&tmp->price, sizeof(tmp->price), 1, f);
        fwrite(&tmp->count, sizeof(tmp->count), 1, f);
    }
    fclose(f);
}

DynamicArray *StorageLoad(const char *filename)
{
    DynamicArray *array = StorageNew();
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        return NULL;
    }
    int readed = 0;
    int len;
    while (!feof(f)) {
        Product * tmp = (Product*)malloc(sizeof(Product));
        readed = fread(&len, sizeof(len), 1, f);
        if (readed == 0)
        {
            free(tmp);
            continue;
        }
        tmp->art = (char*)malloc(len + 1);
        fread(tmp->art, sizeof(char), len, f);
        tmp->art[len] = 0;

        fread(&len, sizeof(len), 1, f);
        tmp->name = (char*)malloc(len + 1);
        fread(tmp->name, sizeof(char), len, f);
        tmp->name[len] = 0;

        fread(&len, sizeof(len), 1, f);
        tmp->desc = (char*)malloc(len + 1);
        fread(tmp->desc, sizeof(char), len, f);
        tmp->desc[len] = 0;

        fread(&tmp->price, sizeof(tmp->price), 1, f);
        fread(&tmp->count, sizeof(tmp->count), 1, f);

        StorageAdd(array, tmp);
    }


    fclose(f);
    return array;
}










