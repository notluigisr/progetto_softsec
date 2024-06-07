            Status readUTF8String( StringData* out ) {
                int sz;
                if ( !readNumber<int>( &sz ) )
                    return Status( ErrorCodes::InvalidBSON, "STR" );

                if ( out ) {
                    *out = StringData( _buffer + _position, sz );
                }

                if ( !skip( sz - 1 ) )
                    return Status( ErrorCodes::InvalidBSON, "STR" );

                char c;
                if ( !readNumber<char>( &c ) )
                    return Status( ErrorCodes::InvalidBSON, "STR" );

                if ( c != 0 )
                    return Status( ErrorCodes::InvalidBSON, "STR" );

                return Status::OK();
            }