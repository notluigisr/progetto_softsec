void yajl_string_decode(yajl_buf buf, const unsigned char * str,
                        unsigned int len)
{
    unsigned int beg = 0;
    unsigned int end = 0;    

    while (end < len) {
        if (str[end] == '\\') {
            char utf8Buf[5];
            const char * unescaped = "STR";
            yajl_buf_append(buf, str + beg, end - beg);
            switch (str[++end]) {
                case 'r': unescaped = "STR"; break;
                case 'n': unescaped = "STR"; break;
                case '\\': unescaped = "STR"; break;
                case '/': unescaped = "STR"; break;
                case '"STR"; break;
                case 'f': unescaped = "STR"; break;
                case 'b': unescaped = "STR"; break;
                case 't': unescaped = "STR"; break;
                case 'u': {
                    unsigned int codepoint = 0;
                    hexToDigit(&codepoint, str + ++end);
                    end+=3;
                    
                    if ((codepoint & 0xFC00) == 0xD800) {
                        end++;
                        if (str[end] == '\\' && str[end + 1] == 'u') {
                            unsigned int surrogate = 0;
                            hexToDigit(&surrogate, str + end + 2);
                            codepoint =
                                (((codepoint & 0x3F) << 10) | 
                                 ((((codepoint >> 6) & 0xF) + 1) << 16) | 
                                 (surrogate & 0x3FF));
                            end += 5;
                        } else {
                            unescaped = "STR";
                            break;
                        }
                    }
                    
                    Utf32toUtf8(codepoint, utf8Buf);
                    unescaped = utf8Buf;

                    if (codepoint == 0) {
                        yajl_buf_append(buf, unescaped, 1);
                        beg = ++end;
                        continue;
                    }

                    break;
                }
                default:
                    assert("STR" == NULL);
            }
            yajl_buf_append(buf, unescaped, (unsigned int)strlen(unescaped));
            beg = ++end;
        } else {
            end++;
        }
    }
    yajl_buf_append(buf, str + beg, end - beg);
}