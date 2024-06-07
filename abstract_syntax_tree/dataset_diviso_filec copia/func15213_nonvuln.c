JANET_CORE_FN(cfun_array_slice,
              "STR",
              "STR"
              "STR"
              "STR"
              "STR"
              "STR") {
    JanetView view = janet_getindexed(argv, 0);
    JanetRange range = janet_getslice(argc, argv);
    JanetArray *array = janet_array(range.end - range.start);
    if (array->data)
        memcpy(array->data, view.items + range.start, sizeof(Janet) * (range.end - range.start));
    array->count = range.end - range.start;
    return janet_wrap_array(array);
}