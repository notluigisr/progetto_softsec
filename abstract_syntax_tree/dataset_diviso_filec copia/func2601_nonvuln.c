static void encode_wavelet_transform(VC2EncContext *s)
{
    encode_transform_params(s);
    avpriv_align_put_bits(&s->pb);
    
}