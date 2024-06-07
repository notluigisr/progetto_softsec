START_TEST(virgl_test_copy_transfer_from_staging_without_iov_fails)
{
  static const unsigned bufsize = 50;
  static const unsigned synchronized = 1;
  struct virgl_context ctx = {0};
  struct virgl_resource src_res = {0};
  struct virgl_resource dst_res = {0};
  struct pipe_box box = {.width = bufsize, .height = 1, .depth = 1};
  int ret;

  ret = testvirgl_init_ctx_cmdbuf(&ctx);
  ck_assert_int_eq(ret, 0);

  ret = testvirgl_create_unbacked_simple_buffer(&src_res, 1, bufsize, VIRGL_BIND_STAGING);
  ck_assert_int_eq(ret, 0);
  virgl_renderer_ctx_attach_resource(ctx.ctx_id, src_res.handle);

  ret = testvirgl_create_backed_simple_buffer(&dst_res, 2, bufsize, VIRGL_BIND_VERTEX_BUFFER);
  ck_assert_int_eq(ret, 0);
  virgl_renderer_ctx_attach_resource(ctx.ctx_id, dst_res.handle);

  box.width = bufsize;
  virgl_encoder_copy_transfer(&ctx, &dst_res, 0, 0, &box, &src_res, 0, synchronized);

  ret = virgl_renderer_submit_cmd(ctx.cbuf->buf, ctx.ctx_id, ctx.cbuf->cdw);
  ck_assert_int_eq(ret, EINVAL);

  virgl_renderer_ctx_detach_resource(ctx.ctx_id, src_res.handle);
  virgl_renderer_ctx_detach_resource(ctx.ctx_id, dst_res.handle);
  virgl_renderer_resource_unref(src_res.handle);
  testvirgl_destroy_backed_res(&dst_res);
  testvirgl_fini_ctx_cmdbuf(&ctx);
}