#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

// Define KeyWords
#define ENTER 13
#define TAB 9
#define BKSP 8
#define PASSWORD_FILE "password.txt"
// Function ProtoType

void menu(void);
void add(void);
void search(void);
void modify(void);
void list(void);
void delete(void);
void end(void);
void createPassword();
void validatePassword();
int savePasswordToFile(const char password[]);
int loadPasswordFromFile(char password[]);

void main()
{
    if (fopen(PASSWORD_FILE, "r") == NULL)
    {
        // File does not exist, prompt to create a password
        createPassword();
    }
    validatePassword(); // Validate the saved password
}

// Function to create a password
void createPassword()
{
    system("cls");
    char password[255];
    char confirmPassword[255];
    char ch;
    int i;

    // Step 1: Enter a password
    printf("Create your password. Hit ENTER to confirm.\n");
    printf("Password: ");
    i = 0;
    while (1)
    {
        ch = getch();
        if (ch == ENTER)
        {
            password[i] = '\0'; // Null-terminate
            break;
        }
        else if (ch == BKSP)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b"); // Handle backspace
            }
        }
        else if (i < 254)     // Ensure no buffer overflow
        {
            password[i++] = ch;
            printf("*");
        }
    }

    // Step 2: Confirm the password
    printf("\nConfirm your password: ");
    i = 0;
    while (1)
    {
        ch = getch();
        if (ch == ENTER)
        {
            confirmPassword[i] = '\0';
            break;
        }
        else if (ch == BKSP)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if (i < 254)
        {
            confirmPassword[i++] = ch;
            printf("*");
        }
    }

    // Step 3: Verify passwords match
    if (strcmp(password, confirmPassword) == 0)
    {
        if (savePasswordToFile(password))
        {
            printf("\nPassword created and saved successfully!\n");
            Sleep(2000);
        }
        else
        {
            printf("\nError saving password. Please try again.\n");
            Sleep(2000);
            createPassword();
        }
    }
    else
    {
        printf("\nPasswords do not match. Try again.\n");
        Sleep(2000);
        createPassword();
    }
}

// Function to validate the password
void validatePassword()
{
    char savedPassword[255];
    char enteredPassword[255];
    char ch;
    int i;

    if (!loadPasswordFromFile(savedPassword))
    {
        printf("\nError loading saved password. Exiting...\n");
        return;
    }

    while (1)
    {
        system("cls");
        printf("Enter your password. Hit ENTER to confirm.\n");
        printf("Password: ");
        i = 0;
        while (1)
        {
            ch = getch();
            if (ch == ENTER)
            {
                enteredPassword[i] = '\0'; // Null-terminate
                break;
            }
            else if (ch == BKSP)
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else if (i < 254)
            {
                enteredPassword[i++] = ch;
                printf("*");
            }
        }

        // Step 2: Verify password
        if (strcmp(savedPassword, enteredPassword) == 0)
        {
            printf("\nCorrect Password!\n");
            Sleep(2000);
            menu();
            break;
        }
        else
        {
            printf("\nInvalid Password! Try again.\n");
            Sleep(2000);
        }
    }
}

// Function to save the password to a file
int savePasswordToFile(const char password[])
{
    FILE *file = fopen(PASSWORD_FILE, "w");
    if (file == NULL)
    {
        return 0; // Error opening fle
    }
    fprintf(file, "%s", password);
    fclose(file);
    return 1; // Success
}

// Function to load the password from a file
int loadPasswordFromFile(char password[])
{
    FILE *file = fopen(PASSWORD_FILE, "r");
    if (file == NULL)
    {
        return 0; // Error opening file
    }
    fscanf(file, "%s", password);
    fclose(file);
    return 1; // Success
}

void menu()
{
    //clears the terminal screen
    system("cls");

label1:

    //clears the input stream - prevents the program from going into infinite loop
    fflush(stdin);

    printf(">>> Phone Book Main Menu <<< \n");
    printf("> 1. Add Record\n");
    printf("> 2. Search Record\n");
    printf("> 3. Modify Record\n");
    printf("> 4. List Record\n");
    printf("> 5. Delete Record\n");
    printf("> 6. Close the Phone Book \n\n");

    int input;
    printf("Please enter a number to proceed: ");
    scanf("%d",&input);

    switch (input)
    {
    case 1:
        add();
        break;
    case 2:
        search();
        break;

    case 3:
        modify();
        break;

    case 4:
        list();
        break;

    case 5:
        delete();
        break;

    case 6:
        end();
        break;

    default:
        printf("\nXXX - Invaild input - XXX\n\n");
        goto label1;
        break;
    }
}

void add() {
    // Clear the input stream
    fflush(stdin);
    system("cls");

    // Open file in append mode (create if it doesn't exist)
    FILE *pF = fopen("record.txt", "ab+");

    if (pF == NULL) {
        printf("Unable to open/locate the file.\n");
        Sleep(2000);
        return; // Exit the function if the file cannot be opened
    }

    int numContacts;
    char name[255];
    char address[255];
    char mail[255];
    double number;

    // Ask user how many contacts to add
    printf("How many contacts do you want to add? ");
    scanf("%d", &numContacts);
    fflush(stdin);

    for (int i = 0; i < numContacts; i++) {
        system("cls");
        printf("Adding Contact %d of %d\n", i + 1, numContacts);

        printf("Enter Name: ");
        gets(name);

        printf("Enter Address (City): ");
        gets(address);

        printf("Enter Mail-ID: ");
        gets(mail);

        printf("Enter Phone No.: ");
        scanf("%lf", &number);
        fflush(stdin);

        // Save contact to file
        fprintf(pF, "%s %s %s %.0lf\n", name, address, mail, number);
        printf("Contact %d saved successfully!\n", i + 1);
        Sleep(1000);
    }

    // Close the file
    fclose(pF);

    printf("\nAll contacts have been added successfully. Redirecting to main menu.\n");
    Sleep(2000);
    menu(); // Redirect to the main menu
}

void search()
{

label2:

    system("cls");
    fflush(stdin);

    FILE *pF = fopen("record.txt", "r");

    char name[255];
    char address[255];
    char mail[255];
    double number;

    int flag=0;
    int compare;

    char find[255];
    printf("Enter the name of the person you want to see the detail: ");
    gets(find);

    while(fscanf(pF, "%s %s %s %lf \n", name, address, mail, &number) != EOF)
    {
        //strcmp(variable, variable1) -- if both the strings are equal then it will return 0 otherwise a random number.
        compare = strcmp(find, name);

        if(compare == 0)
        {
            printf("\n>>> Record Found <<< \n\n");

            printf("> Name: %s \n", name);
            printf("> Address: %s \n", address);
            printf("> Mail ID: %s \n", mail);
            printf("> Phone No.: %.0lf \n", number);

            flag = 1;
        }
    }

    fclose(pF);

    if(flag == 0)
        printf("\n>>> Record Not Found <<< \n");

    fflush(stdin);

    char input;
    printf("\nDo you wanna search for more records [y/N]: ");
    scanf(" %c",&input);

    if(input == 'y' || input=='Y')
        goto label2;
    else if(input=='n' || input=='N')
    {
        printf("\nRedirecting to main menu.");
        Sleep(2000);
        menu();
    }
    else
    {
        printf("\nInvaild input. Redirecting to main menu.");
        Sleep(2000);
        menu();
    }
}

void modify()
{
    system("cls");
    fflush(stdin);

    //opening main record file & a temporary file s
    FILE *pF = fopen("record.txt", "r");
    FILE *pTemp = fopen("temporary.txt", "a");

    char name[255], address[255], mail[255];
    char name1[255], address1[255], mail1[255];
    double number, number1;

    int compare, flag=0;

    printf("Enter the name of the person you want to see the detail: ");
    gets(name1);

    fflush(stdin);
    system("cls");

    while(fscanf(pF, "%s %s %s %lf \n", name, address, mail, &number) != EOF)
    {
        compare = strcmp(name1, name);
        if(compare == 0)
        {
            printf("-------------------------------\n");
            printf(">>> Record Modification <<< \n");
            printf("-------------------------------\n\n");

            printf("Enter Name: ");
            gets(name1);

            printf("Enter Address (City): ");
            gets(address1);

            printf("Enter Mail-ID: ");
            gets(mail1);

            printf("Enter Phone No.: ");
            scanf("%lf",&number1);

            fprintf(pTemp, "%s %s %s %.0lf \n", name1, address1, mail1, number1);

            flag = 1;
        }
        else
            fprintf(pTemp, "%s %s %s %.0lf \n", name, address, mail, number);
    }

    if(flag == 0)
    {
        printf("-------------------------------\n");
        printf(">>> Record Not Found <<< \n");
        printf("-------------------------------\n\n");
    }

    fclose(pF);
    fclose(pTemp);

    //deletes everything from main record file
    pF = fopen("record.txt", "w");
    fclose(pF);

    pF = fopen("record.txt", "a");
    pTemp = fopen("temporary.txt", "r");

    //copies records from temporary file to main record file
    while (fscanf(pTemp, "%s %s %s %lf \n", name, address, mail, &number) != EOF)
    {
        fprintf(pF, "%s %s %s %.0lf \n", name, address, mail, number);
    }

    fclose(pF);
    fclose(pTemp);

    //deletes everything from temporary file
    pTemp = fopen("temporary.txt", "w");
    fclose(pTemp);

    printf("\n\nProcessing your changes....");
    Sleep(3000);
    menu();

}

void list()
{
    system("cls");
    FILE *pF = fopen("record.txt", "r");

    char name[255];
    char address[255];
    char mail[255];
    double number;

    //lists all the records from main record files
    while(fscanf(pF, "%s %s %s %lf \n", name, address, mail, &number) != EOF)
    {
        printf("-------------------------------\n");
        printf("> Name: %s \n", name);
        printf("> Address: %s \n", address);
        printf("> Mail-ID: %s \n", mail);
        printf("> Phone No.: %.0lf \n", number);
        printf("-------------------------------\n\n\n");
    }

    fclose(pF);

    printf("Press any key to get back to main menu.\n");
    getch();
    menu();
}

void delete()
{
    system("cls");

    FILE *pF = fopen("record.txt", "r");
    FILE *pTemp = fopen("temporary.txt", "a");

    char name[255], name1[255], address[255], mail[255];
    double number;

    int compare, flag=0;

    fflush(stdin);
    system("cls");

    printf("Enter the name of the person you want to see the detail: ");
    gets(name1);

    fflush(stdin);
    system("cls");

    while(fscanf(pF, "%s %s %s %lf \n", name, address, mail, &number) != EOF)
    {
        compare = strcmp(name1, name);
        if(compare == 0)
        {
            //this time the record won't be copied to temporary file and this record will be skipped.
            printf("-------------------------------\n");
            printf(">>> Record Deleted Successfully <<< \n");
            printf("-------------------------------\n\n");
            flag = 1;
        }
        else
        {
            //it will copy the records from main file to temporary file one by one.
            fprintf(pTemp, "%s %s %s %.0lf \n", name, address, mail, number);
        }
    }

    if(flag == 0)
    {
        printf("-------------------------------\n");
        printf(">>> Record Not Found <<< \n");
        printf("-------------------------------\n\n");
    }

    fclose(pF);
    fclose(pTemp);

    //deletes everything from main record file
    pF = fopen("record.txt", "w");
    fclose(pF);

    pF = fopen("record.txt", "a");
    pTemp = fopen("temporary.txt", "r");

    while (fscanf(pTemp, "%s %s %s %lf \n", name, address, mail, &number) != EOF)
    {
        fprintf(pF, "%s %s %s %.0lf \n", name, address, mail, number);
    }

    fclose(pF);
    fclose(pTemp);

    //deletes everything from temporary file
    pTemp = fopen("temporary.txt", "w");
    fclose(pTemp);

    printf("\n\nProcessing your changes....");
    Sleep(3000);
    menu();

}

void end()
{
    system("cls");
    printf(">>> Phone Book in C <<< \n\n");
    printf("> Creator: @Alkaison (Ganesh Mourya) \n\n");
    printf("> project done by:\n> abrar shahriar shahjahan ID:C243134 \n");
    printf("> mohammed rasib iftekhar. ID:C243116 \n");
    printf("> chowdhury nashat parvez. ID:C243154 \n\n");
    exit(0);
}
