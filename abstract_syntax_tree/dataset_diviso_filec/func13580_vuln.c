slapi_pblock_clone(Slapi_PBlock *pb)
{
    
    Slapi_PBlock *new_pb = slapi_pblock_new();
    new_pb->pb_backend = pb->pb_backend;
    new_pb->pb_conn = pb->pb_conn;
    new_pb->pb_op = pb->pb_op;
    new_pb->pb_plugin = pb->pb_plugin;
    
    if (pb->pb_dse != NULL) {
        _pblock_assert_pb_dse(new_pb);
        *(new_pb->pb_dse) = *(pb->pb_dse);
    }
    if (pb->pb_task != NULL) {
        _pblock_assert_pb_task(new_pb);
        *(new_pb->pb_task) = *(pb->pb_task);
    }
    if (pb->pb_mr != NULL) {
        _pblock_assert_pb_mr(new_pb);
        *(new_pb->pb_mr) = *(pb->pb_mr);
    }
    if (pb->pb_misc != NULL) {
        _pblock_assert_pb_misc(new_pb);
        *(new_pb->pb_misc) = *(pb->pb_misc);
    }
    if (pb->pb_intop != NULL) {
        _pblock_assert_pb_intop(new_pb);
        *(new_pb->pb_intop) = *(pb->pb_intop);
        
        new_pb->pb_intop->pwdpolicy = NULL;
    }
    if (pb->pb_intplugin != NULL) {
        _pblock_assert_pb_intplugin(new_pb);
        *(new_pb->pb_intplugin) = *(pb->pb_intplugin);
    }
    if (pb->pb_deprecated != NULL) {
        _pblock_assert_pb_deprecated(new_pb);
        *(new_pb->pb_deprecated) = *(pb->pb_deprecated);
    }
#ifdef PBLOCK_ANALYTICS
    new_pb->analytics = NULL;
    pblock_analytics_init(new_pb);
#endif
    return new_pb;
}