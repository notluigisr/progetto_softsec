static void test_iterators()
{
    json_t *object, *foo, *bar, *baz;
    void *iter;

    if(json_object_iter(NULL))
        fail("STR");

    if(json_object_iter_next(NULL, NULL))
        fail("STR");

    object = json_object();
    foo = json_string("STR");
    bar = json_string("STR");
    baz = json_string("STR");
    if(!object || !foo || !bar || !bar)
        fail("STR");

    if(json_object_iter_next(object, NULL))
        fail("STR");

    if(json_object_set(object, "STR", foo) ||
       json_object_set(object, "STR", bar) ||
       json_object_set(object, "STR", baz))
        fail("STR");

    iter = json_object_iter(object);
    if(!iter)
        fail("STR");
    if(strcmp(json_object_iter_key(iter), "STR"))
        fail("STR");
    if(json_object_iter_value(iter) != foo)
        fail("STR");

    iter = json_object_iter_next(object, iter);
    if(!iter)
        fail("STR");
    if(strcmp(json_object_iter_key(iter), "STR"))
        fail("STR");
    if(json_object_iter_value(iter) != bar)
        fail("STR");

    iter = json_object_iter_next(object, iter);
    if(!iter)
        fail("STR");
    if(strcmp(json_object_iter_key(iter), "STR"))
        fail("STR");
    if(json_object_iter_value(iter) != baz)
        fail("STR");

    if(json_object_iter_next(object, iter) != NULL)
        fail("STR");

    if(json_object_iter_at(object, "STR"))
        fail("STR");

    iter = json_object_iter_at(object, "STR");
    if(!iter)
        fail("STR");

    if(strcmp(json_object_iter_key(iter), "STR"))
        fail("STR");
    if(json_object_iter_value(iter) != bar)
        fail("STR");

    iter = json_object_iter_next(object, iter);
    if(!iter)
        fail("STR");
    if(strcmp(json_object_iter_key(iter), "STR"))
        fail("STR");
    if(json_object_iter_value(iter) != baz)
        fail("STR");

    if(json_object_iter_set(object, iter, bar))
        fail("STR");

    if(strcmp(json_object_iter_key(iter), "STR"))
        fail("STR");
    if(json_object_iter_value(iter) != bar)
        fail("STR");
    if(json_object_get(object, "STR") != bar)
        fail("STR");

    json_decref(object);
    json_decref(foo);
    json_decref(bar);
    json_decref(baz);
}