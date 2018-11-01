
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
#define FREERTOS
#define WOLFSSL_LWIP
>>>>>>> Using FREERTOS and LWIP definition
#define WOLFSSL_ESPIDF
<<<<<<< HEAD
>>>>>>> Added wc_GenerateSeed() for ESP32
/* #define NO_MAIN_DRIVER */
=======
#define NO_MAIN_DRIVER
>>>>>>> add wolfSSL files
=======
/* #define NO_MAIN_DRIVER */
>>>>>>> Added wolfssl example server
=======

>>>>>>> Added SNTP to sync time.
#define BENCH_EMBEDDED
#define NO_WRITEV
#define USE_CERT_BUFFERS_2048
#define SIZEOF_LONG_LONG 8
<<<<<<< HEAD
#define NO_WOLFSSL_DIR 
<<<<<<< HEAD
<<<<<<< HEAD
#define WOLFSSL_NO_CURRDIR 
=======
#define NO_WOLFSSL_DIR
#define WOLFSSL_NO_CURRDIR
>>>>>>> Using FREERTOS and LWIP definition

/* TLS 1.3                                 */
#define WOLFSSL_TLS13
#define HAVE_TLS_EXTENSIONS
#define WC_RSA_PSS
#define HAVE_HKDF
#define HAVE_FFDHE_2048
#define HAVE_AEAD
#define HAVE_SUPPORTED_CURVES

<<<<<<< HEAD
<<<<<<< HEAD
// #define WOLFSSL_USER_CURRTIME /* for benchmark */
=======
#define WOLFSSL_NO_CURRDIR

#define WOLFSSL_USER_CURRTIME /* for benchmark */
>>>>>>> add wolfSSL files
=======
#define WOLFSSL_NO_CURRDIR 

// #define WOLFSSL_USER_CURRTIME /* for benchmark */
>>>>>>> Added wolfssl example server
#define NO_ASN_TIME
#define XTIME time
/* #define WOLFSSL_GENSEED_FORTEST*/ /* Wardning: define your own seed gen */
=======
=======
/* date/time                               */
/* if it cannot adjust time in the device, */
/* enable macro below                      */
>>>>>>> Use WOLFSSL_MSG() in server-tls.c
/* #define NO_ASN_TIME */
/* #define XTIME time */
>>>>>>> Added SNTP to sync time.

#define TFM_TIMING_RESISTANT
#define ECC_TIMING_RESISTANT
#define WC_RSA_BLINDING

<<<<<<< HEAD
<<<<<<< HEAD
#define SINGLE_THREADED /* or define RTOS  option */
/* #define WOLFSSL_CMSIS_RTOS */
#define NO_FILESYSTEM 
/* #define TEST_LOAD_BUFFER */
/* #define FORCE_BUFFER_TEST */
=======
#define SINGLE_THREADED  /* or define RTOS  option */
/* #define WOLFSSL_CMSIS_RTOS */
#define NO_FILESYSTEM
>>>>>>> add wolfSSL files
=======
#define SINGLE_THREADED /* or define RTOS  option */
<<<<<<< HEAD
/* #define WOLFSSL_CMSIS_RTOS */
/* #define NO_FILESYSTEM */
/* #define TEST_LOAD_BUFFER */
/* #define FORCE_BUFFER_TEST */
>>>>>>> Added wolfssl example server
=======
#define NO_FILESYSTEM
>>>>>>> Added wc_GenerateSeed() for ESP32

/* #define NO_DH */
#define HAVE_AESGCM
#define WOLFSSL_SHA512
#define HAVE_ECC
#define HAVE_CURVE25519
#define CURVE25519_SMALL
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Added wolfssl example server
#define HAVE_ED25519

/* debug options */
/* #define DEBUG_WOLFSSL */
<<<<<<< HEAD
/* #define WOLFSSL_LOG_PRINTF */
<<<<<<< HEAD
#define WOLFSSL_ESPIDF
<<<<<<< HEAD
<<<<<<< HEAD
=======
#define HAVE_ED25519
>>>>>>> add wolfSSL files
=======
>>>>>>> Added wolfssl example server
=======

/* memory usage */
/* #define USE_WOLFSSL_MEMORY */
#define WOLFSSL_TRACK_MEMORY
>>>>>>> Update
=======
=======
>>>>>>> Use WOLFSSL_MSG() in server-tls.c

/* debug: memory usage */
/* #define USE_WOLFSSL_MEMORY */
/* #define WOLFSSL_TRACK_MEMORY */
>>>>>>> Added wc_GenerateSeed() for ESP32
