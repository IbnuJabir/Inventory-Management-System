// main.c
#include "inventory.h"

InventoryProduct inventory[MAX_FACTORY_PRODUCT];
int FactoryProductCount = 0;

int main(void)
{
  int choice;

  if (!loadData())
  {
    printf("Failed to load data. Starting with empty inventory.\n");
  }

  do
  {
    displayMenu();
    printf("Enter your choice (1-7): ");
    if (scanf("%d", &choice) != 1)
    {
      printf("Invalid input. Please enter a number.\n");
      clearInputBuffer();
      continue;
    }
    clearInputBuffer();

    switch (choice)
    {
    case 1:
      if (!addCategory())
      {
        printf("Failed to add category.\n");
      }
      break;
    case 2:
      if (!addProduct())
      {
        printf("Failed to add product.\n");
      }
      break;
    case 3:
      if (!updateProduct())
      {
        printf("Failed to update product.\n");
      }
      break;
    case 4:
      if (!searchProduct())
      {
        printf("Failed to search product.\n");
      }
      break;
    case 5:
      listAllProducts();
      break;
    case 6:
      listAllCategories();
      break;
    case 7:
      if (!saveData())
      {
        printf("Failed to save data.\n");
        return 1;
      }
      printf("Changes have been saved. Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please enter a number between 1 and 7.\n");
    }
  } while (choice != 7);

  return 0;
}