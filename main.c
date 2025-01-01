//Anywhere use zero-padding for the ID field.
// For example, if the ID is 0001, it should be displayed as 00001.
// The identifier for an ID would be %0Nd, where N is the total width of the number
// The identifier for a string would be %-Ns, where N is the total width of the string

#include<stdio.h>
#include<string.h>
//Limit of products in the inventory
#define MAX_FACTORY_PRODUCT 1000
//Structure to store product details
typedef struct{
//Input data
  int id;
  char name[30];
  char category[30];
  int quantity;
  float price;
} InventoryProduct;//Array to store product details

InventoryProduct inventory[MAX_FACTORY_PRODUCT];//Variable to store the number of products in the inventory
int FactoryProductCount=0;
void displayMenu();
void addProduct();
void updateProduct();
void searchProduct();
void listAllProducts();
void saveData();
void loadData();
int main(){
  int choice;
  loadData();
  do {
    displayMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
      addProduct();
      break;
    case 2:
      updateProduct();
      break;
    case 3:
      searchProduct();
      break;
    case 4:
      listAllProducts();
      break;
    case 5:
      saveData();
      printf("Changes have been saved...\n");
      break;
    
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }while (choice !=5);//Exit the program
  printf("Thank you for using the Inventory Management System!\n");
  return 0;
}

void displayMenu() {
  printf("\n===== Inventory Management System =====\n");
  printf("--------------------------------------------------\n");
  printf("| 1 | Add Product                                |\n");
  printf("|---|--------------------------------------------|\n");
  printf("| 2 | Update Product                             |\n");
  printf("|---|--------------------------------------------|\n");
  printf("| 3 | Search Product                             |\n");
  printf("|---|--------------------------------------------|\n");
  printf("| 4 | List All Products                          |\n");
  printf("|---|--------------------------------------------|\n");
  printf("| 5 | Save the changes and exit the program      |\n");
  printf("--------------------------------------------------\n");
}

void addProduct() {
  if (FactoryProductCount >= MAX_FACTORY_PRODUCT) {
    printf("Inventory is full!\n");
    return;
  }
  
  InventoryProduct product;//Create a new product object to store the input data 
  printf("\nEnter product ID: \n");
  scanf("%04d", &product.id);
  for (int i = 0; i < FactoryProductCount; i++) {
    if (inventory[i].id == product.id) {
      printf("Product ID already exists!\n");
      return;
    }
  }
  printf("Enter product name: \n");
  getchar();//Clear input buffer before reading string input using fgets function  
  fgets(product.name, sizeof(product.name), stdin);
  product.name[strcspn(product.name, "\n")] = 0;
  printf("Enter category: \n");
  fgets(product.category, sizeof(product.category), stdin);
  product.category[strcspn(product.category, "\n")] = 0;
  printf("Enter quantity: \n");
  scanf("%d", &product.quantity);
  printf("Enter price: \n$");
  scanf("%f", &product.price);
  
  inventory[FactoryProductCount++] = product;//
  printf("Product added successfully!\n");
}

void updateProduct() {
  int id;
  printf("Enter product ID to update: ");
  scanf("%04d", &id);
  
  for (int i = 0; i < FactoryProductCount; i++) {
    if (inventory[i].id == id) {
      printf("Enter new name: ");
      getchar();
      fgets(inventory[i].name, sizeof(inventory[i].name), stdin);
      inventory[i].name[strcspn(inventory[i].name, "\n")] = 0;
      printf("Enter new category: ");
      fgets(inventory[i].category, sizeof(inventory[i].category), stdin);
      inventory[i].category[strcspn(inventory[i].category, "\n")] = 0;
      printf("Enter new quantity: ");
      scanf("%d", &inventory[i].quantity);
      printf("Enter new price: ");
      scanf("%f", &inventory[i].price);
      printf("Product updated successfully!\n");
      return;
    }
  }
  printf("Product not found!\n");
}

void searchProduct() {
  int id;
  printf("Enter product ID to search: ");
  scanf("%04d", &id);
  
  for (int i = 0; i < FactoryProductCount; i++) {
    if (inventory[i].id == id) {
      printf("ID: %04d\nName: %s\nCategory: %s\nQuantity: %d\nPrice: %.2f\n",
           inventory[i].id, inventory[i].name, inventory[i].category,
           inventory[i].quantity, inventory[i].price);
      return;
    }
  }
  printf("Product not found!\n");
}

void listAllProducts() {
  if (FactoryProductCount == 0) {
    printf("No products in the inventory!\n");
    return;
  }

  printf("\n=================================== Product List ===================================\n");
  printf("| %-5s | %-20s | %-20s | %-10s | %-10s |\n", "ID", "Name", "Category", "Quantity", "Price");
  printf("-----------------------------------------------------------------------------------\n");

  
  for (int i = 0; i < FactoryProductCount; i++) {
    printf("| %04d | %-20s | %-20s | %-10d | $ %-10.2f |\n",
         inventory[i].id, inventory[i].name, inventory[i].category,
         inventory[i].quantity, inventory[i].price);
  }
  printf("====================================================================================\n\n\n\n\n\n");
}

void saveData(){
  FILE *fp;
  fp = fopen("thh.json", "w");
  if (fp == NULL){
    printf("Error saving data to file!\n");
    return;
  }
  for (int i = 0; i < FactoryProductCount; i++){
    fprintf(fp, "%04d\n", inventory[i].id);
    fprintf(fp, "%s\n", inventory[i].name);
    fprintf(fp, "%s\n", inventory[i].category);
    fprintf(fp, "%d\n", inventory[i].quantity);
    fprintf(fp, "%.2f\n", inventory[i].price);
  }
  fclose(fp);
}

void loadData(){
  FILE *fp;
  fp = fopen("thh.json", "r");
  if (fp == NULL){
    return;
  }
  while (fscanf(fp, "%04d", &inventory[FactoryProductCount].id) != EOF){
    fgetc(fp);
    fgets(inventory[FactoryProductCount].name, sizeof(inventory[FactoryProductCount].name), fp);
    inventory[FactoryProductCount].name[strcspn(inventory[FactoryProductCount].name, "\n")] = 0;
    fgets(inventory[FactoryProductCount].category, sizeof(inventory[FactoryProductCount].category), fp);
    inventory[FactoryProductCount].category[strcspn(inventory[FactoryProductCount].category, "\n")] = 0;
    fscanf(fp, "%d", &inventory[FactoryProductCount].quantity);
    fscanf(fp, "%f", &inventory[FactoryProductCount].price);
    FactoryProductCount++;
  }
  fclose(fp);
} 
