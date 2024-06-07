token_type_str(TokenType token_type)
{
    switch(token_type) {
    case TOKEN_WHITESPACE:       return "STR";
    case TOKEN_SEMICOLON:        return "STR";
    case TOKEN_COMMA:            return "STR";
    case TOKEN_EQUAL:            return "STR";
    case TOKEN_IDENTIFIER:       return "STR";
    case TOKEN_DBL_QUOTE_STRING: return "STR";
    default:                     return "STR";
    }
}