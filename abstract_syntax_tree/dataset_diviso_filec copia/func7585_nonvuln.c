static void encode_picture_start(VC2EncContext *s)
{
    avpriv_align_put_bits(&s->pb);
    encode_picture_header(s);
    avpriv_align_put_bits(&s->pb);
    encode_wavelet_transform(s);
}