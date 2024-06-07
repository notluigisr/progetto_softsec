yaml_parser_save_simple_key(yaml_parser_t *parser)
{
    

    int required = (!parser->flow_level
            && parser->indent == (ptrdiff_t)parser->mark.column);

    

    assert(parser->simple_key_allowed || !required);    

    

    if (parser->simple_key_allowed)
    {
        yaml_simple_key_t simple_key;
        simple_key.possible = 1;
        simple_key.required = required;
        simple_key.token_number = 
            parser->tokens_parsed + (parser->tokens.tail - parser->tokens.head);
        simple_key.mark = parser->mark;

        if (!yaml_parser_remove_simple_key(parser)) return 0;

        *(parser->simple_keys.top-1) = simple_key;
    }

    return 1;
}