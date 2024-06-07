int LibRaw::subtract_black()
{
	CHECK_ORDER_LOW(LIBRAW_PROGRESS_RAW2_IMAGE);

	try {
    if(!is_phaseone_compressed() && (C.cblack[0] || C.cblack[1] || C.cblack[2] || C.cblack[3]))
        {

            int cblk[4],i;
            for(i=0;i<4;i++)
                cblk[i] = C.cblack[i];

            int size = S.iheight * S.iwidth;





            for(i=0; i< size*4; i++)
              {
                int val = imgdata.image[0][i];
                val -= cblk[i & 3];
                imgdata.image[0][i] = CLIP(val);
                if(C.data_maximum < val) C.data_maximum = val;
              }
#undef MIN
#undef MAX
#undef LIM
#undef CLIP
            C.maximum -= C.black;
            ZERO(C.cblack);
            C.black = 0;
#undef BAYERC
        }
    else
        {
          
          
          int idx;
          ushort *p = (ushort*)imgdata.image;
          C.data_maximum = 0;
          for(idx=0;idx<S.iheight*S.iwidth*4;idx++)
            if(C.data_maximum < p[idx]) C.data_maximum = p[idx];
        }
		return 0;
	}
	catch ( LibRaw_exceptions err) {
		EXCEPTION_HANDLER(err);
	}

}