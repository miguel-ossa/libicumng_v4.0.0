/*
#include "unicode/uclean.h"
#include "unicode/translit.h"
#include "unicode/unistr.h"
#include "unicode/calendar.h"
#include "unicode/datefmt.h"
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include "unicode/uclean.h"
#include "unicode/translit.h"
#include "unicode/unistr.h"
#include "unicode/ucnv.h"
#include "unicode/ubrk.h"
//#include "unicode/ustdio.h"
#include "util.h"
#include "unaccent.h"
#include "unicode/calendar.h"
#include "unicode/datefmt.h"
#include "../../include/libmngErrno.h" // POR QUÉ NO FUNCIONA CON -I EN EL MAKE????
#include "../../include/libmngTemplates.h" // POR QUÉ NO FUNCIONA CON -I EN EL MAKE????

#undef DEBUG
//#define DEBUG 1

class clsTransliterate;
class clsNormalize;
class clsConvert;

typedef clsTransliterate *handleTransliterate;
typedef clsNormalize     *handleNormalize;
typedef clsConvert       *handleConvert;
long cbl_length(char *sSource, size_t nSource);

class clsInit_libicumng {
public:
        clsInit_libicumng();
       ~clsInit_libicumng();
};

// Wrapper COBOL
extern "C" {

       //
       handleTransliterate mngTransliterateNew(unsigned char *TransliterateID);
       long                mngTransliterate(handleTransliterate *hTransliterate, const unsigned char *sSource, size_t lenSource, unsigned char *sTarget, size_t lenTarget);
       void                mngTransliterateFree(handleTransliterate *hTransliterate);

       handleNormalize mngNormalizeNew(unsigned char *NormalizeRules);
       long            mngNormalize(handleNormalize *hNormalize, const unsigned char *sSource, size_t lenSource, unsigned char *sTarget, size_t lenTarget);
       void            mngNormalizeFree(handleNormalize *hNormalize);

       handleConvert       mngConvertNew(void);
       long                mngConvert(handleConvert *hConvert, unsigned char *sSourceCodepage, unsigned char *sSource, size_t lenSource, unsigned char *sTargetCodepage, unsigned char *sTarget, size_t lenTarget);
       long                mngConvertGetIDs(handleConvert *hConvert, char* sID, size_t length_sID);
       void                mngConvertFree(handleConvert *hConvert);

       long mngICUCaseUTF8toUpper(const unsigned char *sSource, const size_t lenSource, const unsigned char *sTarget, const size_t lenTarget);
       long mngICUCaseUTF8toLower(const unsigned char *sSource, const size_t lenSource, const unsigned char *sTarget, const size_t lenTarget);
       long mngICUCaseUTF8toTitle(const unsigned char *sSource, const size_t lenSource, const unsigned char *sTarget, const size_t lenTarget);

}
