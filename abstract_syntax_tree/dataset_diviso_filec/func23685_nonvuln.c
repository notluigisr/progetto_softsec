terminate_number_str(char *str, uint8_t max_digits)
{
    uint8_t digits_found = 0;
    while (isdigit(*str) && digits_found <= max_digits) {
        str++;
        digits_found++;
    }

    *str = 0;
    return str;
}