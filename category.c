#include "inventory.h"

Category categories[MAX_CATEGORIES];
int CategoryCount = 0;

void listAllCategories(void)
{
    if (CategoryCount == 0)
    {
        printf("No categories available.\n");
        return;
    }

    printf("\n=== Categories ===\n");
    printf("ID    Name\n");
    printf("----------------\n");
    for (int i = 0; i < CategoryCount; i++)
    {
        printf("%-5d %s\n", categories[i].id, categories[i].name);
    }
    printf("\n");
}

int addCategory(void)
{
    if (CategoryCount >= MAX_CATEGORIES)
    {
        printf("Maximum number of categories reached!\n");
        return 0;
    }

    Category category;
    category.id = CategoryCount + 1; // Auto-increment ID

    printf("Enter category name: ");
    if (fgets(category.name, MAX_CATEGORY_LENGTH, stdin) == NULL ||
        !validateString(category.name, MAX_CATEGORY_LENGTH))
    {
        printf("Error: Invalid category name!\n");
        return 0;
    }
    category.name[strcspn(category.name, "\n")] = 0;

    // Check for duplicate category names
    for (int i = 0; i < CategoryCount; i++)
    {
        if (strcasecmp(categories[i].name, category.name) == 0)
        {
            printf("Error: Category already exists!\n");
            return 0;
        }
    }

    categories[CategoryCount++] = category;
    if (!saveData())
    {
        printf("Failed to save data.\n");
        return 1;
    }
    printf("Category added successfully!\n");
    return 1;
}

char *getCategoryName(int category_id)
{
    for (int i = 0; i < CategoryCount; i++)
    {
        if (categories[i].id == category_id)
        {
            return categories[i].name;
        }
    }
    return "Unknown";
}

int selectCategory(void)
{
    if (CategoryCount == 0)
    {
        printf("No categories available. You need to create a category first.\n");
        printf("Would you like to create a category now? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        clearInputBuffer();

        if (tolower(choice) == 'y')
        {
            if (!addCategory())
            {
                return -1;
            }
            return categories[CategoryCount - 1].id;
        }
        return -1;
    }

    listAllCategories();
    printf("\nSelect a category by ID or enter 0 to create a new category: ");
    int category_id;
    scanf("%d", &category_id);
    clearInputBuffer();

    if (category_id == 0)
    {
        if (!addCategory())
        {
            return -1;
        }
        return categories[CategoryCount - 1].id;
    }

    for (int i = 0; i < CategoryCount; i++)
    {
        if (categories[i].id == category_id)
        {
            return category_id;
        }
    }

    printf("Invalid category ID!\n");
    return -1;
}