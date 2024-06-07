    SG_Exception_Dim_MM::SG_Exception_Dim_MM(const char* container_name, const char* field_1, const char* field_2)
    {
        std::string cn_s(container_name);
        std::string field1_s(field_1);
        std::string field2_s(field_2);

        this -> err_msg = "STR"
                + field1_s
                + "STR"
                + field2_s
                + "STR";
    }