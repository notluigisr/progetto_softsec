static void AddStringToLexer( Lexer *lexer, ctmbstr str )
{
    uint c;

    
    while( 0 != (c = (unsigned char) *str++ ))
        TY_(AddCharToLexer)( lexer, c );
}