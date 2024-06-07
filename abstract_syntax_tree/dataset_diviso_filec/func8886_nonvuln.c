static void dump_data_string(FILE *trace, char *data, u32 dataLength)
{
	u32 i;
	for (i=0; i<dataLength; i++) {
		switch ((unsigned char) data[i]) {
		case '\'':
			gf_fprintf(trace, "STR");
			break;
		case '\"':
			gf_fprintf(trace, "STR");
			break;
		case '&':
			gf_fprintf(trace, "STR");
			break;
		case '>':
			gf_fprintf(trace, "STR");
			break;
		case '<':
			gf_fprintf(trace, "STR");
			break;
		default:
			gf_fprintf(trace, "STR", (u8) data[i]);
			break;
		}
	}
}