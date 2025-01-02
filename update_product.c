#include "inventory.h"

int updateProduct(void)
{
    int id;
    printf("Enter product ID to update: ");
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
            printf("Current product details:\n");
            printf("Name: %s\nCategory: %s\nQuantity: %d\nPrice: $%.2f\n\n",
                   inventory[i].name, getCategoryName(inventory[i].category_id),
                   inventory[i].quantity, inventory[i].price);

            // Update name
            printf("Enter new name (or press Enter to keep current): ");
            char tempName[MAX_NAME_LENGTH];
            if (fgets(tempName, MAX_NAME_LENGTH, stdin) != NULL &&
                tempName[0] != '\n')
            {
                tempName[strcspn(tempName, "\n")] = 0;
                if (validateString(tempName, MAX_NAME_LENGTH))
                {
                    strcpy(inventory[i].name, tempName);
                }
                else
                {
                    printf("Error: Invalid name!\n");
                    return 0;
                }
            }

            // Update category
            printf("Enter new category (or press Enter to keep current): ");
            char tempCategory[MAX_CATEGORY_LENGTH];
            if (fgets(tempCategory, MAX_CATEGORY_LENGTH, stdin) != NULL &&
                tempCategory[0] != '\n')
            {
                tempCategory[strcspn(tempCategory, "\n")] = 0;
                if (validateString(tempCategory, MAX_CATEGORY_LENGTH))
                {
                    strcpy(getCategoryName(inventory[i].category_id), tempCategory);
                }
                else
                {
                    printf("Error: Invalid category!\n");
                    return 0;
                }
            }

            // Update quantity
            printf("Enter new quantity (0-10000, or -1 to keep current): ");
            int tempQuantity;
            if (scanf("%d", &tempQuantity) != 1)
            {
                printf("Error: Invalid input!\n");
                clearInputBuffer();
                return 0;
            }
            if (tempQuantity != -1)
            {
                if (validatePositiveInt(tempQuantity))
                {
                    inventory[i].quantity = tempQuantity;
                }
                else
                {
                    printf("Error: Invalid quantity!\n");
                    clearInputBuffer();
                    return 0;
                }
            }

            // Update price
            printf("Enter new price ($0.01-$10000.00, or -1 to keep current): $");
            float tempPrice;
            if (scanf("%f", &tempPrice) != 1)
            {
                printf("Error: Invalid input!\n");
                clearInputBuffer();
                return 0;
            }
            if (tempPrice != -1)
            {
                if (validatePositiveFloat(tempPrice))
                {
                    inventory[i].price = tempPrice;
                }
                else
                {
                    printf("Error: Invalid price!\n");
                    clearInputBuffer();
                    return 0;
                }
            }

            printf("Product updated successfully!\n");
            return 1;
        }
    }

    printf("Product not found!\n");
    return 0;
}
