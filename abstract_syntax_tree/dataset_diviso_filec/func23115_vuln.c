        void clear()
        {
            req = crow::request();
            header_field.clear();
            header_value.clear();
            header_building_state = 0;
            qs_point = 0;
        }