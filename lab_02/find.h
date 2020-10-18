#ifndef FIND_H
#define FIND_H

#include "my_main.h"
#include "read.h"
#include "io.h"
#include "load.h"
#include "check.h"

func_var add_flat_end(table_r *const table);
void delet_pos(table_r *const table, func_var k, func_var del_id);
func_var delet_record_room(table_r *const table);
func_var find_this_app(table_r *const table, int min, int max);
func_var find_app_be_con(table_r *const table);

func_var find_to_del_room(table_r *const table, func_var room);

#endif // FIND_H
