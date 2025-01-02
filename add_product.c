#include "inventory.h"

void displayProductHeader(void)
{
    printf("\n=== Product Details ===\n");
    printf("%-5s %-20s %-20s %-10s %-10s\n",
           "ID", "Name", "Category", "Quantity", "Price");
    printf("------------------------------------------------------------\n");
}

void displayProductRow(const InventoryProduct *product)
{
    printf("%-5d %-20s %-20s %-10d $%-10.2f\n",
           product->id,
           product->name,
           getCategoryName(product->category_id),
           product->quantity,
           product->price);
}

int addProduct(void)
{
    if (FactoryProductCount >= MAX_FACTORY_PRODUCT)
    {
        printf("Error: Inventory is full!\n");
        return 0;
    }

    InventoryProduct product;
    product.id = FactoryProductCount + 1; // Auto-increment ID

    // Get and validate name
    printf("Enter product name: ");
    if (fgets(product.name, MAX_NAME_LENGTH, stdin) == NULL ||
        !validateString(product.name, MAX_NAME_LENGTH))
    {
        printf("Error: Invalid product name!\n");
        return 0;
    }
    product.name[strcspn(product.name, "\n")] = 0;

    // Select or create category
    int category_id = selectCategory();
    if (category_id == -1)
    {
        printf("Error: Category selection failed!\n");
        return 0;
    }
    product.category_id = category_id;

    // Get and validate quantity
    printf("Enter quantity: ");
    if (scanf("%d", &product.quantity) != 1 ||
        !validatePositiveInt(product.quantity))
    {
        printf("Error: Invalid quantity!\n");
        clearInputBuffer();
        return 0;
    }

    // Get and validate price
    printf("Enter price: $");
    if (scanf("%f", &product.price) != 1 ||
        !validatePositiveFloat(product.price))
    {
        printf("Error: Invalid price!\n");
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer();

    // Display product details and confirm
    displayProductHeader();
    displayProductRow(&product);

    printf("\nDo you want to save this product? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    clearInputBuffer();

    if (tolower(choice) == 'y')
    {
        inventory[FactoryProductCount++] = product;
        if (!saveData())
        {
            printf("Failed to save data.\n");
            return 1;
        }
        printf("Product added successfully!\n");
        return 1;
    }

    printf("Product creation cancelled.\n");
    return 0;
}