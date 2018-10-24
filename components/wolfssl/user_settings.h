
/* #define NO_MAIN_DRIVER */
#define BENCH_EMBEDDED
#define NO_WRITEV
#define WOLFSSL_USER_IO
#define NO_DEV_RANDOM
#define USE_CERT_BUFFERS_2048
#define WOLFSSL_USER_CURRTIME
#define SIZEOF_LONG_LONG 8
#define NO_WOLFSSL_DIR 
#define WOLFSSL_NO_CURRDIR 

/* TLS 1.3 */
#define WOLFSSL_TLS13
#define HAVE_TLS_EXTENSIONS
#define WC_RSA_PSS
#define HAVE_HKDF
#define HAVE_FFDHE_2048
#define HAVE_AEAD
#define HAVE_SUPPORTED_CURVES

// #define WOLFSSL_USER_CURRTIME /* for benchmark */
#define NO_ASN_TIME
#define XTIME time
#define WOLFSSL_GENSEED_FORTEST /* Wardning: define your own seed gen */

#define TFM_TIMING_RESISTANT
#define ECC_TIMING_RESISTANT
#define WC_RSA_BLINDING

#define SINGLE_THREADED /* or define RTOS  option */
/* #define WOLFSSL_CMSIS_RTOS */
#define NO_FILESYSTEM 
/* #define TEST_LOAD_BUFFER */
/* #define FORCE_BUFFER_TEST */

/* #define NO_DH */
#define HAVE_AESGCM
#define WOLFSSL_SHA512
#define HAVE_ECC
#define HAVE_CURVE25519
#define CURVE25519_SMALL
#define HAVE_ED25519

#define DEBUG_WOLFSSL
#define WOLFSSL_LOG_PRINTF
#define WOLFSSL_ESPIDF
