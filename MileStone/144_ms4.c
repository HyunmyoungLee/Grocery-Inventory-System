#include <stdio.h>
#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0
#define MAX_ITEM_NO 500
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
#define DATAFILE "items.txt"
const double TAX = 0.13;
void welcome(void);
void printTitle(void);
void printFooter(double grandTotal);
void flushKeyboard(void);
void pause(void);
int getInt(void);
double getDouble(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDoubleLimited(double lowerLimit, double upperLimit);
int yes(void);
void GroceryInventorySystem(void);
int menu(void);
//void saveItem(struct Item item, FILE* dataFile);
//int loadItem(struct Item* item, FILE* dataFile);
//int saveItems(const struct Item item[], char fileName[], int NoOfRecs);
//int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr);

//double totalAfterTax(struct Item item);
//int isLowQuantity(struct Item item);
//struct Item itemEntry(int sku);
//void displayItem(struct Item item, int linear);
//void listItems(const struct Item item[], int NoOfItems);
//int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index); 

//void search(const struct Item item[], int NoOfRecs);

struct Item {
    double price;
    int sku;
    int isTaxed;
    int quantity;
    int minQuantity;
    char name[21];
};
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQuantity(struct Item item[], int NoOfRecs, int stock);
void saveItem(struct Item item, FILE* dataFile);

int loadItem(struct Item* item, FILE* dataFile);
int saveItems(const struct Item item[], char fileName[], int NoOfRecs);
int loadItems(struct Item item[], char fileName[], int* NoOfRecsPtr);

double totalAfterTax(struct Item item);
int isLowQuantity(struct Item item);
struct Item itemEntry(int sku);
void displayItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

void search(const struct Item item[], int NoOfRecs);

int main(void){
	GroceryInventorySystem();
	return 0;
}

void welcome(void)
{

    printf("---=== Grocery Inventory System ===---\n\n");
}

void printTitle(void)
{
    printf
	("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
    printf
	("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void printFooter(double grandTotal)
{

    printf
	("--------------------------------------------------------+----------------\n");
    if (grandTotal > 0) {
	printf
	    ("                                           Grand Total: |%12.2lf\n",
	     grandTotal);
    }

}

void flushKeyboard(void)
{
    char ch;
    while (ch != '\n') {
	scanf("%c", &ch);
    }
}

void pause(void)
{
    printf("Press <ENTER> to continue...");
    flushKeyboard();
}

int getInt(void)
{
    int Value = 0;
    char NL;

    scanf("%d%c", &Value, &NL);

    while (NL != '\n') {

	flushKeyboard();
	printf("Invalid integer, please try again: ");
	scanf("%d%c", &Value, &NL);
    }
    return Value;
}

int getIntLimited(int lowerLimit, int upperLimit)
{
    int value;
    value = getInt();

    while (value < lowerLimit || value > upperLimit) {
	printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
	value = getInt();
    }
    return value;
}

double getDouble(void)
{
    double Value = 0;
    char NL;
    scanf("%lf%c", &Value, &NL);

    while (NL != '\n') {
	flushKeyboard();
	printf("Invalid number, please try again: ");
	scanf("%lf%c", &Value, &NL);
    }
    return Value;
}

double getDoubleLimited(double lowerLimit, double upperLimit)
{
    double value;
    value = getDouble();
    while (value < lowerLimit || value > upperLimit) {


	printf("Invalid value, %lf< value < %lf: ", lowerLimit,
	       upperLimit);

	value = getDouble();
    }
    return value;
}

int yes(void)
{
    char exit;
    int value = 0;
    exit = 0;
    while (exit != 'Y' && exit != 'y' && exit != 'N' && exit != 'n') {
	scanf("%c", &exit);
	flushKeyboard();
	if (exit == 'Y' || exit == 'y') {
	    value = 1;
	    return value;
	} else if (exit == 'N' || exit == 'n') {
	    value = 0;
	    return value;
	} else {
	    printf("Only (Y)es or (N)o are acceptable: ");
	}
    }
    return value;
}

int menu(void)
{
    int value;
    printf("1- List all items\n");
    printf("2- Search by SKU\n");
    printf("3- Checkout an item\n");
    printf("4- Stock an item\n");
    printf("5- Add new item or update item\n");
    printf("6- delete item\n");
    printf("7- Search by name\n");
    printf("0- Exit program\n");
    printf("> ");
    value = getIntLimited(0, 7);
    return value;
}

void GroceryInventorySystem(void)
{
    struct Item items[MAX_ITEM_NO];
    int read= 0;
    int value = 0;
    int option = 0;
    int index;
    int sku;
    int check;
    welcome();
   int abc  = loadItems(items, DATAFILE, &read);
   if(abc == 0){
	   printf("Could not read from %s.\n", DATAFILE);
   }else{

    while (value == 0) {
	option = menu();
	if (option == 1) {
		listItems(items, read);
	//    printf("List Items under construction!\n");
	    pause();
	} else if (option == 2) {
		search(items,read);
	//    printf("Search Items under construction!\n");
	    pause();
	} else if (option == 3) {
		adjustQuantity(items,read,CHECKOUT);
		 check = saveItems(items, DATAFILE, read);
		if (check == 0){
			printf("Could not read from %s.\n", DATAFILE);
		}
	//    printf("Checkout Item under construction!\n");
	    pause();
	} else if (option == 4) {
		adjustQuantity(items,read,STOCK);
		check = saveItems(items,DATAFILE,read);
		if(read == 0){
			printf("Could not read from %s.\n", DATAFILE);
		}
	//    printf("Stock Item under construction!\n");
	    pause();
	} else if (option == 5) {
		addOrUpdateItem(items,&read);
		check = saveItems(items,DATAFILE,read);
		if (check == 0){
			printf("could not update data file %s\n", DATAFILE);
		}
	//    printf("Add/Update Item under construction!\n");
	    pause();
	} else if (option == 6) {
		printf("Please enter the SKU: ");
		int del = locateItem(items,read,sku,&index);
		if (del == 0){
			printf("SKU not found!\n");
			pause();
		}else{
			printf("This Item will be deleted, are you sure? (Y)es/(N)o: ");
			value = yes();
			if( value == 0){
				printf("Aborted!\n");
			}else if(value == 1){
				printf("Deleted!\n");
			}
		}
	   // printf("Delete Item under construction!\n");
	    pause();
	} else if (option == 7) {
		printf("Not implemented!\n");
	   // printf("Search by name under construction!\n");
	    pause();
	} else {
	    printf("Exit the program? (Y)es/(N)o: ");
	    value = yes();
	}
    }
    }
}

double totalAfterTax(struct Item item)
{
    double total = 0;
    if (item.isTaxed == 0) {
	total = item.price * item.quantity;
    } else if (item.isTaxed == 1) {
	total = item.price * item.quantity;
	total = total + (total * TAX);
    }
    return total;
}

int isLowQuantity(struct Item item)
{
    int value;
    if (item.quantity < item.minQuantity) {
	value = 1;
    } else {
	value = 0;
    }
    return value;
}

struct Item itemEntry(int sku)
{
    struct Item itemEntry;
    itemEntry.sku = sku;
    char *type = "%[^\n]%*c";
    printf("        SKU: %d\n", sku);
    printf("       Name: ");
    scanf(type, &itemEntry.name);
    printf("      Price: ");
    itemEntry.price = getDoubleLimited(0.01,1000.00);
    printf("   Quantity: ");
    itemEntry.quantity = getIntLimited(1,MAX_QTY);
    printf("Minimum Qty: ");
    itemEntry.minQuantity = getIntLimited(0,100);
    printf("   Is Taxed: ");
    itemEntry.isTaxed = yes();
    return itemEntry;
}

void displayItem(struct Item item, int linear)
{
    double total;
    char *check[4];
    if (item.isTaxed == 1) {
	*check = "Yes";
	total = item.price * item.quantity * (1 + TAX);
    } else {
	*check = "No";
	total = item.price * item.quantity;
    }
    if (linear == 1) {
	printf("|%3d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|", item.sku,
	       item.name, item.price, *check, item.quantity,
	       item.minQuantity, total);
	if (item.quantity <= item.minQuantity) {
	    printf("***\n");
	} else {
	    printf("\n");
	}
    } else if (linear == 0) {

	printf("        SKU: %d\n", item.sku);
	printf("       Name: %s\n", item.name);
	printf("      Price: %.2lf\n", item.price);
	printf("   Quantity: %d\n", item.quantity);
	printf("Minimum Qty: %d\n", item.minQuantity);
	printf("   Is Taxed: %s\n", *check);
	if (item.quantity <= item.minQuantity) {
	    printf("WARNING: Quantity low, please order ASAP!!!\n");
	}
    }
}

void listItems(const struct Item item[], int noOfItems)
{
    int i;
    double total = 0;
    double grandTotal = 0;
    printTitle();
    for (i = 0; i < noOfItems; i++) {
	char *check[4];
	if (item[i].isTaxed == 1) {
	    *check = "Yes";
	    total = item[i].price * item[i].quantity * (1 + TAX);
	} else {
	    *check = "No";
	    total = item[i].price * item[i].quantity;
	}
	grandTotal += total;
	printf("%-4d|%3d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|", i + 1,
	       item[i].sku, item[i].name, item[i].price, *check,
	       item[i].quantity, item[i].minQuantity, total);
	if (item[i].quantity <= item[i].minQuantity) {
	    printf("***\n");
	} else {
	    printf("\n");
	}
    }
    printFooter(grandTotal);
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int *index)
{
    int i;
    int flag = 0;
    for (i = 0; i < NoOfRecs; i++) {
	if (sku == item[i].sku) {
	    *index = i;
	    flag = 1;
	}
    }
    return flag;
}

void search(const struct Item item[], int NoOfRecs)
{
    int sku;
    int value;
    int found;
    printf("Please enter the SKU: ");
    sku = getIntLimited(SKU_MIN, SKU_MAX);
    found = locateItem(item, NoOfRecs, sku, &value);
    if (found == 1) {
	displayItem(item[value], FORM);
    } else {
	printf("Item not found!\n");
    }
}

void updateItem(struct Item *itemptr)
{
    struct Item item;
    int answer;
    printf("Enter new data:\n");
    item = itemEntry(itemptr->sku);
    printf("Overwrite old data? (Y)es/(N)o: ");
    answer = yes();
    if (answer == 1) {
	*itemptr = item;
	printf("--== Updated! ==--\n");
    } else {
	printf("--== Aborted! ==--\n");
    }
}

void addItem(struct Item item[], int *NoOfRecs, int sku)
{
    struct Item items;
    int answer;
    if (*NoOfRecs >= MAX_ITEM_NO) {
	printf("Can not add new item; Storage Full!\n");
    } else {
	items = itemEntry(sku);
	printf("Add Item? (Y)es/(N)o: ");
	answer = yes();
	if (answer == 1) {
	    item[*NoOfRecs] = items;
	    (*NoOfRecs)++;
	    printf("--== Added! ==--\n");
	} else {
	    printf("--== Aborted! ==--\n");
	}
    }
}

void addOrUpdateItem(struct Item item[], int *NoOfRecs)
{
    int sku;
    int found;
    int value;
    int answer;
    printf("Please enter the SKU: ");
    sku = getIntLimited(SKU_MIN, SKU_MAX);
    found = locateItem(item, *NoOfRecs, sku, &value);
    if (found == 1) {
	displayItem(item[value], FORM);
	printf("Item already exists, Update? (Y)es/(N)o: ");
	answer = yes();
	if (answer == 1) {
	    updateItem(&item[value]);
	} else {
	    printf("--== Aborted! ==--\n");
	}
    } else {
	addItem(item, NoOfRecs, sku);
    }
}

void adjustQuantity(struct Item item[], int NoOfRecs, int stock)
{
    int sku;
    int value;
    int max;
    int number;
    int found;
    printf("Please enter the SKU: ");
    sku = getIntLimited(SKU_MIN, SKU_MAX);
    found = locateItem(item, NoOfRecs, sku, &value);
    if (found != 0) {
	displayItem(item[value], FORM);
	if (stock == STOCK) {
	    max = (MAX_QTY - item[value].quantity);
	    printf
		("Please enter the quantity to stock; Maximum of %d or 0 to abort: ",
		 max);
	} else if (stock == CHECKOUT) {
	    max = item[value].quantity;
	    printf
		("Please enter the quantity to checkout; Maximum of %d or 0 to abort: ",
		 max);
	}
	number = getIntLimited(0, max);
	if (number != 0) {
	    if (stock == STOCK) {
		item[value].quantity += number;
		printf("--== Stocked! ==--\n");
	    } else {
		item[value].quantity -= number;
		printf("--== Checked out! ==--\n");
	    }

	    if (isLowQuantity(item[value]) == 1) {
		printf("Quantity is low, please reorder ASAP!!!\n");
	    }
	}else{
	    printf("--== Aborted! ==--\n");
	}
	}else {
	    printf("SKU not found in storage!\n");
	}
    }
void saveItem(struct Item item, FILE* dataFile){
	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);
}
int loadItem(struct Item* item, FILE* dataFile){
	int value=0;
	if(fscanf(dataFile, "%d,%d,%d,%lf,%d,%[^\n]", &item->sku, &item->quantity,&item->minQuantity, &item->price, &item->isTaxed,item->name)==6)
	{
		value =1;
	}else{
		value =0;
	}
	return value;
}
int saveItems(const struct Item item[], char fileName[], int NoOfRecs){
	int value=0;
	int i=0;
	FILE *fp;
	fp = fopen(fileName, "w");
	if(fp != NULL){
		for(i=0;i<NoOfRecs;i++){
			saveItem(item[i], fp);
		}
		value=1;
		fclose(fp);
	}else{
		value=0;
	}
	return value;
}
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr){
	int value=0;
	int i=0;
	FILE *fp;
	fp = fopen(fileName, "r");
	if(fp != NULL){
		while(!feof(fp)){
			i+=loadItem(&item[i], fp);
		}
		value =1;
		*NoOfRecsPtr=i;
		fclose(fp);
	}else{
		value = 0;
	}
	return value;
}











/*
int main(void){
	int iVal;
	double dVal;
	welcome();
	printf("\n");
	printf("listing header and footer with grand total:\n");
	printTitle();
	
	printFooter(1234.5678);
	printf("listing header and footer without grand total:\n");
	printTitle();
	printFooter(-1);

	pause();

	printf("Enter an integer: ");
	iVal = getInt();
	printf("You entered: %d\n", iVal);

	printf("Enter an integer between 10 and 20: ");
	iVal = getIntLimited(10, 20);
	printf("Your entered %d\n", iVal);

	printf("Enter a floating point number: ");
	dVal = getDouble();
	printf("You entered: %0.2lf\n", dVal);

	printf("Enter a floating point number between 10.00 and 20.00: ");
	dVal = getDoubleLimited(10.0, 20.0);
	printf("You entered: %0.2lf\n", dVal);
	printf("End of tester program for IO tools!\n");
	
	welcome();
	GroceryInventorySystem();





		return 0;
}
*/
