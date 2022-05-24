// #include <stdio.h>
// #include <string.h>

// char inHoaKyTuDau(char s[])
// {
//     int i;

//     if(s[0]!=' ')
//     {
//         s[0]=s[0]-32;
//         for(i=1;i<strlen(s);i++)
//         {
//             if(s[i]==' ' && s[i+1]!=' ' && s[i+1]>='a' && s[i+1]<='z' )
//             {
//                 s[i+1]=s[i+1]-32;
//             }         
//         }
//     }
//     else
//     {
//         for(i=0;i<strlen(s);i++)
//         {
//             if(s[i]==' ' && s[i+1]!=' ' && s[i+1]>='a' && s[i+1]<='z' )
//             {
//             s[i+1]=s[i+1]-32;
//             }          
//         }
//     }
//     // printf("%s",s);
// }

// int main()
// {
// 	char stringSeconds[100];
// 	printf("%s",stringSeconds);
// 	gets(stringSeconds);

// 	inHoaKyTuDau(stringSeconds);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 200
#define MAX2 630

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

typedef struct
{
    char employeeID2[MAX2];
    char projectID[MAX2];
    char progress[MAX2];
} progress_t;
void convertToLower(char *string);
int countDepartment(employee_t employees[], FILE *outfile, FILE *checkfile, char department[]);
void listMale(employee_t employees[], FILE *outfile);
void listFemale(employee_t employees[], FILE *outfile);
void reportN(progress_t progress[], FILE *outfile, float n);
void averageX(progress_t progress[], FILE *outfile, int x);
void sortAsc(employee_t employees[], FILE *outfile, int value5);
void swap(char *string1, char *string2);
// void swap(employee_t *string1, employee_t *string2);
void countryName(employee_t employees[], FILE *outfile, char name[]);
char* copyString(char s[]);
int main()
{
    FILE *infile;
    FILE *infile2;
    FILE *outfile;
    FILE *checkfile;
    infile = fopen("Employee.csv", "r");
    infile2 = fopen("Progress.csv", "r");
    outfile = fopen("result.csv", "w");
    checkfile = fopen("check.txt", "w");

    if (!infile)
    {
        printf("Can not open file\n");
        return 0;
    }
    if (!infile2)
    {
        printf("Can not open file \n");
        return 0;
    }

    char buf[MAX];
    int column;
    int row = 0;
    int i = 0;
    employee_t employees[MAX];

    while (fgets(buf, MAX, infile) != NULL)
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
            }
            if (column == 1)
            {
                strcpy(employees[i].firstName, temp);
            }
            if (column == 2)
            {
                strcpy(employees[i].lastName, temp);
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

    char buffer[MAX2];
    int column2;
    int row2 = 0;
    int s;
    progress_t progress[MAX2];

    while (fgets(buffer, MAX2, infile2) != NULL)
    {
        column2 = 0;
        row2++;
        if(row2 == 1)
        {
            continue;
        }
        char *tmp = strtok(buffer, ",");
        while (tmp)
        {
            if(column2 == 0)
            {
                strcpy(progress[s].employeeID2, tmp);
            }
            if(column2 == 1)
            {
                strcpy(progress[s].projectID, tmp);
            }
            if (column2 == 2)
            {
                strcpy(progress[s].progress, tmp);
            }
            tmp = strtok(NULL, ",");
            column2++;
        }
        s++;
    }
    char stringFirst[10];
    scanf("%s", &stringFirst);
    char department[10];
    int j;
    int x;
    // char n[5];
    float n;
    char stringFeMale[10];
    char asc[10];
    char name[10];
    // convertToLower(string);
    for (j = 0; j <= strlen(stringFirst); j++)
    {
        if (stringFirst[j] >= 65 && stringFirst[j] <= 90)
        {
            stringFirst[j] = stringFirst[j] + 32;
        }
    }
    if (strcmp(stringFirst, "count") == 0)
    {
        scanf("%s", &department);
        // if(department < 0)
        // {
        //     fprintf(checkfile, "%s", "wrong syntax");
        // }
        // else
        // {
        fprintf(outfile, "%d",countDepartment(employees, outfile, checkfile, department));
        //}
    }
    if (strcmp(stringFirst, "list") == 0)
    {
        scanf("%s", &stringFeMale);
        convertToLower(stringFeMale);
        if(strcmp(stringFeMale,"male") != 0 || strcmp(stringFeMale,"female") != 0)
        {
            fprintf(checkfile, "%s", "wrong syntax");
        }
        if(strcmp(stringFeMale, "male") == 0)
        {
            listMale(employees, outfile);
        }
        if(strcmp(stringFeMale, "female") == 0)
        {
            listFemale(employees, outfile);
        }
    }
    if(strcmp((stringFirst), "report") == 0)
    {
        scanf("%f", &n);
        if(n < 0 || n > 1)
        {
            fprintf(checkfile, "%s", "wrong syntax");
        }
        else
        {
            reportN(progress, outfile, n);
        }
    }
    if(strcmp((stringFirst), "average") == 0)
    {
        scanf("%d", &x);
        averageX(progress, outfile, x);
    }
    if(strcmp((stringFirst), "sort") == 0)
    {
        scanf("%s", &asc);
        convertToLower(asc);
        if(strcmp(asc, "asc") == 0)
        {
            sortAsc(employees, outfile, i);
        }
        // if(strcmp(asc, "desc") == 0)
        // {
        //     listFemale(employees, outfile);
        // }
    }
    if(strcmp((stringFirst), "country") == 0)
    {
        scanf("%s", &name);

        // if(strcmp(asc, "asc") == 0)
        // {
        countryName(employees, outfile, name);
        //}
        // if(strcmp(asc, "desc") == 0)
        // {
        //     listFemale(employees, outfile);
        // }
    }

    fclose(infile);
    fclose(infile2);
    fclose(outfile);
    fclose(checkfile);
    return 0;
}

void convertToLower(char *string) {
	int i;
    for(i=0;i<=strlen(string);i++)
    {
        if(string[i] >= 65 && string[i] <= 90)
        {
            string[i] = string[i]+32;
        }
    }
}
int countDepartment(employee_t employees[], FILE *outfile, FILE *checkfile, char department[])
{
    int i;
    int count = 0;
    for (i = 0; i < MAX; i++)
    {
        if (atoi(department) == atoi(employees[i].department))
        {
            count++;
        }
    }
    return count;
}

void listMale(employee_t employees[], FILE *outfile)
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        if (strcmp("Male", employees[i].gender) == 0)
        {
            fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);
        }
    }
}
void listFemale(employee_t employees[], FILE *outfile)
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        if (strcmp("Female", employees[i].gender) == 0)
        {
            fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);
        }
    }
}
void reportN(progress_t progress[], FILE *outfile, float n)
{
    float arrayProgress[MAX2];
    int i;
    for(i = 0; i < MAX2; i++)
    { 
		arrayProgress[i] =  atof(progress[i].progress);
        if (n == arrayProgress[i])
        {
            fprintf(outfile, "%s\n", progress[i].employeeID2);
        }
    }
}

void averageX(progress_t progress[], FILE *outfile, int x)
{
    int i;
    float average = 0;
    int count = 0;
	float result;
    for(i = 0; i < MAX2; i++)
    {
        if(x == atoi(progress[i].projectID))
        {
            average += atof(progress[i].progress);
			count++;
        }
    }
	result = average/count;
    fprintf(outfile,"%.3f", result);
}
// void swap(employee_t *string1, employee_t *string2)
// {
//     employee_t temp = *string1;
//     *string1 = *string2;
//     *string2 = temp;
    
// }
// void sortAsc(employee_t employees[], FILE *outfile, int value5)
// {
//     int i, j;

//     for(i = 0; i < value5; i++)
//     {
//         for(j = i + 1; j < value5; j++)
//         {
//             if(strcmp(employees[i].lastName, employees[j].lastName) > 0)
//             {
//                 swap(&employees[i], &employees[j]);
//             }
//             else
//             {
//                 if(strcmp(employees[i].lastName, employees[j].lastName) == 0)
//                 {
//                     if(strcmp(employees[i].firstName, employees[j].firstName) > 0)
//                     {
//                         swap(&employees[i], &employees[j]);
//                     }
//                 }
//             }
//         }
//     }
//     for (i = 0; i < value5; i++)
//     {
//         fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);      
//     }
// }
void swap(char *string1, char *string2)
{
    char temp[25];
    strcpy(temp,string1);
    strcpy(string1,string2);
    strcpy(string2,temp);
}
void sortAsc(employee_t employees[], FILE *outfile, int value5)
{
    int i, j, m;
    
    for(i = 0; i < 200; i ++)
    {
        for(j = i+1; j < 200; j++)
        {
            if(strcmp(employees[i].lastName,employees[j].lastName)>0)
            {
                swap(employees[i].lastName,employees[j].lastName);
                // swap(employees[i].firstName,employees[j].firstName);
                // swap(employees[i].firstName,employees[j].gender);
            }
        }
        //swap(employees[i].lastName,employees[m].lastName);
    }
    for(i = 0; i < value5; i ++)
    {
        fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);
    }
}
void countryName(employee_t employees[], FILE *outfile, char name[])
{
    int i, len;
    char s[]= "\n";
    char *country = strcat(name , s);
    for (i = 0; i < MAX; i++)
    {
        if (strcmp(country, employees[i].country) == 0)
        {
            fprintf(outfile, "%s,%s,%s,%s,%s,%s,%s", employees[i].employeeID, employees[i].firstName, employees[i].lastName, employees[i].gender, employees[i].dateOfBirth, employees[i].department, employees[i].country);
        }
    }
}