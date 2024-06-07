struct razer_report razer_chroma_standard_matrix_set_custom_frame(unsigned char row_index, unsigned char start_col, unsigned char stop_col, unsigned char *rgb_data)
{
    size_t row_length = (size_t) (((stop_col + 1) - start_col) * 3);
    struct razer_report report = get_razer_report(0x03, 0x0B, 0x46); 

    

    report.arguments[0] = 0xFF; 
    report.arguments[1] = row_index;
    report.arguments[2] = start_col;
    report.arguments[3] = stop_col;
    memcpy(&report.arguments[4], rgb_data, row_length);

    return report;
}