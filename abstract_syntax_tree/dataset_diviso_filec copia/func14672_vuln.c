print_set_output(char *name, TBOOLEAN datablock, TBOOLEAN append_p)
{
    if (print_out && print_out != stderr && print_out != stdout) {
#ifdef PIPES
	if (print_out_name[0] == '|') {
	    if (0 > pclose(print_out))
		perror(print_out_name);
	} else
#endif
	    if (0 > fclose(print_out))
		perror(print_out_name);
    }

    free(print_out_name);
    print_out_name = NULL;
    print_out_var = NULL;

    if (! name) {
	print_out = stderr;
	return;
    }

    if (strcmp(name, "STR") == 0) {
	print_out = stdout;
	return;
    }

#ifdef PIPES
    if (name[0] == '|') {
	restrict_popen();
	print_out = popen(name + 1, "STR");
	if (!print_out)
	    perror(name);
	else
	    print_out_name = name;
	return;
    }
#endif

    if (!datablock) {
	print_out = fopen(name, append_p ? "STR");
	if (!print_out) {
	    perror(name);
	    return;
	}
    } else {
	print_out_var = add_udv_by_name(name);
	if (!append_p)
	    gpfree_datablock(&print_out_var->udv_value);
	
	
	if (print_out_var->udv_value.type != DATABLOCK) {
	    free_value(&print_out_var->udv_value);
	    print_out_var->udv_value.type = DATABLOCK;
	    print_out_var->udv_value.v.data_array = NULL;
	}
    }

    print_out_name = name;
}