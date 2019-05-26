/*--------------------------------------------------------------------*\
 | libmngErrno.h                                                      |
 | =============                                                      |
 |                                                                    |
 | Include con la definicion de errores para las shared libraries.    |
 |                                                                    |
 | Arquitectura CAM, Mango, febrero de 2017                           |
 |                                                                    |
\*--------------------------------------------------------------------*/

#ifndef _LIBMNG_ERRNO_H
#define _LIBMNG_ERRNO_H

#include <stdio.h>
#include <dlfcn.h>
#ifdef _AIX
#include <cobtypes.h>
#include "cobsignal.h"
#include "cobmain.h"
#include "cobscreen.h"
#endif // _AIX

long libmng_errcod;
char libmng_errstr[1024];

/*-------------------------------------*\
 |                                     |
 | Definicion de la clase clsLibErrMNG |
 |                                     |
\*-------------------------------------*/
class clsLibErrMNG
{
public:
  clsLibErrMNG();

  /* use virtual otherwise linker will try to perform static linkage */
  virtual void mngPerror(const char *strCustomMessage);

private:

};

typedef clsLibErrMNG *handleLiberr;

#ifdef __liberrmng_so_
//----------------------------------------------------------------------
// Wrapper COBOL
extern "C" {
  handleLiberr mngLiberrNew(){return(new clsLibErrMNG());}
  void         mngPerror(handleLiberr *hLiberr, const char *strCustomMessage){ return ((*hLiberr)->mngPerror(strCustomMessage));}
} // of extern "C"
#endif

clsLibErrMNG* myclsLibErrMNG;
void (*destroy)(clsLibErrMNG*);

/*--------------------------------------------------------------------*\
 | Carga_LibErrMNG                                                    |
 | ===============                                                    |
 |                                                                    |
 | Carga dinamica de la libreria de gestion de errores.               |
 |                                                                    |
 | Parametros de entrada: ninguno                                     |
 |                                                                    |
 | Parametros de salida: ninguno                                      |
 |                                                                    |
\*--------------------------------------------------------------------*/
void Carga_LibErrMNG()
{
  void* handle = dlopen("liberrmng.so", RTLD_LAZY);
#ifdef _AIX
  if (handle == NULL) {
    cobprintf((const unsigned char*)"****EXCEPTION 'liberrmng.so' NOT FOUND!");
    exit(-1);
  }
#endif // _AIX
  clsLibErrMNG* (*create)();
  create = (clsLibErrMNG* (*)())dlsym(handle, "create_object");
  destroy = (void (*)(clsLibErrMNG*))dlsym(handle, "destroy_object");
  myclsLibErrMNG = (clsLibErrMNG*)create();
}


#define LIBMNG_LIBID_MNG               0
#define LIBMNG_LIBID_ICU               1
#define LIBMNG_LIBID_SSL               2
#define LIBMNG_LIBID_URL               3
#define LIBMNG_LIBID_SSH               4
#define LIBMNG_LIBID_STL               5

#define LIBMNG_OFFRANGE                100000

#define MAKE_LIBMNG_ERRCOD(LIBID, NUMBER) (long)(-1 * ((LIBID * LIBMNG_OFFRANGE) + NUMBER))
#define MAKE_LIBMNG_ERRSTR(SERROR) snprintf(libmng_errstr, 1024, "%s[%d]: %s() %s", (int)__LINE__, __FILE__, __func__, SERROR)

#ifdef __libmng_so_
extern "C" {
#endif
       // mngGetLastErrorCode ...
       // mngGetLastErrorString ...
#ifdef __libmng_so_
}
#endif

/*-------------------------------------------------------------*\
 |                                                             |
 | Definicion de constantes de error para "libicumng.so".      |
 |                                                             |
 | Errores codificados de -100001 a -199999                    |
 |                                                             |
\*-------------------------------------------------------------*/

#define _LIBICUMNG_ERRCOD_001 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  1) /* "ERROR: clsTransliterate::Transliterate() Parameter cannot be null\n" */
#define _LIBICUMNG_ERRCOD_002 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  2) /* "ERROR: clsTransliterate::Transliterate() lenTarget not informed\n" */
#define _LIBICUMNG_ERRCOD_003 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  3) /* "ERROR: clsTransliterate::Transliterate() Parameter cannot be null\n" */
#define _LIBICUMNG_ERRCOD_004 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  4) /* "ERROR: clsTransliterate::Transliterate() Parameter cannot be null\n" */
#define _LIBICUMNG_ERRCOD_005 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  5) /* "ERROR: clsTransliterate::Transliterate() Invalid argument\n" */
#define _LIBICUMNG_ERRCOD_006 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  6) /* "ERROR: clsTransliterate::transliterate() Size exceeded\n" */
#define _LIBICUMNG_ERRCOD_007 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  7) /* "ERROR: clsNormalize::Normalize() rbtUnaccent cannot be null\n" */
#define _LIBICUMNG_ERRCOD_008 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  8) /* "ERROR: clsNormalize::Normalize() Source parameter cannot be null\n" */
#define _LIBICUMNG_ERRCOD_009 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  9) /* "ERROR: clsNormalize::Normalize() lenTarget not informed\n" */
#define _LIBICUMNG_ERRCOD_010 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  10) /* "ERROR: clsNormalize::Normalize() Parameter cannot be null\n" */
#define _LIBICUMNG_ERRCOD_011 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  11) /* "ERROR: clsNormalize::Normalize() Parameter cannot be null\n" */
#define _LIBICUMNG_ERRCOD_012 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  12) /* "ERROR: clsNormalize::Normalize() Invalid argument\n" */
#define _LIBICUMNG_ERRCOD_013 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  13) /* "ERROR: clsNormalize::normalize Size exceeded\n" */
#define _LIBICUMNG_ERRCOD_014 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  14) /* "ERROR: clsConvert::Convert() This object cannot be null\n" */
#define _LIBICUMNG_ERRCOD_015 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  15) /* "ERROR: clsConvert::Convert() Parameter 'sSourceCodepage' cannot be null\n" */
#define _LIBICUMNG_ERRCOD_016 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  16) /* "ERROR: clsConvert::Convert() Parameter 'sSource' cannot be null\n" */
#define _LIBICUMNG_ERRCOD_017 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  17) /* "ERROR: clsConvert::Convert() Parameter 'sTargetCodepage' cannot be null\n" */
#define _LIBICUMNG_ERRCOD_018 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  18) /* "ERROR: clsConvert::Convert() Parameter 'lenTarget' cannot be zero\n" */
#define _LIBICUMNG_ERRCOD_019 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  19) /* "ERROR: clsConvert::Convert() Error in ucnv_convert\n" */
#define _LIBICUMNG_ERRCOD_020 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_ICU,  20) /* "ERROR: clsConvert::GetAvailableIDs() End of available IDs\n" */

#define _LIBICUMNG_ERRSTR_001 MAKE_LIBMNG_ERRSTR("Parameter cannot be null")
#define _LIBICUMNG_ERRSTR_002 MAKE_LIBMNG_ERRSTR("lenTarget not informed")
#define _LIBICUMNG_ERRSTR_003 MAKE_LIBMNG_ERRSTR("Parameter cannot be null")
#define _LIBICUMNG_ERRSTR_004 MAKE_LIBMNG_ERRSTR("Parameter cannot be null")
#define _LIBICUMNG_ERRSTR_005 MAKE_LIBMNG_ERRSTR("Invalid argument")
#define _LIBICUMNG_ERRSTR_006 MAKE_LIBMNG_ERRSTR("Size exceeded")
#define _LIBICUMNG_ERRSTR_007 MAKE_LIBMNG_ERRSTR("rbtUnaccent cannot be null")
#define _LIBICUMNG_ERRSTR_008 MAKE_LIBMNG_ERRSTR("Source parameter cannot be null")
#define _LIBICUMNG_ERRSTR_009 MAKE_LIBMNG_ERRSTR("lenTarget not informed")
#define _LIBICUMNG_ERRSTR_010 MAKE_LIBMNG_ERRSTR("Parameter cannot be null")
#define _LIBICUMNG_ERRSTR_011 MAKE_LIBMNG_ERRSTR("Parameter cannot be null")
#define _LIBICUMNG_ERRSTR_012 MAKE_LIBMNG_ERRSTR("Invalid argument")
#define _LIBICUMNG_ERRSTR_013 MAKE_LIBMNG_ERRSTR("Size exceeded")
#define _LIBICUMNG_ERRSTR_014 MAKE_LIBMNG_ERRSTR("This object cannot be null")
#define _LIBICUMNG_ERRSTR_015 MAKE_LIBMNG_ERRSTR("Parameter 'sSourceCodepage' cannot be null")
#define _LIBICUMNG_ERRSTR_016 MAKE_LIBMNG_ERRSTR("Parameter 'sSource' cannot be null")
#define _LIBICUMNG_ERRSTR_017 MAKE_LIBMNG_ERRSTR("Parameter 'sTargetCodepage' cannot be null")
#define _LIBICUMNG_ERRSTR_018 MAKE_LIBMNG_ERRSTR("Parameter 'lenTarget' cannot be zero")
#define _LIBICUMNG_ERRSTR_019 MAKE_LIBMNG_ERRSTR("Error in ucnv_convert")
#define _LIBICUMNG_ERRSTR_020 MAKE_LIBMNG_ERRSTR("End of available IDs")


/*-------------------------------------------------------------*\
 |                                                             |
 | Definicion de constantes de error para "libsslmng.so".      |
 |                                                             |
 | Errores codificados de -200001 a -299999                    |
 |                                                             |
\*-------------------------------------------------------------*/

#define _LIBSSLMNG_ERRCOD_001 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL,  1) /* "ERROR: clsCrypto::SetParamVigenere() Alphabet must be between 0 and 254 characters\n" */
#define _LIBSSLMNG_ERRCOD_002 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL,  2) /* "ERROR: clsCrypto::SetParamVigenere() Password must have 6 or more characters\n"       */
#define _LIBSSLMNG_ERRCOD_003 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL,  3) /* "ERROR: clsCrypto::SetParamVigenere() Alphabet contains repeated characters\n"         */
#define _LIBSSLMNG_ERRCOD_004 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL,  4) /* "ERROR: clsCrypto::SetParamVigenere() Password char not found in alphabet\n"           */
#define _LIBSSLMNG_ERRCOD_005 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL,  5) /* "ERROR: clsCrypto::GenerateRandomMatrix() len cannot be greater than AES_BLOCK_SIZE\n" */
#define _LIBSSLMNG_ERRCOD_006 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL,  6) /* "ERROR: clsCrypto::GetMatrix() len cannot be greater than AES_BLOCK_SIZE\n"            */
#define _LIBSSLMNG_ERRCOD_007 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL,  7) /* "ERROR: clsCrypto::Encrypt() Algorithm cannot be null\n"                               */
#define _LIBSSLMNG_ERRCOD_008 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL,  8) /* "ERROR: clsCrypto::Encrypt() source parameter cannot be null\n"                        */
#define _LIBSSLMNG_ERRCOD_009 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL,  9) /* "ERROR: clsCrypto::Encrypt() lenTarget not informed\n"                                 */
#define _LIBSSLMNG_ERRCOD_010 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 10) /* "ERROR: clsCrypto::Encrypt() Algorithm not implemented\n"                              */
#define _LIBSSLMNG_ERRCOD_011 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 11) /* "ERROR: clsCrypto::Encrypt() Matrix not initialized properly\n"                        */
#define _LIBSSLMNG_ERRCOD_012 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 12) /* "ERROR: clsCrypto::Encrypt() Vigenere password not informed\n"                         */
#define _LIBSSLMNG_ERRCOD_013 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 13) /* "ERROR: clsCrypto::Encrypt() size exceeded\n"                                          */
#define _LIBSSLMNG_ERRCOD_014 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 14) /* "ERROR: clsCrypto::Decrypt() Algorithm cannot be null\n"                               */
#define _LIBSSLMNG_ERRCOD_015 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 15) /* "ERROR: clsCrypto::Decrypt() source parameter cannot be null\n")                       */
#define _LIBSSLMNG_ERRCOD_016 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 16) /* "ERROR: clsCrypto::Decrypt() lenTarget not informed\n"                                 */
#define _LIBSSLMNG_ERRCOD_017 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 17) /* "ERROR: clsCrypto::Encrypt() Algorithm not implemented\n"                              */
#define _LIBSSLMNG_ERRCOD_018 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 18) /* "ERROR: clsCrypto::Encrypt() Vigenere password not informed\n"                         */
#define _LIBSSLMNG_ERRCOD_019 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 19) /* "ERROR: clsCrypto::Encrypt() Matrix not initialized properly\n"                        */
#define _LIBSSLMNG_ERRCOD_020 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 20) /* "ERROR: clsCrypto::Encrypt() size exceeded\n"                                          */
#define _LIBSSLMNG_ERRCOD_021 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 21) /* "ERROR: Couldn't initialize AES cipher\n"                                              */
#define _LIBSSLMNG_ERRCOD_022 MAKE_LIBMNG_ERRCOD(LIBMNG_LIBID_SSL, 22) /* "ERROR: lenSource or lenTarget different than lenMatrix\n"                             */

#define _LIBSSLMNG_ERRSTR_001 MAKE_LIBMNG_ERRSTR("Alphabet must be between 0 and 254 characters")
#define _LIBSSLMNG_ERRSTR_002 MAKE_LIBMNG_ERRSTR("Password must have 6 or more characters")
#define _LIBSSLMNG_ERRSTR_003 MAKE_LIBMNG_ERRSTR("Alphabet contains repeated characters")
#define _LIBSSLMNG_ERRSTR_004 MAKE_LIBMNG_ERRSTR("Password char not found in alphabet")
#define _LIBSSLMNG_ERRSTR_005 MAKE_LIBMNG_ERRSTR("len cannot be greater than AES_BLOCK_SIZE")
#define _LIBSSLMNG_ERRSTR_006 MAKE_LIBMNG_ERRSTR("len cannot be greater than AES_BLOCK_SIZE")
#define _LIBSSLMNG_ERRSTR_007 MAKE_LIBMNG_ERRSTR("Algorithm cannot be null")
#define _LIBSSLMNG_ERRSTR_008 MAKE_LIBMNG_ERRSTR("Source parameter cannot be null")
#define _LIBSSLMNG_ERRSTR_009 MAKE_LIBMNG_ERRSTR("lenTarget not informed")
#define _LIBSSLMNG_ERRSTR_010 MAKE_LIBMNG_ERRSTR("Algorithm not implemented")
#define _LIBSSLMNG_ERRSTR_011 MAKE_LIBMNG_ERRSTR("Matrix not initialized properly")
#define _LIBSSLMNG_ERRSTR_012 MAKE_LIBMNG_ERRSTR("Vigenere password not informed")
#define _LIBSSLMNG_ERRSTR_013 MAKE_LIBMNG_ERRSTR("Size exceeded")
#define _LIBSSLMNG_ERRSTR_014 MAKE_LIBMNG_ERRSTR("Algorithm cannot be null")
#define _LIBSSLMNG_ERRSTR_015 MAKE_LIBMNG_ERRSTR("Source parameter cannot be null")
#define _LIBSSLMNG_ERRSTR_016 MAKE_LIBMNG_ERRSTR("lenTarget not informed")
#define _LIBSSLMNG_ERRSTR_017 MAKE_LIBMNG_ERRSTR("Algorithm not implemented")
#define _LIBSSLMNG_ERRSTR_018 MAKE_LIBMNG_ERRSTR("Vigenere password not informed")
#define _LIBSSLMNG_ERRSTR_019 MAKE_LIBMNG_ERRSTR("Matrix not initialized properly")
#define _LIBSSLMNG_ERRSTR_020 MAKE_LIBMNG_ERRSTR("Size exceeded")
#define _LIBSSLMNG_ERRSTR_021 MAKE_LIBMNG_ERRSTR("Couldn't initialize AES cipher")
#define _LIBSSLMNG_ERRSTR_022 MAKE_LIBMNG_ERRSTR("lenSource or lenTarget different than lenMatrix")


#endif // LIBMNG_ERRNO_H
