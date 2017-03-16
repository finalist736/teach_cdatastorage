#ifndef DATASTORAGE_H
#define DATASTORAGE_H

typedef struct Prdct {
    char *art, *name, *desc;
    int price, count;
} Product;

typedef struct DataStorage {
    int len, cap;
    Product **storage;
} DynamicArray;


// Storage
DynamicArray *StorageNew();
void StorageAdd(DynamicArray *, Product *);
void StorageDisplay(const DynamicArray *);
void StorageSave(const char* filename, const DynamicArray* s);
DynamicArray *StorageLoad(const char *filename);

// Products
Product *ProductNew(const char *art, const char *name, const char *desc, int price, int count);


#endif // DATASTORAGE_H
