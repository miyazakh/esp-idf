

#define BENCH_EMBEDDED
#define USE_CERT_BUFFERS_2048

/* TLS 1.3                                 */
#define WOLFSSL_TLS13
#define HAVE_TLS_EXTENSIONS
#define WC_RSA_PSS
#define HAVE_HKDF
#define HAVE_FFDHE_2048
#define HAVE_AEAD
#define HAVE_SUPPORTED_CURVES

/* date/time                               */
/* if it cannot adjust time in the device, */
/* enable macro below                      */
/* #define NO_ASN_TIME */
/* #define XTIME time */

#define SINGLE_THREADED /* or define RTOS  option */
#define NO_FILESYSTEM

#define HAVE_AESGCM
#define WOLFSSL_SHA512
#define HAVE_ECC
#define HAVE_CURVE25519
#define CURVE25519_SMALL
#define HAVE_ED25519

/* debug options */
/* #define DEBUG_WOLFSSL */

/* debug: memory usage */
/* #define USE_WOLFSSL_MEMORY */
/* #define WOLFSSL_TRACK_MEMORY */
