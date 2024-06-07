int af_get_page_raw(AFFILE *af,int64_t pagenum,uint32_t *arg,
		    unsigned char *data,size_t *bytes)
{
    char segname[AF_MAX_NAME_LEN];

    memset(segname,0,sizeof(segname));
    sprintf(segname,AF_PAGE,pagenum);
    int r = af_get_seg(af,segname,arg,data,bytes);
    if(r < 0 && errno == ENOENT)
    {
	
	sprintf(segname,AF_SEG_D,pagenum);
	r = af_get_seg(af,segname,arg,data,bytes);
    }
    
    if(r==0 && bytes && *bytes>0) af->pages_read++; 
    return r;
}