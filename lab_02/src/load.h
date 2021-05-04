#ifndef LOAD_H
#define LOAD_H

#include "my_main.h"
#include "read.h"
#include "check.h"
#include "io.h"

func_var load_in_file(table_r *table, FILE *f, func_var s, func_var e);
func_var parsing_from_file(table_r *table);

#endif // LOAD_H
