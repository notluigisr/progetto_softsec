INST_HANDLER (dec) {	
	int d = ((buf[0] >> 4) & 0xf) | ((buf[1] & 0x1) << 4);
	ESIL_A ("STR", d);				
								
	ESIL_A ("STR");			
	ESIL_A ("STR");			
	ESIL_A ("STR");				
	ESIL_A ("STR");				
	ESIL_A ("STR", d);					
}