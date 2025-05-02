#include <stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_PRODUCTS 100
typedef struct
{
    int id;
    char name[50];
    char catagory[50];
    int quantity;
    float price;
    char productiondate[15];
    char expirydate[15];

}Product;

Product products[MAX_PRODUCTS];
int productCount=0;

void showMainmenu();
void saveToFile();
void loadFromFile();

void ProductManagementMenu();
void addProduct();
void updateProduct();
void deleteProduct();

void InventoryMenu();
void ViewStock();


int main()
{
    loadFromFile();

    int choice;

    while(1)
    {
        showMainmenu();

        scanf("%d",&choice);
        getchar();

        switch(choice)
        {
            case 1:
            ProductManagementMenu();
            break;
            case 2:
            InventoryMenu();
            break;
            case 3:
            printf("Billing System is selected.\n");
            break;
            case 4:
            printf("Sales Records is selected.\n");
            break;
            case 0:
            printf("Exiting.....\n");
            return 0;
            default:
            printf("Invalid choice.\nPlease try again.\n");

        }
    }
    return 0;
}
void showMainmenu()
{
    printf("\n===============================\n");
    printf("            ReTail_Sync           \n");
    printf("===============================\n");
    printf("[1] Product Management.\n");
    printf("[2] Inventory System.\n");
    printf("[3] Billing System .\n");
    printf("[4] Sales Records.\n");
    printf("[0] Exit App.\n");
    printf("Enter your choice: ");

}

void ProductManagementMenu()
{
    int choice;

    while(1)
    {
        printf("\n=============================\n");
        printf("       Product Management       \n");
        printf("=================================\n");
        printf("[1]Add New Product.\n");
        printf("[2]Update Existing Product.\n");
        printf("[3]Delete a Product.\n");
        printf("[0]Back to Main Menu.\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
            addProduct();
            break;
            case 2:
            updateProduct();
            break;
            case 3:
            deleteProduct();
            break;

            case 0:
            return;

            default:
            printf("Invalid choice.\nPlease try again.\n");

        }

    }
}

void addProduct()
{
    if(productCount>=MAX_PRODUCTS)
    {
        printf("LIMIT REACHED!\nCannot add more products.\n");
        return;
    }
    Product newProduct;
    newProduct.id=productCount+1;

    printf("\nEnter Product Name: ");
    fgets(newProduct.name, sizeof(newProduct.name),stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = '\0';

    printf("\nEnter Product Category: ");
    fgets(newProduct.catagory, sizeof(newProduct.catagory),stdin);
    newProduct.catagory[strcspn(newProduct.catagory, "\n")] = '\0';

    printf("Enter Quantity: ");
    scanf("%d",&newProduct.quantity);

    printf("Enter price per unit: ");
    scanf("%f",&newProduct.price);
    getchar();

    printf("Enter Production Date (YYYY-MM-DD): ");
    fgets(newProduct.productiondate, sizeof(newProduct.productiondate),stdin);
    newProduct.productiondate[strcspn(newProduct.productiondate, "\n")] = '\0';

    printf("Enter Expiration Date (YYYY-MM-DD): ");
    fgets(newProduct.expirydate, sizeof(newProduct.expirydate),stdin);
    newProduct.expirydate[strcspn(newProduct.expirydate, "\n")] = '\0';

    products[productCount]=newProduct;
    productCount++;

    printf("Product Added Successfully! \n");

    saveToFile();

}
void updateProduct()
{
    int id, found=0;
    printf("\n Enter Product ID to update: ");
    scanf("%d",&id);
    getchar();

    for(int i=0;i<productCount;i++)
    {
        if(products[i].id == id)
        {
        found=1;
        printf("\nUpdating Product ID %d:\n",id);

        printf("Enter new name:");
        fgets(products[i].name,sizeof(products[i].name),stdin);
        products[i].name[strcspn(products[i].name, "\n")]='\0';

        printf("Enter new catagory:");
        fgets(products[i].catagory,sizeof(products[i].catagory),stdin);
        products[i].catagory[strcspn(products[i].catagory, "\n")]='\0';

        printf("Enter new quantity: ");
        scanf("%d", &products[i].quantity);
        getchar();

        printf("Enter new price: ");
        scanf("%f", &products[i].price);
        getchar();

        printf("Enter New Production Date (YYYY-MM-DD): ");
        fgets(products[i].productiondate, sizeof(products[i].productiondate),stdin);
        products[i].productiondate[strcspn(products[i].productiondate, "\n")] = '\0';

        printf("Enter New Expiration Date (YYYY-MM-DD): ");
        fgets(products[i].expirydate, sizeof(products[i].expirydate),stdin);
        products[i].expirydate[strcspn(products[i].expirydate, "\n")] = '\0';

        printf("\n Product updated successfully!\n");

        saveToFile();
        return;
        }


    }

        if(found==0)
        {
             printf(" Product with ID %d not found.\n", id);
        }
}

void deleteProduct()
{
    int id, found = 0;
    printf("\n Enter Product ID to delete: ");
    scanf("%d", &id);
    getchar();

    for(int i=0;i<productCount;i++)
    {
        if(products[i].id==id)
        {
            found=1;
            for(int j = i; j < productCount - 1; j++)
            {
                products[j] = products[j + 1];

            }
            productCount--;
            printf("\n Product with ID %d deleted successfully!\n", id);

            saveToFile();
            return;
        }
    }

    if(found==0)
    {
        printf(" Product with ID %d not found.\n", id);
    }

}

void saveToFile()
{
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d|%s|%s|%d|%.2f|%s|%s\n",
                products[i].id,
                products[i].name,
                products[i].catagory,
                products[i].quantity,
                products[i].price,
                products[i].productiondate,
                products[i].expirydate);
    }

    fclose(file);
    printf("Products saved successfully to file.\n");
}

void loadFromFile()
{
     FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("No saved products found.\n");
        return;
    }


    while (fscanf(file, "%d|%49[^|]|%49[^|]|%d|%f|%14[^|]|%14[^\n]\n",
                   &products[productCount].id,
                   products[productCount].name,
                   products[productCount].catagory,
                   &products[productCount].quantity,
                   &products[productCount].price,
                   products[productCount].productiondate,
                   products[productCount].expirydate) == 7) {
        if (productCount < MAX_PRODUCTS) {
            productCount++;
        }
        else {
            break;
        }
    }

    fclose(file);
    printf("Products loaded successfully from file.\n");

}

void InventoryMenu()
{
    int choice;
    while(1)
    {
        printf("\n=============================\n");
        printf("         Inventory Menu       \n");
        printf("=============================\n");
        printf("[1] View Stock (All Products)\n");
        printf("[2] Low Stock Alerts\n");
        printf("[3] Expiry Date Alerts\n");
        printf("[0] Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                ViewStock();
                break;
            case 2:
                printf("Low Stock Alerts selected.\n");
                break;
            case 3:
                printf("Expiry Date Alerts selected.\n");
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
void ViewStock()
{
    if (productCount == 0) {
        printf("\nNo products available.\n");
        return;
    }

    printf("\n================================== All Products ===============================\n");
    printf("ID  | Name              | Category       | Qty | Price  | Prod. Date  | Exp. Date\n");
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < productCount; i++)
    {
        printf("%-4d| %-17s| %-15s| %-4d| %-7.2f| %-12s| %-12s\n",
               products[i].id,
               products[i].name,
               products[i].catagory,
               products[i].quantity,
               products[i].price,
               products[i].productiondate,
               products[i].expirydate);
    }
}
