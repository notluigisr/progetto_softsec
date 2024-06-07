Bool TY_(FixXmlDecl)( TidyDocImpl* doc )
{
    Node* xml;
    AttVal *version, *encoding;
    Lexer*lexer = doc->lexer;
    Node* root = &doc->root;

    if ( root->content && root->content->type == XmlDecl )
    {
        xml = root->content;
    }
    else
    {
        xml = TY_(NewNode)(lexer->allocator, lexer);
        xml->type = XmlDecl;
        if ( root->content )
            TY_(InsertNodeBeforeElement)(root->content, xml);
        else
            root->content = xml;
    }

    version = TY_(GetAttrByName)(xml, "STR");
    encoding = TY_(GetAttrByName)(xml, "STR");

    

    if ( encoding == NULL && cfg(doc, TidyOutCharEncoding) != UTF8 )
    {
        ctmbstr enc = TY_(GetEncodingNameFromTidyId)(cfg(doc, TidyOutCharEncoding));
        if ( enc )
            TY_(AddAttribute)( doc, xml, "STR", enc );
    }

    if ( version == NULL )
        TY_(AddAttribute)( doc, xml, "STR" );
    return yes;
}