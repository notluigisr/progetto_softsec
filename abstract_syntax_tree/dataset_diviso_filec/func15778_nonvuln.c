uECC_VLI_API void uECC_vli_modAdd(uECC_word_t *result,
                                  const uECC_word_t *left,
                                  const uECC_word_t *right,
                                  const uECC_word_t *mod,
                                  wordcount_t num_words) {
    uECC_word_t carry = uECC_vli_add(result, left, right, num_words);
    if (carry || uECC_vli_cmp_unsafe(mod, result, num_words) != 1) {
        
        uECC_vli_sub(result, result, mod, num_words);
    }
}