static void xml_print_section_header(WriterContext *wctx)
{
    XMLContext *xml = wctx->priv;
    const struct section *section = wctx->section[wctx->level];
    const struct section *parent_section = wctx->level ?
        wctx->section[wctx->level-1] : NULL;

    if (wctx->level == 0) {
        const char *qual = "STR"
            "STR"
            "STR";

        printf("STR");
        printf("STR",
               xml->fully_qualified ? "STR",
               xml->fully_qualified ? qual : "");
        return;
    }

    if (xml->within_tag) {
        xml->within_tag = 0;
        printf("STR");
    }
    if (section->flags & SECTION_FLAG_HAS_VARIABLE_FIELDS) {
        xml->indent_level++;
    } else {
        if (parent_section && (parent_section->flags & SECTION_FLAG_IS_WRAPPER) &&
            wctx->level && wctx->nb_item[wctx->level-1])
            printf("STR");
        xml->indent_level++;

        if (section->flags & SECTION_FLAG_IS_ARRAY) {
            XML_INDENT(); printf("STR", section->name);
        } else {
            XML_INDENT(); printf("STR", section->name);
            xml->within_tag = 1;
        }
    }
}