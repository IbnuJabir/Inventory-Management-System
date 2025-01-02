#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FACTORY_PRODUCT 1000
#define MAX_CATEGORIES 100
#define MAX_NAME_LENGTH 30
#define MAX_CATEGORY_LENGTH 30

typedef struct
{
    int id;
    char name[MAX_CATEGORY_LENGTH];
} Category;

typedef struct
{
    int id;
    char name[MAX_NAME_LENGTH];
    int category_id;
    int quantity;
    float price;
} InventoryProduct;

// Global variables
extern InventoryProduct inventory[MAX_FACTORY_PRODUCT];
extern Category categories[MAX_CATEGORIES];
extern int FactoryProductCount;
extern int CategoryCount;

// Function prototypes
void displayMenu(void);
int addProduct(void);
int addCategory(void);
int updateProduct(void);
int searchProduct(void);
void listAllProducts(void);
void listAllCategories(void);
int saveData(void);
int loadData(void);
void clearInputBuffer(void);
int validateString(const char *str, size_t maxLength);
int validatePositiveInt(int num);
int validatePositiveFloat(float price);
void displayProductHeader(void);
void displayProductRow(const InventoryProduct *product);
char *getCategoryName(int category_id);
int selectCategory(void);

#endif /* INVENTORY_H */