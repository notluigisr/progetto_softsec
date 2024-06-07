checkforcmd_noparen(
    char_u	**pp,		
    char	*cmd,		
    int		len)		
{
    return checkforcmd_opt(pp, cmd, len, TRUE);
}