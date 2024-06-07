connection_get_operation(void)
{
    struct Slapi_op_stack *stack_obj = (struct Slapi_op_stack *)PR_StackPop(op_stack);
    if (!stack_obj) {
        stack_obj = (struct Slapi_op_stack *)slapi_ch_calloc(1, sizeof(struct Slapi_op_stack));
        stack_obj->op = operation_new(plugin_build_operation_action_bitmap(0,
                                                                           plugin_get_server_plg()));
    } else {
        PR_AtomicDecrement(&op_stack_size);
        if (!stack_obj->op) {
            stack_obj->op = operation_new(plugin_build_operation_action_bitmap(0,
                                                                               plugin_get_server_plg()));
        } else {
            operation_init(stack_obj->op,
                           plugin_build_operation_action_bitmap(0, plugin_get_server_plg()));
        }
    }
    return stack_obj;
}