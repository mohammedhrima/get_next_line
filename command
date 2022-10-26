-fsanitize  -g3 (to see more details)
gcc main.c get_next_line.c get_next_line_utils.c ./Leak_Hunter/leak_hunter.c ./Leak_Hunter/list_tools.c
leaks a.out (to see if there is any leak)