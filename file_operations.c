#include "inventory.h"

int saveData(void)
{
    // Save categories
    FILE *fp = fopen("categories.txt", "w");
    if (fp == NULL)
    {
        printf("Error: Could not open categories file for writing!\n");
        return 0;
    }

    for (int i = 0; i < CategoryCount; i++)
    {
        fprintf(fp, "%d\n%s\n", categories[i].id, categories[i].name);
    }
    fclose(fp);

    // Save products
    fp = fopen("inventory.txt", "w");
    if (fp == NULL)
    {
        printf("Error: Could not open inventory file for writing!\n");
        return 0;
    }

    for (int i = 0; i < FactoryProductCount; i++)
    {
        fprintf(fp, "%d\n%s\n%d\n%d\n%.2f\n",
                inventory[i].id,
                inventory[i].name,
                inventory[i].category_id,
                inventory[i].quantity,
                inventory[i].price);
    }
    fclose(fp);
    return 1;
}

int loadData(void)
{
    // Load categories
    FILE *fp = fopen("categories.txt", "r");
    if (fp != NULL)
    {
        CategoryCount = 0;
        while (!feof(fp) && CategoryCount < MAX_CATEGORIES)
        {
            Category category;
            if (fscanf(fp, "%d\n", &category.id) != 1)
                break;
            if (fgets(category.name, MAX_CATEGORY_LENGTH, fp) == NULL)
                break;
            category.name[strcspn(category.name, "\n")] = 0;
            categories[CategoryCount++] = category;
        }
        fclose(fp);
    }

    // Load products
    fp = fopen("inventory.txt", "r");
    if (fp == NULL)
    {
        return 1; // No products file yet - not an error
    }

    FactoryProductCount = 0;
    while (!feof(fp) && FactoryProductCount < MAX_FACTORY_PRODUCT)
    {
        InventoryProduct product;
        if (fscanf(fp, "%d\n", &product.id) != 1)
            break;
        if (fgets(product.name, MAX_NAME_LENGTH, fp) == NULL)
            break;
        product.name[strcspn(product.name, "\n")] = 0;
        if (fscanf(fp, "%d\n%d\n%f\n",
                   &product.category_id,
                   &product.quantity,
                   &product.price) != 3)
            break;
        inventory[FactoryProductCount++] = product;
    }
    fclose(fp);
    return 1;
}
