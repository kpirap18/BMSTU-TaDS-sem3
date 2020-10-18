#include "read.h"

/*!
 * \brief gluing_address - Connecting an address to a single line.
 * \param *table - A pointer to a table.
 * \param *city, *street - A pointer to a city and a street.
 * \param num_home, app - number of house and flat.
 * \param i - Position in the table.
 * \return OK if all is well, otherwise some ERROR_.
 */
void gluing_address(table_r *table, char *city, char *street,
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

/*!
 * \brief read_address - Reading an address.
 * \param *table - A pointer to a table.
 * \param *f - A pointer to a file.
 * \param i - Position in the table.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var read_address(table_r *table, FILE *f, func_var i)
{
    char city[101], street[101], ch[10];
    int num_home, app;

    if (!f->_file)
    {
        printf("Specify the city where the apartment is located \n"
                   "(only in Latin, without spaces ( length 1 to 50)): ");
        fflush(stdin);
        char *rc = fgets(city, 52, f);
        if (rc == NULL || city[0] == '\n')
        {
            printf("Invalid city enteredt.\n");
            return ERROR_READ_FILE;
        }
        else
        {
            if (city[strlen(city) - 1] != '\n')
            {
                if (fscanf(f, "%s", ch))
                {
                    printf("Invalid city entered.\n");
                    return ERROR_READ_FILE;
                }
            }
            else
                city[strlen(city) - 1] = '\0';
        }
    }
    else
    {
        if (fscanf(f, "%50s", city) != 1)
        {
            printf("Invalid city entered.\n");
            return ERROR_READ_FILE;
        }
    }
    if (!f->_file)
    {
        printf("Specify the street where the apartment is located \n"
                   "(only in Latin, without spaces (length 1 to 50)): ");
        fflush(stdin);
        char *rc = fgets(street, 52, f);
        if (rc == NULL || street[0] == '\n')
        {
            printf("Invalid street entered.\n");
            return ERROR_READ_FILE;
        }
        else
        {
            if (street[strlen(street) - 1] != '\n')
            {
                if (fscanf(f, "%s", ch))
                {
                    printf("Invalid street entered.\n");
                    return ERROR_READ_FILE;
                }
            }
            else
                street[strlen(city) - 1] = '\0';
        }
    }
    else
    {
        if (fscanf(f, "%50s", street) != 1)
        {
            printf("Invalid street entered.\n");
            return ERROR_READ_FILE;
        }
    }
    if (!f->_file)
        printf("Enter the house number (from 1 to 999): ");
    if (fscanf(f, "%d", &num_home) != 1)
    {
        printf("Invalid house number entered.\n");
        return ERROR_READ_FILE;
    }
    if (num_home < MIN_NUM_HOME || num_home > MAX_NUM_HOME)
    {
        printf("Invalid house number entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the apartment number (from 1 to 999): ");
    if (fscanf(f, "%d", &app) != 1)
    {
        printf("Invalid appartment number entered.\n");
        return ERROR_READ_FILE;
    }
    if (app < MIN_NUM_HOME || app > MAX_NUM_HOME)
    {
        printf("Invalid appartment number entered.\n");
        return ERROR_READ_FILE;
    }

     gluing_address(table, city, street, num_home, app, i);

     return OK;
}

/*!
 * \brief read_other - Reading other data.
 * \param *table - A pointer to a table.
 * \param *f - A pointer to a file.
 * \param i - Position in the table.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var read_other(table_r *table, FILE *f, func_var i)
{
    func_var primary;

    if (!f->_file)
        printf("Enter the total area of the apartment in square meters (from 1 to 999): ");
    if (fscanf(f, "%hd", &table->appar[i].arrr) != 1)
    {
        printf("Incorrect area size entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].arrr > MAX_ARRR || table->appar[i].arrr < MIN_ARRR)
    {
        printf("Incorrect area size entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the number of rooms (from 1 to 20): ");
    if (fscanf(f, "%hd", &table->appar[i].room) != 1)
    {
        printf("Invalid number of rooms entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].room > 20 || table->appar[i].room < 1)
    {
        printf("Invalid number of rooms entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the cost per square meter in thousand rubles (from 1 to 1 000 000): ");
    if (fscanf(f, "%d", &table->appar[i].square) != 1)
    {
        printf("Incorrect price per square meter entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].square > 1000000 || table->appar[i].square < 1)
    {
        printf("Incorrect price per square meter entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Specify whether the housing is primary. Enter 1 if Yes and 0 if no: ");
    if (fscanf(f, "%hd", &primary) != 1)
    {
        printf("Invalid attribute entered.\n");
        return ERROR_READ_FILE;
    }
    if (primary > 1 || primary < 0)
    {
        printf("Invalid attribute entered.\n");
        return ERROR_READ_FILE;
    }

    table->appar[i].is_prim_sec = (primary) ? true : false;

    return OK;
}

/*!
 * \brief read_primary - Reading data of the primary housing.
 * \param *table - A pointer to a table.
 * \param *f - A pointer to a file.
 * \param i - Position in the table.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var read_primary(table_r *table, FILE *f, func_var i)
{
    func_var decor;

    if (!f->_file)
        printf("Specify whether the apartment has primary\n"
               "Enter 1 if Yes and 0 if no: ");
    if (fscanf(f, "%hd", &decor) != 1)
    {
        printf("Invalid attribute entered.");
        return ERROR_READ_FILE;
    }
    if (decor < false || decor > true)
    {
        printf("Invalid attribute entered.");
        return ERROR_READ_FILE;
    }

    table->appar[i].flat.primary.decoration = (decor) ? true : false;

    return OK;

}

/*!
 * \brief read_secondary - Reading data of the secondary housing.
 * \param *table - A pointer to a table.
 * \param *f - A pointer to a file.
 * \param i - Position in the table.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var read_secondary(table_r *const table, FILE *f, func_var i)
{
    func_var animal;

    if (!f->_file)
        printf("Enter the year of construction (1930..2020): ");
    if (fscanf(f, "%hd", &table->appar[i].flat.second.build_time) != 1)
    {
        printf("Incorrect year of construction entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].flat.second.build_time < MIN_YEAR ||
        table->appar[i].flat.second.build_time > MAX_YEAR)
    {
        printf("Incorrect year of construction entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the number of previous owners (1 to 15): ");
    if (fscanf(f, "%hd", &table->appar[i].flat.second.previous_own_count) != 1)
    {
        printf("Incorrect number of previous owners entered.\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].flat.second.previous_own_count < MIN_OWNER ||
        table->appar[i].flat.second.previous_own_count > MAX_OWNER)
    {
        printf("Incorrect number of previous owners entered.\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the number of previous residents (1 to 15): ");
    if (fscanf(f, "%hd", &table->appar[i].flat.second.last_tenants_count) != 1)
    {
        printf("Incorrect number of previous tanents entered..\n");
        return ERROR_READ_FILE;
    }
    if (table->appar[i].flat.second.last_tenants_count < MIN_TEN ||
        table->appar[i].flat.second.last_tenants_count > MAX_TEN)
    {
        printf("Incorrect number of previous tanents entered..\n");
        return ERROR_READ_FILE;
    }

    if (!f->_file)
        printf("Enter the \"was there an animal\" attribute (1 if Yes 0 if no): ");
    if (fscanf(f, "%hd", &animal) != 1)
    {
        printf("Invalid attribute entered..\n");
        return ERROR_READ_FILE;
    }
    if (animal < false || animal > true)
    {
        printf("Invalid attribute entered..\n");
        return ERROR_READ_FILE;
    }

    table->appar[i].flat.second.animals = (animal) ? true : false;

    return OK;

}

/*!
 * \brief read_min_max - Reading min and max search boundaries.
 * \param *min, *max - pointer on min and max.
 * \return OK if all is well, otherwise some ERROR_.
 */
func_var read_min_max(int *min, int *max)
{
    printf("Enter the lower limit of the price to search for (1 to 1 000 000): ");
    if (scanf("%d", min) != 1)
    {
        return ERROR_INPUT;
    }
    printf("Enter the upper limit of the price to search for (1 to 1 000 000): ");
    if (scanf("%d", max) != 1)
    {
        return ERROR_INPUT;
    }

    if (*min < MIN_PRICE || *max > MAX_PRICE)
    {
        return ERROR_INPUT;
    }

    if (*min >= *max)
    {
        printf("The lower border is larger than the upper one.\n");
        return ERROR_INPUT;
    }

    return OK;
}
