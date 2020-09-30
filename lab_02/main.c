#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RESET "\x1b[0m"


#define OK 0
#define ERROR 1


#define INV_NUMBER_CHOICE 2
#define DONT_INT_NUM_CHOICE 3
#define ERROR_INPUT 7
#define ERROR_FIND 8
#define FILE_ERROR 4
#define NAME_FILE "C:/msys64/home/Ira/tads/lab_02/flat.txt"
#define ERROR_READ_FILE 5
#define SIZE_FILE 100
#define MIN_NUM_HOME 1
#define MAX_NUM_HOME 999
#define MAX_ARRR 999
#define MIN_ARRR 1
#define MAX_SIZE 100
#define MIN_YEAR 1930
#define MAX_YEAR 2020
#define MIN_OWNER 1
#define MAX_OWNER 15
#define MIN_TEN 1
#define MAX_TEN 15
#define MAX_ROOM 20
#define MIN_ROOM 1
#define MAX_PRICE 1000000
#define MIN_PRICE 1
#define EMPTY_TABLE 6

typedef short int func_var;

typedef enum BOOLEAN{false = 0, true = 1} boolean;

typedef struct primary
{
    boolean decoration;
}primary_r;

typedef struct secondary
{
       func_var build_time;
       func_var previous_own_count;
       func_var last_tenants_count;
       boolean animals;
} secondary_r;

typedef union prim_sec
{
    primary_r primary;
    secondary_r second;
} prim_sec_r;

typedef struct keys
{
    func_var room;
    func_var id;
} key_r;

typedef struct appartment
{
    char address[101];
    func_var arrr;
    func_var room;
    int square;
    boolean is_prim_sec;
    prim_sec_r flat;
} appartment_r;

typedef struct table
{
    appartment_r appar[100];
    key_r key[100];
    func_var size;
    func_var size_max;
} table_r;

void print_hello()
{
    printf(COLOR_GREEN"%s"COLOR_RESET"%s",
           "\nThis program allows you to: \n",
           " - compare the time taken to sort the table by sorts;\n"
           " - with asymptotic complexities O(n^2) and O(nlogn);\n"
           " - add the entry entered by the user to the end of the"
           " table;\n"
           " - delete an entry from the table by the value of the"
           " specified field;\n"
           " - view the sorted key table when the source table "
           "is unsorted;\n"
           " - output an ordered source table;\n"
           " - output the source table in an ordered form using "
           "an ordered key table;\n"
           " - display the results of using different sorting "
           "algorithms;\n\n\n");

    printf("%s",
           "1 - To upload a table from a file.\n"
           "2 - Display the uploaded table.\n"
           "3 - Add an entry to the table.\n"
           "4 - Delete an entry from the table /////////////.\n"
           "5 - Sort the key table by sorting O(n^2).\n"
           "6 - sort the key table by sorting O(nlogn).\n"
           "7 - Output the key table.\n"
           "8 - //////O(n^2).\n"
           "9 - //// O(nlogn).\n"
           "10 - Output the source table using an ordered key table.\n"
           "11 - Output a comparison of the table sorting time by sorting with\n"
           "complexities O(n^2) and O(nlogn) and comparing the time of normal sorting and sorting using\n"
           "an array of keys.\n"
           "12 - ////////////////\n\n"
           "0 - Program exit.\n");
}
void printf_input()
{
    printf(COLOR_YELLOW"%s"COLOR_RESET"%s","\n\nFor help input 10", "\nINPUT YOUR CHOICE: ");
}
void clean_()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

func_var size_check(func_var size)
{
    if (!size)
    {
        fprintf(stderr, "Пустая");
        return EMPTY_TABLE;
    }

    return OK;
}

func_var check_number(func_var *const number, const func_var l, const func_var r)
{
    if (scanf("%hd", number) != 1)
    {
        clean_();
        return DONT_INT_NUM_CHOICE;
    }

    if (*number < l || *number > r)
    {
        clean_();
        return INV_NUMBER_CHOICE;
    }

    return OK;
}

void clean_tab(table_r *const table)
{
    for (func_var i = 0; i < table->size; i++)
    {
        table->key[i].id = 0;
        table->appar[i].address[0] = '\0';
    }
}
func_var file_size(table_r *table, FILE *f)
{
    if (fscanf(f, "%hd", &table->size) != 1)
        return ERROR_READ_FILE;

    if (table->size < 1 || table->size > SIZE_FILE)
        return FILE_ERROR;

    return OK;
}
void  gluing_address(table_r *table, char *city, char *street,
                     func_var num_home, func_var app, func_var i)
{
    char num_home_str[4], app_str[4];

    sprintf(num_home_str, "%d", num_home);
    sprintf(app_str, "%d", app);

    strcat(table->appar[i].address, city);
    strcat(table->appar[i].address, ", ");
    strcat(table->appar[i].address, street);
    strcat(table->appar[i].address, " ");
    strcat(table->appar[i].address, num_home_str);
    strcat(table->appar[i].address, " ");
    strcat(table->appar[i].address, app_str);
    strcat(table->appar[i].address, "\0");

}
func_var read_address(table_r *table, FILE *f, func_var i)
{
    char city[101], street[101], ch[10];
    int num_home, app;

    if (!f->_file)
        printf("Specify the city where the apartment is located \n"
               "(only in Latin, without spaces (1 to 50)): ");
    if (fscanf(f, "%50s", city) != 1)
    {
        fprintf(stderr, "Invalid ciy entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file && fscanf(f, "%s", ch) == 1)
    {
        fprintf(stderr, "Invalid ciy entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Specify the street where the apartment is located \n"
               "(only in Latin, without spaces (1 to 50)): ");
    if (fscanf(f, "%50s", street) != 1)
    {
        fprintf(stderr, "Invalid street entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the house number (from 1 to 999): ");
    if (fscanf(f, "%d", &num_home) != 1)
    {
        fprintf(stderr, "Invalid house number entered.\n");
        return ERROR_READ_FILE;
    }
    if (num_home < MIN_NUM_HOME || num_home > MAX_NUM_HOME)
    {
        fprintf(stderr, "Invalid house number entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the apartment number (from 1 to 999): ");
    if (fscanf(f, "%d", &app) != 1)
    {
        fprintf(stderr, "Invalid appartment number entered.\n");
        return ERROR_READ_FILE;
    }
    if (app < MIN_NUM_HOME || app > MAX_NUM_HOME)
    {
        fprintf(stderr, "Invalid appartment number entered.\n");
        return ERROR_READ_FILE;
    }

     gluing_address(table, city, street, num_home, app, i);

     return OK;
}

func_var read_other(table_r *table, FILE *f, func_var i)
{
    func_var primary;

    if (!f->_file)
        printf("Enter the total area of the apartment in square meters (from 1 to 999): ");
    if (fscanf(f, "%hd", &table->appar[i].arrr) != 1)
    {
        fprintf(stderr, "Incorrect area size entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].arrr > MAX_ARRR || table->appar[i].arrr < MIN_ARRR)
    {
        fprintf(stderr, "Incorrect area size entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the number of rooms (from 1 to 20): ");
    if (fscanf(f, "%hd", &table->appar[i].room) != 1)
    {
        fprintf(stderr, "Invalid number of rooms entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].room > 20 || table->appar[i].room < 1)
    {
        fprintf(stderr, "Invalid number of rooms entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the cost per square meter in thousand rubles (from 1 to 1 000 000): ");
    if (fscanf(f, "%d", &table->appar[i].square) != 1)
    {
        fprintf(stderr, "Incorrect price per square meter entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].square > 1000000 || table->appar[i].square < 1)
    {
        fprintf(stderr, "Incorrect price per square meter entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Specify whether the housing is primary. Enter 1 if Yes and 0 if no: ");
    if (fscanf(f, "%hd", &primary) != 1)
    {
        fprintf(stderr, "Invalid attribute entered.\n");
        return ERROR_READ_FILE;
    }
    if (primary > 1 || primary < 0)
    {
        fprintf(stderr, "Invalid attribute entered.\n");
        return ERROR_READ_FILE;
    }

    table->appar[i].is_prim_sec = (primary) ? true : false;

    return OK;
}

func_var read_primary(table_r *table, FILE *f, func_var i)
{
    func_var decor;

    if (!f->_file)
        printf("Specify whether the apartment has finishing\n"
               "Enter 1 if Yes and 0 if no.");
    if (fscanf(f, "%hd", &decor) != 1)
    {
        fprintf(stderr, "Invalid attribute entered.");
        return ERROR_READ_FILE;
    }
    if (decor < false || decor > true)
    {
        fprintf(stderr, "Invalid attribute entered.");
        return ERROR_READ_FILE;
    }

    table->appar[i].flat.primary.decoration = (decor) ? true : false;

    return OK;

}

func_var read_secondary(table_r *const table, FILE *f, func_var i)
{
    func_var animal;

    if (!f->_file)
        printf("Enter the year of construction: ");
    if (fscanf(f, "%hd", &table->appar[i].flat.second.build_time) != 1)
    {
        fprintf(stderr, "Incorrect year of construction entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].flat.second.build_time < MIN_YEAR ||
        table->appar[i].flat.second.build_time > MAX_YEAR)
    {
        fprintf(stderr, "Incorrect year of construction entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the number of previous owners: ");
    if (fscanf(f, "%hd", &table->appar[i].flat.second.previous_own_count) != 1)
    {
        fprintf(stderr, "Incorrect number of previous owners entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].flat.second.previous_own_count < MIN_OWNER ||
        table->appar[i].flat.second.previous_own_count > MAX_OWNER)
    {
        fprintf(stderr, "Incorrect number of previous owners entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the number of previous residents: ");
    if (fscanf(f, "%hd", &table->appar[i].flat.second.last_tenants_count) != 1)
    {
        fprintf(stderr, "Incorrect number of previous tanents entered..\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].flat.second.last_tenants_count < MIN_TEN ||
        table->appar[i].flat.second.last_tenants_count > MAX_TEN)
    {
        fprintf(stderr, "Incorrect number of previous tanents entered..\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the \"was there an animal\" attribute (1 if Yes 0 if no): ");
    if (fscanf(f, "%hd", &animal) != 1)
    {
        fprintf(stderr, "Invalid attribute entered..\n");
        return ERROR_READ_FILE;
    }
    if (animal < false || animal > true)
    {
        fprintf(stderr, "Invalid attribute entered..\n");
        return ERROR_READ_FILE;
    }

    table->appar[i].flat.second.animals = (animal) ? true : false;

    return OK;

}

func_var load_in_file(table_r *table, FILE *f, func_var s, func_var e)
{
    func_var rc;

    for (func_var i = s; i < e; i++)
    {
        rc = read_address(table, f, i);

        if (rc)
            return rc;

        rc = read_other(table, f, i);

        if (rc)
            return rc;

        if (table->appar[i].is_prim_sec)
            rc = read_primary(table, f, i);
        else
            rc = read_secondary(table, f, i);

        table->key[i].id = i;
        table->key[i].room = table->appar[i].room;
    }

    return OK;
}
func_var parsing_from_file(table_r *table)
{
    FILE *f = NULL;

    clean_tab(table);

    f = fopen(NAME_FILE, "r");

    if (f == NULL)
        return FILE_ERROR;

    if (file_size(table, f) != OK)
        return FILE_ERROR;

    func_var rc = load_in_file(table, f, 0, table->size);

    if (rc)
        return rc;

    fclose(f);

    return OK;
}

func_var add_flat_end(table_r *const table)
{
    if (table->size + 1 == MAX_SIZE)
    {
        fprintf(stderr, "Unable to add, table is full\n");
        return ERROR;
    }

    func_var rc = load_in_file(table, stdin, table->size, table->size + 1);

    if (rc)
        return rc;

    ++(table->size);

    printf("Flat add to end table");

    return OK;
}


void print_table(const table_r table, boolean keys)
{
    printf("\n");

    printf("%30s %8s %7s %10s %15s\n", "Address", "Square", "Rooms",
           "Price", "Primacy");
    printf("%74s %4s\n", "Yes", "Decor");
    printf("%74s %4s %10s %10s %7s\n", "No", "time", "Owner", "Tenants", "Animal");
    for (func_var i = 0; i < table.size; i++)
    {
        func_var k = (keys) ? table.key[i].id : i;

        printf("%30s %8hd %7hd %10d %15s", table.appar[k].address,
               table.appar[k].arrr, table.appar[k].room,
               table.appar[k].square, (table.appar[k].is_prim_sec) ? "Yes" : "No");

        if (table.appar[k].is_prim_sec)
            printf(" %4s\n", (table.appar[k].flat.primary.decoration) ? "Yes" : "No");
        else
            printf(" %4hd %10hd %10hd %7s\n", table.appar[k].flat.second.build_time,
                   table.appar[k].flat.second.previous_own_count,
                   table.appar[k].flat.second.last_tenants_count,
                   (table.appar[k].flat.second.animals) ? "Yes" : "No");

    }
}
void print_keys(const table_r table)
{
    printf("%4s %7s", "Key", "Rooms\n");
    for (func_var i = 0; i < table.size; i++)
    {
        printf("%4hd %7hd\n", table.key[i].id, table.key[i].room);
    }
}
func_var input_room_delet(func_var *room)
{
    printf("Enter the number of apartments that you want to remove from the list (from 1 to 20): ");
    if (scanf("%hd", room) != 1)
    {
        printf("Invalid apartment number entered.\n");
        return ERROR_INPUT;
    }

    if (*room < MIN_ROOM || *room > MAX_ROOM)
    {
        printf("Invalid apartment number entered.\n");
        return ERROR_INPUT;
    }

    return OK;
}

void delet_pos(table_r *const table, func_var k, func_var del_id)
{
    for (func_var i = del_id; i < table->size - 1; i++)
    {
        table->appar[i] = table->appar[i + 1];
        table->key[i].id--;
    }

    for (func_var i = k; i < table->size - 1; i++)
        table->key[i] = table->key[i + 1];

    --table->size;
}
func_var find_to_del_room(table_r *const table, func_var room)
{
    func_var i = 0;

    for (func_var k = 0; k < table->size; k++)
    {
        if (table->key[k].room == room)
        {
            i++;
            delet_pos(table, k, table->key[k].id);
            k--;
        }
    }

    return (i) ? OK : ERROR_FIND;
}
func_var delet_record_room(table_r *const table)
{
    func_var room;

    if (size_check(table->size))
    {
        printf("Table is empty");
        return EMPTY_TABLE;
    }

    if (input_room_delet(&room))
    {
        printf("Invalid apartment number entered.\n");
        return ERROR_INPUT;
    }

    if (find_to_del_room(table, room))
    {
        fprintf(stderr, "There are no apartments with this number.\n");
        return ERROR_FIND;
    }

    printf("All apartments with the entered number have been deleted.\n");

    return OK;
}

int compare_key(const void *v1, const void *v2)
{
    return ((key_r*)(v1))->room - ((key_r*)(v2))->room;
}
int compare_table(const void *v1, const void *v2)
{
    return ((appartment_r*)(v1))->room - ((appartment_r*)(v2))->room;
}
void swap(boolean table, void *v1, void *v2)
{
    if (!table)
    {
        appartment_r buf = *(appartment_r*)v1;
        *(appartment_r*)v1 = *(appartment_r*)v2;
        *(appartment_r*)v2 = buf;

    }
    else
    {
        key_r buf = *(key_r*)v1;
        *(key_r*)v1 = *(key_r*)v2;
        *(key_r*)v2 = buf;
    }
}
void bubble_sort(const func_var size, void *aa, func_var (*compare)(const void *v1, const void *v2),
                 boolean table, size_t byte_size)
{
    char *a = (char*)aa;
    for (func_var i = 0; i < (func_var)(size * byte_size - byte_size); i += byte_size)
    {
        for (func_var j = 0; j < (func_var)(size * byte_size - i - byte_size); j += byte_size)
        {
            if (compare((a + j), (a + j + byte_size)))
            {
                swap(table, a + j, a + j + byte_size);
            }
        }
    }
}

func_var do_action(func_var code_act, table_r *table)
{
    func_var rc;

    //system("cls");

    switch (code_act)
    {
        case 1:
            rc = parsing_from_file(table);
            if (rc)
                return rc;
            printf("Data is loaded into the table");
            printf("1");
            break;

        case 2:
            code_act = add_flat_end(table);
            printf("2");
            break;

        case 3:
            code_act = delet_record_room(table);
            printf("3");
            break;

        case 4:
            if (size_check(table->size))
                return EMPTY_TABLE;

            if (input_ch_sort() == 1)
            {

                qsort(table->key, table->size, sizeof(table->key[0]), compare_key);
                print_keys(*table);
                printf("4 SORTED\n");
            }
            else if (input_ch_sort() == 2)
            {
                bubble_sort(table->size, table->key, compare_key, false, sizeof(table->key[0]));

            }
            break;

        case 5:
            if (size_check(table->size))
                return EMPTY_TABLE;
            qsort(table->appar, table->size, sizeof(table->appar[0]), compare_table);
            print_table(*table, false);
            printf("5");
            break;

        case 6:
            if (size_check(table->size))
                return EMPTY_TABLE;
            qsort(table->key, table->size, sizeof(table->key[0]), compare_key);
            print_table(*table, true);
            printf("6");
            break;

        case 7:
            printf("7");
            break;

        case 8:

            printf("8");
            break;

        case 9:
            if (size_check(table->size))
                return EMPTY_TABLE;
            print_table(*table, false);
            printf("9");
            break;
        case 10:
            print_hello();
    }
    return OK;
}

int main()
{
    system("cls");

    print_hello();
    func_var num_command = -1;

    while (num_command != 0)
    {
        printf_input();
        if (check_number(&num_command, 0, 12) != OK)
        {
            printf("Invalid command entered, please re-enter!!!\n");

            print_hello();
        }
        else
        {
            table_r table;
            func_var code_err = do_action(num_command, &table);

            printf("%d", code_err);
            if (code_err)
            {
                return code_err;
            }
        }
    }

    return OK;
}
