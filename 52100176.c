//----------------- Calling libraries to use functions in c --------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//---------------------------- Definition of values ----------------------------
#define MAX 100
#define MAX2 1000

//---------------------------- Struct for Employee -----------------------------
typedef struct
{
    char employeeID[MAX];
    char firstName[MAX];
    char lastName[MAX];
    char gender[MAX];
    char dateOfBirth[MAX];
    char department[MAX];
    char country[MAX];
} employee_t;

//---------------------------- Struct for Progress -----------------------------
typedef struct
{
    char employeeID2[MAX];
    char projectID[MAX];
    char progress[MAX];
} progress_t;

//--------------------------- Function declaration -----------------------------
void swap(employee_t *a, employee_t *b);
void countDepartment(employee_t employees[], FILE *outfile, int number, int value);
void readFileProgress(progress_t progress[]);
void listMale(employee_t employees[], FILE *outfile, int value1);
void listFemale(employee_t employees[], FILE *outfile, int value2);
void reportN(progress_t progress[], FILE *outfile, double number2, int value3);
void averageX(progress_t progress[], FILE *outfile, int number, int value4);
void sortAsc(employee_t employees[], FILE *outfile, int value5);
void sortDesc(employee_t employees[], FILE *outfile, int value6);
void countryName(employee_t employees[], FILE *outfile, char stringSecond[], int value7);
void deleteDuplicates(int temp[], int *count);
void lowerCase(char *s);
void clearFileContent(const char *filePath);
int checkIsNumber(char *s);
int countFileLimit(progress_t progress[]);

int main()
{
//-------------------------------- Open file------------------------------------
    FILE *infile;
    infile = fopen("Employee.csv", "r");
    FILE *infile2;
    infile2 = fopen("Progress.csv", "r");

//--- Create a result file to write the result from the command just executed --  
    FILE *outfile;
    outfile = fopen("result.csv", "w+");

    char buf[MAX];
    int column, row = 0, i = 0;
    employee_t employees[MAX2];

// Read data from Employee file to get information employee into struct Employee
    while (fgets(buf, sizeof(buf), infile) != NULL)
    {
        column = 0;
        row++;
        if (row == 1)
        {
            continue;
        }

        char *temp = strtok(buf, ",");
        while (temp)
        {
            if (column == 0)
            {
                strcpy(employees[i].employeeID, temp);
                // printf("%s\n", temp);
            }
            if (column == 1)
            {  
                strcpy(employees[i].firstName, temp);
            }
            if (column == 2)
            {
                strcpy(employees[i].lastName, temp);
                // printf("%s"\n, temp);
            }
            if (column == 3)
            {
                strcpy(employees[i].gender, temp);
            }
            if (column == 4)
            {
                strcpy(employees[i].dateOfBirth, temp);
            }
            if (column == 5)
            {
                strcpy(employees[i].department, temp);
            }
            if (column == 6)
            {
                strcpy(employees[i].country, temp);
            }
            temp = strtok(NULL, ",");
            column++;
        }
        i++;
    }

    progress_t progress[MAX2];

//------------------- Function to read data from progress ----------------------
    readFileProgress(progress);


    char count[10] = "count";
    char list[10] = "list";
    char report[10] = "report";
    char average[10] = "average";
    char sort[10] = "sort";
    char country[10] = "country";
    int number, check, j = 0;
    double number2;
    int value3, value4;
    char stringFirst[10], stringSecond[MAX], string[MAX];

//-------------------- Enter commands from the keyboard ------------------------
    fgets(string, MAX, stdin);
   
//------------------------ Check spaces and newlines ---------------------------
    for(check = 0; check <= strlen(string); check++)
    {
        if(string[check] == '\0' || string[check] == ' ')
        {
            j++;
        }
    }

//------------------ Cut the string just imported from fgets -------------------
    char *t = strtok(string," ");
    strcpy(stringFirst, t);
    while(t!=NULL)
    {
        t = strtok(NULL," ");
        if(t!=NULL)
        {
            strcpy(stringSecond, t);
        }
    }

    if(j == 2)
    {
//---------------------------- A command of count ------------------------------
        lowerCase(stringFirst);
        lowerCase(stringSecond);
        if (strcmp(stringFirst, count) == 0)
        {
            if(checkIsNumber(stringSecond) != 0)
            {
                number = atoi(stringSecond);
                countDepartment(employees, outfile, number, i);
                clearFileContent("check.txt");
            }
            else
            {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
                FILE *checkfile = fopen("check.txt", "w+");
                fprintf(checkfile, "wrong syntax");
                fclose(checkfile);            
            }

        }
        
//---------------------------- A command of list -------------------------------
        else if (strcmp(stringFirst, list) == 0)
        {
            if(checkIsNumber(stringSecond) == 1 && checkIsNumber(stringSecond) != 0)
            {
                if (strncmp(stringSecond, "male", 4) == 0)
                {
                    listMale(employees, outfile, i);
                    clearFileContent("check.txt");
                }
                else
                {
                    if (strncmp(stringSecond, "female", 6) == 0)
                    {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
                        listFemale(employees, outfile, i);
                        clearFileContent("check.txt");
                    }
                    else
                    {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
                        FILE *checkfile = fopen("check.txt", "w+");
                        fprintf(checkfile, "wrong syntax");
                        fclose(checkfile);
                    }
                }
            }
            else
            {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
                FILE *checkfile = fopen("check.txt", "w+");
                fprintf(checkfile, "wrong syntax");
                fclose(checkfile);     
            }
        }

//--------------------------- A command of report ------------------------------
        else if(strcmp(stringFirst, report) == 0)
        { 
            if(checkIsNumber(stringSecond) != 1 && checkIsNumber(stringSecond) != 0)
            {
                number2 = atof(stringSecond);
                if(number2 >= 0.0 && number2 <= 1.0)
                {
                    reportN(progress, outfile, number2, countFileLimit(progress));
                    clearFileContent("check.txt");
                }
                else
                {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
                    FILE *checkfile = fopen("check.txt", "w+");
                    fprintf(checkfile, "wrong syntax");
                    fclose(checkfile);              
                }
            }
            else
            {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
                FILE *checkfile = fopen("check.txt", "w+");
                fprintf(checkfile, "wrong syntax");
                fclose(checkfile);            
            }
        }

//--------------------------- A command of average -----------------------------
        else if(strcmp(stringFirst, average) == 0)
        {
            if(checkIsNumber(stringSecond) != 1 && checkIsNumber(stringSecond) != 0)
            {
                number = atoi(stringSecond);
                averageX(progress, outfile, number, countFileLimit(progress));
                // clearFileContent("check.txt");
            }
            else
            {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
                FILE *checkfile = fopen("check.txt", "w+");
                fprintf(checkfile, "wrong syntax");
                fclose(checkfile);      
            }
        }

//---------------------------- A command of sort -------------------------------
        else if(strcmp(stringFirst, sort) == 0)
        {
            if(checkIsNumber(stringSecond) == 1 && checkIsNumber(stringSecond) != 0)
            {
                if(strncmp(stringSecond, "asc", 3) == 0)
                {
                    sortAsc(employees, outfile, i);
                    clearFileContent("check.txt");
                }
                else
                {
                    if(strncmp(stringSecond,"desc", 4) == 0)
                    {
                        sortDesc(employees, outfile, i);
                        clearFileContent("check.txt");
                    }
                    else
                    {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
                        FILE *checkfile = fopen("check.txt", "w+");
                        fprintf(checkfile, "wrong syntax");
                        fclose(checkfile);     
                    }
                }
            }
            else
            {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
                FILE *checkfile = fopen("check.txt", "w+");
                fprintf(checkfile, "wrong syntax");
                fclose(checkfile);     
            }

        }

//-------------------------- A command of country ------------------------------
        else if(strcmp(stringFirst, country) == 0)
        {  
            if(checkIsNumber(stringSecond) == 1 && checkIsNumber(stringSecond) != 0)
            {
                countryName(employees, outfile, stringSecond, i);  
                clearFileContent("check.txt");                  
            } 
        }
        
        else
        {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
            FILE *checkfile = fopen("check.txt", "w+");
            fprintf(checkfile, "wrong syntax");
            fclose(checkfile);     
        }
    }
    else
    {
// If the command is entered incorrectly, it will generate a check file and print out the wrong syntax
            FILE *checkfile = fopen("check.txt", "w+");
            fprintf(checkfile, "wrong syntax");
            fclose(checkfile);     
    }

//-------------------------------- Close file ----------------------------------       
    fclose(infile);
    fclose(outfile);   
    return 0;
}

//Function to read data from Progress file to get information into struct Progress
void readFileProgress(progress_t progress[])
{
//-------------------------------- Open file------------------------------------
    FILE *infile2;
    infile2 = fopen("Progress.csv", "r");
    char buffer[MAX];
    int column2, row2 = 0, s = 0;

    while (fgets(buffer, sizeof(buffer), infile2) != NULL)
    {
        column2 = 0;
        row2++;
        if(row2 == 1)
        {
            continue;
        }
        char *tmp2 = strtok(buffer, ",");
        while (tmp2)
        {
            if(column2 == 0)
            {
                strcpy(progress[s].employeeID2, tmp2);
            }
            if(column2 == 1)
            {
                strcpy(progress[s].projectID, tmp2);
            }
            if (column2 == 2)
            {
                strcpy(progress[s].progress, tmp2);
            }
            tmp2 = strtok(NULL, ",");
            column2++;
        }
        s++;
    }

//-------------------------------- Close file ---------------------------------- 
    fclose(infile2);
}

//--------------------- Count the limit of progress file -----------------------
int countFileLimit(progress_t progress[])
{
    FILE *infile2;
    infile2 = fopen("Progress.csv", "r");
    char buffer[MAX];
    int column2, row2 = 0;
    int s = 0;

    while (fgets(buffer, MAX, infile2) != NULL)
    {
        row2++;
        if(row2 == 1)
        {
            continue;
        }
        char *tmp2 = strtok(buffer, ",");
        while (tmp2)
        {
            tmp2 = strtok(NULL, ",");
        }
        s++;
    }
    return s;
    fclose(infile2);
}

//--------------- Function to convert characters to lowercase ------------------
void lowerCase(char *s)
{
    int i;
    for(i = 0; i < strlen(s); i++)
    {
        if(s[i] >= 65 && s[i] <= 90)
        {
            s[i] = s[i] + 32;
        }
    }
}

//-------------- Check if input string is a number or a letter -----------------
int checkIsNumber(char *s)
{
    int i, j, t, f, h, d, g;
    for( i = 0; i <= strlen(s); i = i + 1)
    {
        for(j = 33; j <= 47; j = j + 1)
        {
            if( j == 46)
            {
                continue;
            }
            for(t = 58; t <= 64; t = t + 1)
            {
                for(f = 91; f <= 96; f = f + 1)
                {
                    for(h = 123; h <= 126; h = h + 1)
                    {
                        if(s[i] == j || s[i] == t || s[i] == f || s[i] == h)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
        for(d = 65; d <= 90; d++)
        {
            for(g = 97; g <= 122; g++)
            {
                if(s[i] == d || s[i] == g)
                {
                    return 1;
                }
            }
        }
    }
}

//---------------------- Function to delete data in file -----------------------
void clearFileContent(const char *filePath)
{
    FILE *checkfile = fopen("check.txt", "w+");
    if(checkfile == NULL)
    {
        return;
    }
    fclose(checkfile);
}

//---------- Function to perform counting a number of departments --------------
void countDepartment(employee_t employees[], FILE *outfile, int number, int value)
{
    int i, count = 0;

    for (i = 0; i < value; i++)
    {
        if (number == atoi(employees[i].department))
        {
            count++;
        }
    }
    fprintf(outfile, "%d", count);
}

//-------------- Function to filter the list of male Employees -----------------
void listMale(employee_t employees[], FILE *outfile, int value1)
{
    int i;
    char string[MAX] = "Male";
    for (i = 0; i < value1; i++)
    {
        if (strcmp((string), employees[i].gender) == 0)
        {
            fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);
        }
    }
}

//------------- Function to filter the list of female Employees ----------------
void listFemale(employee_t employees[], FILE *outfile, int value2)
{
    int i;
    char string[MAX] = "Female";
    for (i = 0; i < value2; i++)
    {
        if (strcmp((string), employees[i].gender) == 0)
        {
            fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);
        }
    }
}

// Function to report a number of Employees working on the same project progress
void reportN(progress_t progress[], FILE *outfile, double number2, int value3)
{
    int i, k, count = 0, temp[MAX];
    char string[MAX];
    double value;

    for(i = 0; i < value3; i++)
    {   
        value = atof(progress[i].progress);
        if(value  == number2) 
        {
            temp[count] = atoi(progress[i].employeeID2);
            count++;
        }
    }
    deleteDuplicates(temp, &count);

    for(k = 0; k < count; k++)
    {
        sprintf(string, "%d", temp[k]);
        fprintf(outfile, "%s\n", string);
    }
}

//----------------------- Function to delete duplicates ------------------------
void deleteDuplicates(int temp[220], int *count)
{
    int i, j ,h;
    for(i = 0; i < (*count) - 1; i++)
    {
        j = i + 1;
        while(j < (*count))
        {
            if(temp[i] == temp[j])
            {
                for(h = j; h < (*count) - 1; h++)
                {
                    temp[h] = temp[h + 1];

                }
                *count = *count - 1;
            }
            j = j + 1;
        }
    }
}

//-- Average the progress of Employees when participating in the same project --
void averageX(progress_t progress[], FILE *outfile, int number, int value4)
{
    int i, count = 0;
    float sum = 0, S, value2;


    for (i = 0; i < value4; i++)
    {
        value2 = atof(progress[i].progress);
        if(atoi(progress[i].projectID) == number)
        {
            sum = sum + value2;
            count++;
        }    
    }
    if(count == 0)
    {
        fprintf(outfile, "0");
    }
    else
    {
        S = sum / count;
        fprintf(outfile, "%.3f", S);
    }

}

//------------------------ Function to swap positions --------------------------
void swap(employee_t *a, employee_t *b)
{
    employee_t temp = *a;
    *a = *b;
    *b = temp;
}

//-------------- Function to sort Employees in alphabetical order --------------
void sortAsc(employee_t employees[], FILE *outfile, int value5)
{
    int i, j;
    char check[20], check1[20], check2[20], check3[20];

    for(i = 0; i < value5; i++)
    {
        for(j = i + 1; j < value5; j++)
        {
            strcpy(check, employees[i].lastName);
            strcpy(check1, employees[i].firstName);   
            strcpy(check2, employees[j].lastName);            
            strcpy(check3, employees[j].firstName);
            lowerCase(check);
            lowerCase(check1);
            lowerCase(check2);
            lowerCase(check3);
            if(strcmp(check, check2) > 0)
            {
                swap(&employees[i], &employees[j]);
            }
            else
            {
                if(strcmp(check, check2) == 0)
                {
                    if(strcmp(check1, check3) > 0)
                    {
                        swap(&employees[i], &employees[j]);
                    }
                }
            }
        }
    }
    for (i = 0; i < value5; i++)
    {
        fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);      
    }
}

//--------- Function to sort Employees in reverse alphabetical order -----------
void sortDesc(employee_t employees[], FILE *outfile, int value6)
{
    int i, j;
   char check[20], check1[20], check2[20], check3[20];

    for(i = 0; i < value6; i++)
    {
        for(j = i + 1; j < value6; j++)
        {
            strcpy(check, employees[i].lastName);
            strcpy(check1, employees[i].firstName);   
            strcpy(check2, employees[j].lastName);            
            strcpy(check3, employees[j].firstName);
            lowerCase(check);
            lowerCase(check1);
            lowerCase(check2);
            lowerCase(check3);
            if(strcmp(check, check2) < 0)
            {
                swap(&employees[i], &employees[j]);
            }
            else
            {
                if(strcmp(check, check2) == 0)
                {
                    if(strcmp(check1, check3) > 0)
                    {
                        swap(&employees[i], &employees[j]);
                    }
                }
            }
        }
    }
    for (i = 0; i < value6; i++)
    {
        fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);      
    }   
}

//------------- Function to find Employees from the same country ---------------
void countryName(employee_t employees[], FILE *outfile, char stringSecond[], int value7)
{
    int i;
    char temp[MAX];
    printf("%s\n", stringSecond);
    for (i = 0; i < value7; i++)
    {
        strcpy(temp, employees[i].country);
        lowerCase(temp);
        if (strcmp(stringSecond, temp) == 0)
        {
            fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);
        }
    }
}