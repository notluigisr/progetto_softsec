static bool set_reg_profile(RAnal *anal) {
	const char *p =
		"STR"
		"STR" 
		"STR" 
		"STR"
		"STR"
		"STR"
		"STR"
		"STR" 
		"STR" 
		"STR" 
		"STR" 
		
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"
		"STR"

		
		"STR"
		"STR"
		
		;
	return r_reg_set_profile_string (anal->reg, p);
}