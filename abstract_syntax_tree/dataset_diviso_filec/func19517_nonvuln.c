void dwgRSCodec::decode239I(unsigned char *in, unsigned char *out, duint32 blk){
    int k=0;
    unsigned char data[255];
    RScodec rsc(0x96, 8, 8); 
    for (duint32 i=0; i<blk; i++){
        k = i;
        for (int j=0; j<255; j++) {
            data[j] = in[k];
            k +=blk;
        }
        int r = rsc.decode(data);
        if (r<0)
            DRW_DBG("STR");
        k = i*239;
        for (int j=0; j<239; j++) {
            out[k++] = data[j];
        }
    }
}