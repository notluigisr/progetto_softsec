tsize_t t2p_write_pdf_catalog(T2P* t2p, TIFF* output)
{
	tsize_t written = 0;
	char buffer[32];
	int buflen = 0;

	written += t2pWriteFile(output, 
		(tdata_t)"STR", 
		27);
	buflen = snprintf(buffer, sizeof(buffer), "STR", (unsigned long)t2p->pdf_pages);
	check_snprintf_ret(t2p, buflen, buffer);
	written += t2pWriteFile(output, (tdata_t) buffer,
				TIFFmin((size_t)buflen, sizeof(buffer) - 1));
	written += t2pWriteFile(output, (tdata_t) "STR", 6);
	if(t2p->pdf_fitwindow){
		written += t2pWriteFile(output, 
			(tdata_t) "STR", 
			39);
	}
	written += t2pWriteFile(output, (tdata_t)"STR", 3);

	return(written);
}