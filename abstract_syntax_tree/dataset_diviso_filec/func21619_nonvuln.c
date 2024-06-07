simplify_key(int key, int *modifiers)
{
    int	    i;
    int	    key0;
    int	    key1;

    if (*modifiers & (MOD_MASK_SHIFT | MOD_MASK_CTRL | MOD_MASK_ALT))
    {
	
	if (key == TAB && (*modifiers & MOD_MASK_SHIFT))
	{
	    *modifiers &= ~MOD_MASK_SHIFT;
	    return K_S_TAB;
	}
	key0 = KEY2TERMCAP0(key);
	key1 = KEY2TERMCAP1(key);
	for (i = 0; modifier_keys_table[i] != NUL; i += MOD_KEYS_ENTRY_SIZE)
	    if (key0 == modifier_keys_table[i + 3]
		    && key1 == modifier_keys_table[i + 4]
		    && (*modifiers & modifier_keys_table[i]))
	    {
		*modifiers &= ~modifier_keys_table[i];
		return TERMCAP2KEY(modifier_keys_table[i + 1],
						   modifier_keys_table[i + 2]);
	    }
    }
    return key;
}