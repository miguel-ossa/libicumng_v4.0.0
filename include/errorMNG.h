// Errores de librerias MNG
#ifndef _ERRORMNG_H
#define _ERRORMNG_H

#undef LIBMNG_CODE_LIBRARY
#define LIBMNG_CODE_LIBRARY          001000
#undef LIBICUMNG_CODE_LIBRARY
#define LIBICUMNG_CODE_LIBRARY       002000
#undef LIBSSLMNG_CODE_LIBRARY
#define LIBSSLMNG_CODE_LIBRARY       003000

#ifndef _LIBSSLMNG_ERROR
#define _LIBSSLMNG_ERROR

  #define _LIBSSLMNG_ERROR_001 -LIBSSLMNG_CODE_LIBRARY * 1 // "ERROR: clsCrypto::SetParamVigenere() Alphabet must be between 0 and 254 characters\n"
  #define _LIBSSLMNG_ERROR_002 2 // "ERROR: clsCrypto::SetParamVigenere() Password must have 6 or more characters\n"
  #define _LIBSSLMNG_ERROR_003 3 // "ERROR: clsCrypto::SetParamVigenere() Alphabet contains repeated characters\n"
  #define _LIBSSLMNG_ERROR_004 4 // "ERROR: clsCrypto::SetParamVigenere() Password char not found in alphabet\n"
  #define _LIBSSLMNG_ERROR_005 5 // "ERROR: clsCrypto::GenerateRandomMatrix() len cannot be greater than AES_BLOCK_SIZE\n"
  #define _LIBSSLMNG_ERROR_006 6 // "ERROR: clsCrypto::GetMatrix() len cannot be greater than AES_BLOCK_SIZE\n"
  #define _LIBSSLMNG_ERROR_007 7 // "ERROR: clsCrypto::Encrypt() Algorithm cannot be null\n"
  #define _LIBSSLMNG_ERROR_008 8 // "ERROR: clsCrypto::Encrypt() source parameter cannot be null\n"
  #define _LIBSSLMNG_ERROR_009 9 // "ERROR: clsCrypto::Encrypt() lenTarget not informed\n"
  #define _LIBSSLMNG_ERROR_010 10 // "ERROR: clsCrypto::Encrypt() Algorithm not implemented\n"
  #define _LIBSSLMNG_ERROR_011 11 // "ERROR: clsCrypto::Encrypt() Matrix not initialized properly\n"
  #define _LIBSSLMNG_ERROR_012 12 // "ERROR: clsCrypto::Encrypt() Vigenere password not informed\n"
  #define _LIBSSLMNG_ERROR_013 13 // "ERROR: clsCrypto::Encrypt() size exceeded\n"
  #define _LIBSSLMNG_ERROR_014 14 // "ERROR: clsCrypto::Decrypt() Algorithm cannot be null\n"
  #define _LIBSSLMNG_ERROR_015 15 // "ERROR: clsCrypto::Decrypt() source parameter cannot be null\n")
  #define _LIBSSLMNG_ERROR_016 16 // "ERROR: clsCrypto::Decrypt() lenTarget not informed\n"
  #define _LIBSSLMNG_ERROR_017 17 // "ERROR: clsCrypto::Encrypt() Algorithm not implemented\n"
  #define _LIBSSLMNG_ERROR_018 18 // "ERROR: clsCrypto::Encrypt() Vigenere password not informed\n"
  #define _LIBSSLMNG_ERROR_019 19 // "ERROR: clsCrypto::Encrypt() Matrix not initialized properly\n"
  #define _LIBSSLMNG_ERROR_020 20 // "ERROR: clsCrypto::Encrypt() size exceeded\n"

#endif//_LIBSSLMNG_ERROR


#endif//_ERRORMNG_H
