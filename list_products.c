#include "inventory.h"

void listAllProducts(void)
{
    if (FactoryProductCount == 0)
    {
        printf("No products in the inventory!\n");
        return;
    }

    printf("\n=================================== Product List ===================================\n");
    printf("| %-5s | %-20s | %-20s | %-10s | %-10s |\n",
           "ID", "Name", "Category", "Quantity", "Price");
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < FactoryProductCount; i++)
    {
        printf("| %04d | %-20s | %-20s | %-10d | $%-9.2f |\n",
               inventory[i].id, inventory[i].name, getCategoryName(inventory[i].category_id),
               inventory[i].quantity, inventory[i].price);
    }
    printf("====================================================================================\n");
}
