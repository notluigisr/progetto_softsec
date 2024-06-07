TEST(DecodeAPI, OptionalParams) {
  vpx_codec_ctx_t dec;

#if CONFIG_ERROR_CONCEALMENT
  EXPECT_EQ(VPX_CODEC_OK, vpx_codec_dec_init(&dec, &vpx_codec_vp8_dx_algo, NULL,
                                             VPX_CODEC_USE_ERROR_CONCEALMENT));
#else
  EXPECT_EQ(VPX_CODEC_INCAPABLE,
            vpx_codec_dec_init(&dec, &vpx_codec_vp8_dx_algo, NULL,
                               VPX_CODEC_USE_ERROR_CONCEALMENT));
#endif  
}