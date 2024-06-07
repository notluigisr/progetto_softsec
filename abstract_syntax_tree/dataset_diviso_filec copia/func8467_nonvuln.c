START_TEST(virgl_test_transfer_read_3d_bad_box)
{
  struct virgl_renderer_resource_create_args res;
  struct iovec iovs[1];
  int niovs = 1;
  int ret;
  struct virgl_box box;

  testvirgl_init_simple_1d_resource(&res, 1);
  res.target = PIPE_TEXTURE_3D;
  res.depth = 5;

  ret = virgl_renderer_resource_create(&res, NULL, 0);
  ck_assert_int_eq(ret, 0);

  virgl_renderer_ctx_attach_resource(1, res.handle);

  box.x = box.y = box.z = 0;
  box.w = 10;
  box.h = 2;
  box.d = 6;

  ret = virgl_renderer_transfer_read_iov(1, 1, 0, 1, 1, &box, 0, iovs, niovs);
  ck_assert_int_eq(ret, EINVAL);
  virgl_renderer_ctx_detach_resource(1, res.handle);

  virgl_renderer_resource_unref(1);
}