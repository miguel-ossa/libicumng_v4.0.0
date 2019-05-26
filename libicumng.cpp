// Version 3.0.0 - Nuevo parametro de tamaño maximo de salida

//#include "unicode/uclean.h"
//#include "unicode/unistr.h"
//#include "unicode/calendar.h"
//#include "unicode/datefmt.h"

#include "libicumng.h"

clsInit_libicumng InitLib; // Instanciamos para controlar carga y descarga.

// RuleBasedTransliterator rules to remove accents from characters
// so they can be displayed as ASCIIx

UnicodeString m_unaccent_RULES =
(
    "[\\u00C0-\\u00C5] > A;"
    "[\\u00C8-\\u00CB] > E;"
    "[\\u00CC-\\u00CF] > I;"
    "[\\u00E0-\\u00E5] > a;"
    "[\\u00E8-\\u00EB] > e;"
    "[\\u00EC-\\u00EF] > i;"
    "[\\u0300-\\u036F] > ;"
    "[\\u2074-\\u207F] > ;"
    );

long cbl_length(char *sSource, size_t nSource)
{
       size_t offset = 0;
       for (; ((offset < (nSource-1)) && (sSource[offset] != 0x00)); offset++);
       if (sSource[offset] == 0x00) offset--;
       nSource = offset + 1;
       for (; ((nSource > 0) && ((sSource[offset] == 0x20) || (sSource[offset] == 0x00 ))); offset--, nSource--);

       return(nSource);
}

//---------------------------------------------------------------------
clsInit_libicumng::clsInit_libicumng(void)
{
    /* Carga dinamica de la libreria "liberrmng.so" */
    Carga_LibErrMNG();
}
//---------------------------------------------------------------------
clsInit_libicumng::~clsInit_libicumng(void)
{
  if (myclsLibErrMNG != NULL) destroy( myclsLibErrMNG );
}
//---------------------------------------------------------------------

//----------------------------------------------------------------------
class clsTransliterate {
public:
       clsTransliterate(unsigned char *sTransliterateID);
       ~clsTransliterate(void);
       long Transliterate(const unsigned char *sSource, size_t lenSource, unsigned char *sTarget, size_t lenTarget);
  private:
       Transliterator *m_oTransliterator;
       Transliterator *m_rbtm_unaccent;
       Transliterator *m_unaccent;
       UnicodeString m_normalizeRules;
       UParseError m_pError;
       UErrorCode m_status;
};


clsTransliterate::clsTransliterate(unsigned char *sTransliterateID)
{
    /* Carga dinamica de la libreria "liberrmng.so" */
    //Carga_LibErrMNG();
    if (sTransliterateID != NULL) {

       std::string strTransliterationID((char*)sTransliterateID);

       m_status = U_ZERO_ERROR;
       u_init(&m_status);
       if (U_SUCCESS(m_status)) {
          m_oTransliterator = Transliterator::createInstance(UnicodeString::fromUTF8((char*)sTransliterateID), UTRANS_FORWARD, m_status);
      }
   }
}

clsTransliterate::~clsTransliterate(void)
{
  if (m_oTransliterator != NULL) { delete m_oTransliterator; m_oTransliterator = NULL; }
  if (m_rbtm_unaccent != NULL) { delete m_rbtm_unaccent; m_rbtm_unaccent = NULL; }
  if (m_unaccent != NULL) { delete m_unaccent; m_unaccent = NULL; }
  //if (myclsLibErrMNG != NULL) destroy( myclsLibErrMNG );
}

long clsTransliterate::Transliterate(const unsigned char *sSource, size_t lenSource, unsigned char *sTarget, size_t lenTarget)
{
    if ((sSource == NULL) || (lenSource < 1) ) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_002;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: Parameter cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_001);
#endif
      return(_LIBICUMNG_ERRCOD_001);
    }

    if (lenTarget < 1) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_002;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: lenTarget not informed\n");
      exit(_LIBICUMNG_ERRCOD_002);
#endif
      return(_LIBICUMNG_ERRCOD_002);
    }

    UnicodeString str;

    char *mySource = strndup((char*)sSource, cbl_length((char*)sSource, lenSource));
    if (mySource == NULL) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_003;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: Parameter cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_003);
#endif
      return(_LIBICUMNG_ERRCOD_003);
    }

    // Convert Source to unicode
    str =  UnicodeString::fromUTF8(mySource);
    free(mySource);
    if (str == NULL) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_004;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsTransliterate::Transliterate() parameter cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_004);
#endif
      return(_LIBICUMNG_ERRCOD_004);
    }
    // Transliterate
    try {
       m_oTransliterator->transliterate(str);
    } catch (const std::invalid_argument& e) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_005;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsTransliterate::Transliterate() Invalid argument\n");
      exit(_LIBICUMNG_ERRCOD_005);
#endif
      return(_LIBICUMNG_ERRCOD_005);
    };
    // Convert transliteration to utf-8
    std::string utf8_transliterated;
    str.toUTF8String(utf8_transliterated);
    // Copy transliteration to Destination
    memcpy((char*)sTarget, (char*)'\20', lenTarget);
    size_t lenTransliteration = strlen((char*)utf8_transliterated.c_str());
    if (lenTransliteration > lenTarget) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_006;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsTransliterate::transliterate() Size exceeded\n");
      exit(_LIBICUMNG_ERRCOD_006);
#endif
      return(_LIBICUMNG_ERRCOD_006);
    }
    else {
      strncpy((char*)sTarget, (char*)utf8_transliterated.c_str(), lenTransliteration);

      return((long)lenTransliteration);
    }
}

//----------------------------------------------------------------------
class clsNormalize {
public:
       clsNormalize(unsigned char *sm_normalizeRules);
       ~clsNormalize(void);
       long Normalize(const unsigned char *sSource, size_t lenSource, unsigned char *sTarget, size_t lenTarget);
  private:
       Transliterator *m_rbtm_unaccent;
       Transliterator *m_unaccent;
       UParseError m_pError;
       UnicodeString m_normalizeRules;
       UErrorCode m_status;
};

clsNormalize::clsNormalize(unsigned char *sm_normalizeRules)
{

   /* Carga dinamica de la libreria "liberrmng.so" */
   //Carga_LibErrMNG();
   if (sm_normalizeRules == NULL) {
      m_normalizeRules = m_unaccent_RULES;
   }
   else {
      UnicodeString strRules =  UnicodeString::fromUTF8((char*)sm_normalizeRules);
      m_normalizeRules = strRules;
   }

//#ifdef DEBUG
//      uprintf(m_normalizeRules);
//      std::cout << " " << std::endl;
//#endif

   m_status = U_ZERO_ERROR;
   u_init(&m_status);
   if (U_SUCCESS(m_status)) {

      // Create a custom Transliterator

      m_rbtm_unaccent = Transliterator::createFromRules("m_rbtm_unaccent",
                                                     (UnicodeString&)m_normalizeRules,
                                                     UTRANS_FORWARD,
                                                     m_pError,
                                                     m_status);
      check(m_status, "Transliterator::createFromRules");

      // Create another custom Transliterator
      m_unaccent = new UnaccentTransliterator();

   }
}

clsNormalize::~clsNormalize(void)
{
  if (m_rbtm_unaccent != NULL) { delete m_rbtm_unaccent; m_rbtm_unaccent = NULL; }
  if (m_unaccent != NULL) { delete m_unaccent; m_unaccent = NULL; }
  //if (myclsLibErrMNG != NULL) destroy( myclsLibErrMNG );
}

long clsNormalize::Normalize(const unsigned char *sSource, size_t lenSource, unsigned char *sTarget, size_t lenTarget)
{
    if (m_rbtm_unaccent == NULL) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_007;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsNormalize::Normalize() m_rbtm_unaccent cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_007);
#endif
      return(_LIBICUMNG_ERRCOD_007);
    }
    if ((sSource == NULL) || (lenSource < 1) ) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_008;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsNormalize::Normalize() Source parameter cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_008);
#endif
      return(_LIBICUMNG_ERRCOD_008);
    }
    if (lenTarget < 1) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_009;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsNormalize::Normalize() lenTarget not informed\n");
      exit(_LIBICUMNG_ERRCOD_009);
#endif
      return(_LIBICUMNG_ERRCOD_009);
    }
    UnicodeString str;

    char *mySource = strndup((char*)sSource, cbl_length((char*)sSource, lenSource));
    if (mySource == NULL) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_010;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsNormalize::Normalize() Parameter cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_010);
#endif
      return(_LIBICUMNG_ERRCOD_010);
    }

    // Convert Source to unicode
    str =  UnicodeString::fromUTF8((char*)mySource);
    free(mySource);
    if (str == NULL) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_011;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsNormalize::Normalize() Parameter cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_011);
#endif
      return(_LIBICUMNG_ERRCOD_011);
    }
    // Normalize transliteration
    try {
       m_rbtm_unaccent->transliterate(str);
       m_unaccent->transliterate(str);
    } catch (const std::invalid_argument& e) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_012;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsNormalize::Normalize() Invalid argument\n");
      exit(_LIBICUMNG_ERRCOD_012);
#endif
      return(_LIBICUMNG_ERRCOD_012);
    };
    // Convert normalization to utf-8
    std::string utf8_normalized;
    str.toUTF8String(utf8_normalized);
    // Copy normalization to Normalized
    memcpy((char*)sTarget, (char*)'\20', lenTarget);
    size_t lenNormalization = strlen((char*)utf8_normalized.c_str());
    if (lenNormalization > lenTarget) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_013;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsNormalize::normalize Size exceeded\n");
      exit(_LIBICUMNG_ERRCOD_013);
#endif
      return(_LIBICUMNG_ERRCOD_013);
    }
    else {
      strncpy((char*)sTarget, (char*)utf8_normalized.c_str(), strlen((char*)utf8_normalized.c_str()));

      return((long)strlen((char*)utf8_normalized.c_str()));
    }
}

//----------------------------------------------------------------------
class clsConvert {
public:
       clsConvert(void);
       ~clsConvert();
       long Convert(unsigned char *sSourceCodepage,
                    unsigned char *sSource,
                    size_t         lenSource,
                    unsigned char *sTargetCodepage,
                    unsigned char *sTarget,
                    size_t         lenTarget);
       long GetAvailableIDs(char* sID, size_t length_sID);
private:
       //Converter *oConventer;
       UParseError m_pError;
       UErrorCode m_status;
       int m_element;
};

clsConvert::clsConvert(void)
{
  /* Carga dinamica de la libreria "liberrmng.so" */
  //Carga_LibErrMNG();
}

clsConvert::~clsConvert(void)
{
  //if (myclsLibErrMNG != NULL) destroy( myclsLibErrMNG );
}

long clsConvert::Convert(unsigned char *sSourceCodepage,
                         unsigned char *sSource,
                         size_t         lenSource,
                         unsigned char *sTargetCodepage,
                         unsigned char *sTarget,
                         size_t         lenTarget)
{
    if (this == NULL) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_014;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsConvert::Convert() This object cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_014);
#endif
      return(_LIBICUMNG_ERRCOD_014);
    }
    if (sSourceCodepage == NULL) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_015;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsConvert::Convert() Parameter 'sSourceCodepage' cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_015);
#endif
      return(_LIBICUMNG_ERRCOD_015);
    }
    if (sSource == NULL) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_016;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsConvert::Convert() Parameter 'sSource' cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_016);
#endif
      return(_LIBICUMNG_ERRCOD_016);
    }
    if (sTargetCodepage == NULL) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_017;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsConvert::Convert() Parameter 'sTargetCodepage' cannot be null\n");
      exit(_LIBICUMNG_ERRCOD_017);
#endif
      return(_LIBICUMNG_ERRCOD_017);
    }
    if (lenTarget == 0) {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_018;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsConvert::Convert() Parameter 'lenTarget' cannot be zero\n");
      exit(_LIBICUMNG_ERRCOD_018);
#endif
      return(_LIBICUMNG_ERRCOD_018);
    }
    size_t myLenSource = cbl_length((char*)sSource, lenSource);

    long result = (long)ucnv_convert((const char*)sTargetCodepage,
	                             (const char*)sSourceCodepage,
	                             (char*)sTarget,
	                             (int)lenTarget,
	                             (const char*)sSource,
	                             (int)myLenSource,
	                             &m_status);
	  if (U_SUCCESS(m_status)) {
       return ((long)(result));
	  }
	  else {
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_019;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsConvert::Convert() Error in ucnv_convert\n");
      exit(_LIBICUMNG_ERRCOD_019);
#endif
      return(_LIBICUMNG_ERRCOD_019);
    }
}

/*--------------------------------------------------------------*\
 * Recibe inicialmente "m_element" = 0,                         *
 * "sID" como parámetro de salida y "length_sID" su longitud.   *
 * "m_element" se incrementa con cada llamada, y finaliza cuan- *
 * do la función devuelve un negativo.                          *
 *                                                              *
\*--------------------------------------------------------------*/
long clsConvert::GetAvailableIDs(char* sID, size_t length_sID)
{
    UErrorCode err = U_ZERO_ERROR;
    if (m_element < ucnv_countAvailable())
    {
       char *chrElement = (char*)ucnv_getAvailableName(m_element);
       if (chrElement != NULL) {
          for (long i=0; i<length_sID; i++)
          {
             if (i<strlen(ucnv_getAvailableName(m_element))) {
               *sID++ = ucnv_getAvailableName(m_element)[i];
             }
             else {
               *sID++ = 0x20;
             }
          }
          int antElement = m_element;
          m_element++;

          return (long)(strlen(ucnv_getAvailableName(antElement)));
       }
       else {
          m_element = 0;
#ifdef DEBUG
          printFunctionTrace(1);
          _LIBICUMNG_ERRSTR_020;
          myclsLibErrMNG->mngPerror(libmng_errstr);
          //printf("ERROR: clsConvert::GetAvailableIDs() End of available IDs\n");
          exit(_LIBICUMNG_ERRCOD_020);
#endif
          return(_LIBICUMNG_ERRCOD_020);
       }
    }
    else
    {
       m_element = 0;
#ifdef DEBUG
      printFunctionTrace(1);
      _LIBICUMNG_ERRSTR_020;
      myclsLibErrMNG->mngPerror(libmng_errstr);
      //printf("ERROR: clsConvert::GetAvailableIDs() End of available IDs\n");
      exit(_LIBICUMNG_ERRCOD_020);
#endif
      return(_LIBICUMNG_ERRCOD_020);
    }
}
//----------------------------------------------------------------------
#define CASE_ERROR_OFFSET 10000
#define caseLower 1
#define caseUpper 2
#define caseTitle 3
long mngICUCaseUTF8(const unsigned char *sSource,
                    const size_t         lenSource,
                    const unsigned char *sTarget,
                    const size_t         lenTarget,
                    const unsigned char *sLocale,
                    const unsigned short cCase)
{
       int32_t myTargetLen, mySourceLen;
       UErrorCode status = U_ZERO_ERROR;
       UBreakIterator *uBrk;

//     Limpiamos destino *> Limpiamos solo RESTO
       memset((void *)sTarget, 0x20, lenTarget);

       u_init(&status);

       UCaseMap *caseMap=ucasemap_open((char *)sLocale, 0, &status);
       if (U_FAILURE(status)) return(-1*CASE_ERROR_OFFSET);

//     Calculamos capacidad necesaria del destino (Upper y Lower no necesariamente miden lo mismo)
       //MOSSA
       //char *mySource = strndup((char*)sSource, cbl_length((char*)sSource, lenSource));
       mySourceLen=cbl_length((char *)sSource, lenSource);
       //mySource[mySourceLen] = 0x0;
       //printf("mySource=%s\n", mySource);
       //for(int i=0; i<mySourceLen; i++) printf("%02x", mySource[i]);
       //printf("mySourceLen=%d\n", mySourceLen);
       //MOSSA

//     Preservamos Source si es el mismo que Target
//       if (sSource == sTarget) memcpy(mySource, mySource = (char *)malloc(lenSource), mySourceLen);
//       else mySource = (char *)sSource;

//     Aplicamos CASE
       switch(cCase)
       {
          case caseLower: myTargetLen = ucasemap_utf8ToLower(caseMap, (char *)sTarget, lenTarget, (char *)sSource, mySourceLen, &status); break;
          case caseUpper: myTargetLen = ucasemap_utf8ToUpper(caseMap, (char *)sTarget, lenTarget, (char *)sSource, mySourceLen, &status); break;
          case caseTitle: uBrk=ubrk_open(UBRK_SENTENCE, (char *)sLocale, NULL, 0, &status);
                          ucasemap_setBreakIterator(caseMap, uBrk, &status);
                          myTargetLen = ucasemap_utf8ToTitle(caseMap, (char *)sTarget, lenTarget, (char *)sSource, mySourceLen, &status);
                          ubrk_close(uBrk);
                          break;
          default:        ucasemap_close(caseMap);
                          //if (sSource == sTarget) free(mySource);
                          return(-4*CASE_ERROR_OFFSET);
       }

//     Limpiamos resto de destino
//       memset((void *)sTarget+OFF, 0x20, lenTarget-myTargetLen);

//     Liberamos recursos y acabamos
       ucasemap_close(caseMap);
       return((U_FAILURE(status))?(-1*status):myTargetLen);
}

//----------------------------------------------------------------------
// Wrapper COBOL
extern "C" {

handleTransliterate mngTransliterateNew(unsigned char *TransliterateID){return(new clsTransliterate(TransliterateID));}
long                mngTransliterate(handleTransliterate *hTransliterate, const unsigned char *sSource, size_t lenSource, unsigned char *sTarget, size_t lenTarget){return((*hTransliterate)->Transliterate(sSource, lenSource, sTarget, lenTarget));}
void                mngTransliterateFree(handleTransliterate *hTransliterate){delete hTransliterate; *hTransliterate = NULL;}

handleNormalize     mngNormalizeNew(unsigned char *m_normalizeRules){return(new clsNormalize(m_normalizeRules));}
long                mngNormalize(handleNormalize *hNormalize, const unsigned char *sSource, size_t lenSource, unsigned char *sTarget, size_t lenTarget){return((*hNormalize)->Normalize(sSource, lenSource, sTarget, lenTarget));}
void                mngNormalizeFree(handleNormalize *hNormalize){delete hNormalize; *hNormalize = NULL;}

handleConvert       mngConvertNew(void){return(new clsConvert());}
long                mngConvert(handleConvert *hConvert,
                               unsigned char *sSourceCodepage,
                               unsigned char *sSource,
                               size_t         lenSource,
                               unsigned char *sTargetCodepage,
                               unsigned char *sTarget,
                               size_t         lenTarget){return((*hConvert)->Convert(sSourceCodepage, sSource, lenSource, sTargetCodepage, sTarget, lenTarget));}
long                mngConvertGetIDs(handleConvert *hConvert, char* sID, size_t length_sID){return((*hConvert)->GetAvailableIDs(sID, length_sID));}
void                mngConvertFree(handleConvert *hConvert) {delete hConvert; *hConvert = NULL;}


long   mngICUCaseUTF8toUpper(const unsigned char *sSource,
                             const size_t         lenSource,
                             const unsigned char *sTarget,
                             const size_t         lenTarget)
//                           const unsigned char *sLocale)
       {return(mngICUCaseUTF8(sSource, lenSource, sTarget, lenTarget, NULL, caseUpper));}

long   mngICUCaseUTF8toLower(const unsigned char *sSource,
                             const size_t         lenSource,
                             const unsigned char *sTarget,
                             const size_t         lenTarget)
//                           const unsigned char *sLocale)
       {return(mngICUCaseUTF8(sSource, lenSource, sTarget, lenTarget, NULL, caseLower));}

long   mngICUCaseUTF8toTitle(const unsigned char *sSource,
                             const size_t         lenSource,
                             const unsigned char *sTarget,
                             const size_t         lenTarget)
//                           const unsigned char *sLocale)
       {return(mngICUCaseUTF8(sSource, lenSource, sTarget, lenTarget, NULL, caseTitle));}

} // of extern "C"

