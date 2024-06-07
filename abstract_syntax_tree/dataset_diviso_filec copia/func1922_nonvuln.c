static int avi_sampsize(avi_t *AVI, int j)
{
	int s;
	s = ((AVI->track[j].a_bits+7)/8)*AVI->track[j].a_chans;
	
	if(s<4) s=4; 
	return s;
}