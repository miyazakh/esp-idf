/* wolfcrypt esp_tsl.h
 *
 * Copyright (C) 2006-2018 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

#ifndef _ESP_TLS_H_
#define _ESP_TLS_H_

#include <stdbool.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <wolfcrypt/ssl.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief      ESP-TLS configuration parameters 
 */ 
typedef struct esp_tls_cfg {
    const char **alpn_protos;               /*!< Application protocols required for HTTP2.
                                                 If HTTP2/ALPN support is required, a list
                                                 of protocols that should be negotiated. 
                                                 The format is length followed by protocol
                                                 name. 
                                                 For the most common cases the following is ok:
                                                 "\x02h2"
                                                 - where the first '2' is the length of the protocol and
                                                 - the subsequent 'h2' is the protocol name */
 
    const unsigned char *cacert_pem_buf;    /*!< Certificate Authority's certificate in a buffer */
 
    unsigned int cacert_pem_bytes;          /*!< Size of Certificate Authority certificate
                                                 pointed to by cacert_pem_buf */
 
    bool non_block;                         /*!< Configure non-blocking mode. If set to true the 
                                                 underneath socket will be configured in non 
                                                 blocking mode after tls session is established */

    int timeout_ms;                         /*!< Network timeout in milliseconds */

    bool use_global_ca_store;               /*!< Use a global ca_store for all the connections in which
                                                 this bool is set. */
} esp_tls_cfg_t;

/**
 * @brief      ESP-TLS Connection Handle 
 */
typedef struct esp_tls {
   WOLFSSL *ssl;                                                                /*!< write file descriptors */
} esp_tls_t;

esp_tls_t *esp_tls_conn_new(const char *hostname, int hostlen, int port, const esp_tls_cfg_t *cfg);
esp_tls_t *esp_tls_conn_http_new(const char *url, const esp_tls_cfg_t *cfg);
//int esp_tls_conn_new_async(const char *hostname, int hostlen, int port, const esp_tls_cfg_t *cfg, esp_tls_t *tls);
//int esp_tls_conn_http_new_async(const char *url, const esp_tls_cfg_t *cfg, esp_tls_t *tls);

static inline ssize_t esp_tls_conn_write(esp_tls_t *tls, const void *data, size_t datalen)
{
    return wolfSSL_wirte((WOLFSSL *)tls, (byte *)data, datalen);
}

static inline ssize_t esp_tls_conn_read(esp_tls_t *tls, void  *data, size_t datalen)
{
    return wolfSSL_read((WOLFSSL *)tls, (byte *)data, datalen);
}

void esp_tls_conn_delete(esp_tls_t *tls);

//size_t esp_tls_get_bytes_avail(esp_tls_t *tls);
esp_err_t esp_tls_set_global_ca_store(const unsigned char *cacert_pem_buf, const unsigned int cacert_pem_bytes);
//mbedtls_x509_crt *esp_tls_get_global_ca_store();
//void esp_tls_free_global_ca_store();

#ifdef __cplusplus
}
#endif

#endif /* ! _ESP_TLS_H_ */
