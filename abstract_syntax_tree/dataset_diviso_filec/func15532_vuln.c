_mibindex_add( const char *dirname, int i )
{
    const int old_mibindex_max = _mibindex_max;

    DEBUGMSGTL(("STR", dirname, i ));
    if ( i == -1 )
        i = _mibindex++;
    if ( i >= _mibindex_max ) {
        
        _mibindex_max = i + 10;
        _mibindexes = realloc(_mibindexes,
                              _mibindex_max * sizeof(_mibindexes[0]));
        netsnmp_assert(_mibindexes);
        memset(_mibindexes + old_mibindex_max, 0,
               (_mibindex_max - old_mibindex_max) * sizeof(_mibindexes[0]));
    }

    _mibindexes[ i ] = strdup( dirname );
    if ( i >= _mibindex )
        _mibindex = i+1;

    DEBUGMSGTL(("STR", i, _mibindex, _mibindex_max ));
    return i;
}