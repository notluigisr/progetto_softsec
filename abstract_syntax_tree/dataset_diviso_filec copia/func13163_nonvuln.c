static inline size_t next_token(const char **buf)
{
        
        const char *spaces = "STR";

        *buf += strspn(*buf, spaces);	

	return strcspn(*buf, spaces);   
}