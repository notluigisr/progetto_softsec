static void encode_transform_params(VC2EncContext *s)
{
    put_vc2_ue_uint(&s->pb, s->wavelet_idx);
    put_vc2_ue_uint(&s->pb, s->wavelet_depth);

    encode_slice_params(s);
    encode_quant_matrix(s);
}