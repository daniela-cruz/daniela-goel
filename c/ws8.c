#include <stdio.h> /* printf */
#include <stdlib.h> /* alloc */
#include <string.h> /* strlen */

enum {Failure, Success};

typedef struct DateOfBirth 
{
	size_t day;
	size_t month;
	size_t year;
} dob_t;

typedef struct contact 
{
	char f_name[50];
	char l_name[50];
	dob_t date;
	size_t id;
} contact_t;

void CreateContactsFile();
contact_t *ReadFileToNewStruct(const char *name);

int main()
{
	CreateContactsFile();
	
	return 0;
}

void CreateContactsFile()
{
	contact_t contacts[] = {
							{"Daniela ",  "Goel",  {5, 3, 1984}, 39456314},
							{"Daniel",  "Soifer",  {1, 1, 1998}, 318651643},
							{"Alex ",  "Burstein", {9, 12, 1985}, 307558114},
							{"Nitzan",  "Izhaki",  {1, 1, 1991}, 201630225},
							{"Hay ",  "Hoffman",  {1, 1, 1992}, 203265186},
							{"Mai ",  "Aloni",  {14, 7, 1993}, 309651107},
							{"Dor ",  "Tambour",  {15, 4, 1992}, 203516208},
							{"Omri ",  "Roimi",  {1, 1,1986}, 301722864}};
	contact_t *contacts_2;
	FILE *file_name;
	const char *name = "infinity_contacts.txt";
	
	file_name = fopen(name, "w+");
	
	if (NULL != file_name)
	{
		fwrite(contacts, sizeof(contact_t), sizeof(contacts), file_name);
		fclose(file_name);
	}
	else
	{
		printf("Error: unable to open file.");
	}
	
	contacts_2 = ReadFileToNewStruct(name);
	printf("Name: %s \n", contacts_2->f_name);
	
	free(contacts_2);
}

contact_t *ReadFileToNewStruct(const char *name)
{
	contact_t contacts_2[8];
	contact_t *new_contacts;
	FILE *file_name;
	
	new_contacts = (contact_t *)malloc(sizeof(contacts_2) * sizeof(contact_t));
	
	if (NULL != name)
	{
		file_name = fopen(name, "r");
		fread(contacts_2, sizeof(contact_t), sizeof(contacts_2), file_name);
		printf("Name: %s \n", contacts_2[7].f_name);
		fclose(file_name);
	}
	else
	{
		printf("Error: unable to open file.");
	}
	
	new_contacts = contacts_2;
	
	return new_contacts;
}
