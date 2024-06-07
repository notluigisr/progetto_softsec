OJPEGReadHeaderInfoSecTablesAcTable(TIFF* tif)
{
	static const char module[]="STR";
	OJPEGState* sp=(OJPEGState*)tif->tif_data;
	uint8 m;
	uint8 n;
	uint8 o[16];
	uint32 p;
	uint32 q;
	uint32 ra;
	uint8* rb;
	if (sp->actable_offset[0]==0)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"STR");
		return(0);
	}
	sp->in_buffer_file_pos_log=0;
	for (m=0; m<sp->samples_per_pixel; m++)
	{
		if ((sp->actable_offset[m]!=0) && ((m==0) || (sp->actable_offset[m]!=sp->actable_offset[m-1])))
		{
			for (n=0; n<m-1; n++)
			{
				if (sp->actable_offset[m]==sp->actable_offset[n])
				{
					TIFFErrorExt(tif->tif_clientdata,module,"STR");
					return(0);
				}
			}
			TIFFSeekFile(tif,sp->actable_offset[m],SEEK_SET);  
			p=(uint32)TIFFReadFile(tif,o,16);
			if (p!=16)
				return(0);
			q=0;
			for (n=0; n<16; n++)
				q+=o[n];
			ra=sizeof(uint32)+21+q;
			rb=_TIFFmalloc(ra);
			if (rb==0)
			{
				TIFFErrorExt(tif->tif_clientdata,module,"STR");
				return(0);
			}
			*(uint32*)rb=ra;
			rb[sizeof(uint32)]=255;
			rb[sizeof(uint32)+1]=JPEG_MARKER_DHT;
			rb[sizeof(uint32)+2]=(uint8)((19+q)>>8);
			rb[sizeof(uint32)+3]=((19+q)&255);
			rb[sizeof(uint32)+4]=(16|m);
			for (n=0; n<16; n++)
				rb[sizeof(uint32)+5+n]=o[n];
			p=(uint32)TIFFReadFile(tif,&(rb[sizeof(uint32)+21]),q);
			if (p!=q)
				return(0);
			sp->actable[m]=rb;
			sp->sos_tda[m]=(sp->sos_tda[m]|m);
		}
		else
			sp->sos_tda[m]=(sp->sos_tda[m]|(sp->sos_tda[m-1]&15));
	}
	return(1);
}