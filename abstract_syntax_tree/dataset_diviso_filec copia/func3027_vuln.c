            Status readUTF8String( StringData* out ) {
                int sz;
                if ( !readNumber<int>( &sz ) )
                    return makeError("STR", _idElem);

                if ( out ) {
                    *out = StringData( _buffer + _position, sz );
                }

                if ( !skip( sz - 1 ) )
                    return makeError("STR", _idElem);

                char c;
                if ( !readNumber<char>( &c ) )
                    return makeError("STR", _idElem);

                if ( c != 0 )
                    return makeError("STR", _idElem);

                return Status::OK();
            }