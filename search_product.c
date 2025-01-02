#include "inventory.h"

int searchProduct(void)
{
    int id;
    printf("Enter product ID to search: ");
    if (scanf("%d", &id) != 1 || !validatePositiveInt(id))
    {
        printf("Error: Invalid product ID!\n");
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer();

    for (int i = 0; i < FactoryProductCount; i++)
    {
        if (inventory[i].id == id)
        {
            printf("\n=== Product Details ===\n");
            printf("ID: %04d\n", inventory[i].id);
            printf("Name: %s\n", inventory[i].name);
            printf("Category: %s\n", getCategoryName(inventory[i].category_id));
            printf("Quantity: %d\n", inventory[i].quantity);
            printf("Price: $%.2f\n", inventory[i].price);
            return 1;
        }
    }

    printf("Product not found!\n");
    return 0;
}