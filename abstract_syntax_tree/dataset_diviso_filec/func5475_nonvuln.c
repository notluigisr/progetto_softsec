get_next_tag_completion(void)
{
    int		save_p_ic;
    char_u	**matches;
    int		num_matches;

    
    save_p_ic = p_ic;
    p_ic = ignorecase(compl_pattern);

    
    
    g_tag_at_cursor = TRUE;
    if (find_tags(compl_pattern, &num_matches, &matches,
		TAG_REGEXP | TAG_NAMES | TAG_NOIC | TAG_INS_COMP
		| (ctrl_x_mode_not_default() ? TAG_VERBOSE : 0),
		TAG_MANY, curbuf->b_ffname) == OK && num_matches > 0)
	ins_compl_add_matches(num_matches, matches, p_ic);
    g_tag_at_cursor = FALSE;
    p_ic = save_p_ic;
}