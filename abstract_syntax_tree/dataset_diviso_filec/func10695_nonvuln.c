static void test_double_free_in_vrend_renderer_blit_int_trigger_invalid_formats()
{
   struct virgl_renderer_resource_create_args args;
   args.handle = 1;
   args.target = 0;
   args.format = 262144;
   args.bind = 131072;
   args.width = 1;
   args.height = 1;
   args.depth = 1;
   args.array_size = 0;
   args.last_level = 0;
   args.nr_samples = 0;
   args.flags = 0;

   virgl_renderer_resource_create(&args, NULL, 0);
   virgl_renderer_ctx_attach_resource(ctx_id, args.handle);

   args.handle = 6;
   args.target = 4;
   args.format = 1;
   args.bind = 2;
   args.width = 2;
   args.height = 0;
   args.depth = 1;
   args.array_size = 6;
   args.last_level = 2;
   args.nr_samples = 0;
   args.flags = 0;

   virgl_renderer_resource_create(&args, NULL, 0);
   virgl_renderer_ctx_attach_resource(ctx_id, args.handle);

   args.handle = 1;
   args.target = 7;
   args.format = 237;
   args.bind = 1;
   args.width = 6;
   args.height = 0;
   args.depth = 1;
   args.array_size = 0;
   args.last_level = 0;
   args.nr_samples = 6;
   args.flags = 0;

   virgl_renderer_resource_create(&args, NULL, 0);
   virgl_renderer_ctx_attach_resource(ctx_id, args.handle);

   uint32_t cmd[VIRGL_CMD_BLIT_SIZE + 1];

   int i = 0;
   cmd[i++] = VIRGL_CMD_BLIT_SIZE << 16 | 0 << 8 | VIRGL_CCMD_BLIT;
   cmd[i++] = 17113104; 
   cmd[i++] = 1; 
   cmd[i++] = 36; 
   cmd[i++] = 6; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 
   cmd[i++] = 6; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 
   cmd[i++] = 1; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 
   cmd[i++] = 268435456; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 
   cmd[i++] = 0; 

   virgl_renderer_submit_cmd((void *) cmd, ctx_id, VIRGL_CMD_BLIT_SIZE + 1);
}