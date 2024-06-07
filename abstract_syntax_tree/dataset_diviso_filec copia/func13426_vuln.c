
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *yyscanner, HEX_LEX_ENVIRONMENT *lex_env)
{
  YYUSE (yyvaluep);
  YYUSE (yyscanner);
  YYUSE (lex_env);
  if (!yymsg)
    yymsg = "STR";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 16: 
#line 94 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1023 "STR" 
        break;

    case 17: 
#line 95 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1029 "STR" 
        break;

    case 18: 
#line 96 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1035 "STR" 
        break;

    case 19: 
#line 97 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1041 "STR" 
        break;

    case 21: 
#line 100 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1047 "STR" 
        break;

    case 22: 
#line 99 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1053 "STR" 
        break;

    case 23: 
#line 98 "STR" 
      { yr_re_node_destroy(((*yyvaluep).re_node)); }
#line 1059 "STR" 
        break;


      default:
        break;
    }