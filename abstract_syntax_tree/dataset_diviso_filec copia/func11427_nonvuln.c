static int strncpy_with_color_codes(char *s1, char *s2, int n) {
	int i = 0, j = 0;
	int count = 0;
	while (s2[j] && count < n) {
		
		while (s2[j] == 0x1b) {
			
			while (s2[j] && s2[j] != 'm') {
				s1[i++] = s2[j++];
			}
			
			if (s2[j]) {
				s1[i++] = s2[j++];
			}
		}
		if (s2[j]) {
			s1[i++] = s2[j++];
			count++;
		}
	}
	return i;
}