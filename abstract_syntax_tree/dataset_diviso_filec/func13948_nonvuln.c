png_text_compress_init(compression_state *comp, png_const_bytep input,
   png_alloc_size_t input_len)
{
   comp->input = input;
   comp->input_len = input_len;
   comp->output_len = 0;
}