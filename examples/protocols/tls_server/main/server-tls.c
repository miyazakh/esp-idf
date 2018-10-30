/* server-tls-callback.c
 *
 * Copyright (C) 2006-2015 wolfSSL Inc.
 *
 * This file is part of wolfSSL. (formerly known as CyaSSL)
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* the usual suspects */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* socket includes */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

/* wolfSSL */
#include <wolfssl/options.h>
#include <wolfssl/ssl.h>

/* buffer cert */
#include <wolfssl/certs_test.h>

/* ESP specific */
#include "my_esp_wifi.h"

#ifdef WOLFSSL_TRACK_MEMORY
    #include <wolfssl/wolfcrypt/mem_track.h>
#endif

static const char *TAG = "tls_server";

void tls_smp_server_task()
{
    int                sockfd;
    int                connd;
    struct sockaddr_in servAddr;
    struct sockaddr_in clientAddr;
    socklen_t          size = sizeof(clientAddr);
    char               buff[256];
    size_t             len;
    int                shutdown = 0;
    int                ret;

    /* declare wolfSSL objects */
    WOLFSSL_CTX* ctx;
    WOLFSSL*     ssl;

    ESP_LOGI(TAG, "start app_main()");

#ifdef DEBUG_WOLFSSL
    ESP_LOGI(TAG, "Debug ON");
    wolfSSL_Debugging_ON();
#endif
#ifdef WOLFSSL_TRACK_MEMORY
    InitMemoryTracker();
#endif
    /* Initialize wolfSSL */
    ESP_LOGI(TAG, "start wolfSSL_Init()");
    wolfSSL_Init();

    /* Create a socket that uses an internet IPv4 address,
     * Sets the socket to be stream based (TCP),
     * 0 means choose the default protocol. */
    ESP_LOGI(TAG, "start socket())");
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        ESP_LOGI(TAG,"ERROR: failed to create the socket");
    }
    ESP_LOGI(TAG, "finish socket())");
   
    /* Create and initialize WOLFSSL_CTX */
    ESP_LOGI(TAG, "Create and initialize WOLFSSL_CTX");
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    ESP_LOGI(TAG, " Create wolfSSLv23_server_method()");
    if ((ctx = wolfSSL_CTX_new(wolfSSLv23_server_method())) == NULL)
    {
=======
    if ((ctx = wolfSSL_CTX_new(wolfTLSv1_2_server_method())) == NULL) {
>>>>>>> Added tls_server based on wolfssl
=======
    ESP_LOGI(TAG, " Create wolfSSLv23_server_method()");
    if ((ctx = wolfSSL_CTX_new(wolfSSLv23_server_method())) == NULL)
    {
>>>>>>> Use wolfSSLv23_server_method()
        fprintf(stderr, "ERROR: failed to create WOLFSSL_CTX\n");
        return;
=======
    ESP_LOGI(TAG, "Create wolfSSLv23_server_method()");
    if ((ctx = wolfSSL_CTX_new(wolfSSLv23_server_method())) == NULL) {
        ESP_LOGI(TAG, "ERROR: failed to create WOLFSSL_CTX");
>>>>>>> Added SNTP to sync time.
    }

    /* Load server certificates into WOLFSSL_CTX */
    if ((ret = wolfSSL_CTX_use_certificate_buffer(ctx, server_cert_der_2048,
<<<<<<< HEAD
<<<<<<< HEAD
                        sizeof_server_cert_der_2048,
=======
                        sizeof_server_cert_der_2048, 
>>>>>>> Added tls_server based on wolfssl
=======
                        sizeof_server_cert_der_2048,
>>>>>>> Use wolfSSLv23_server_method()
                        WOLFSSL_FILETYPE_ASN1)) != SSL_SUCCESS) {
        ESP_LOGI(TAG, "ERROR: failed to load (ret=%d,) please check.", ret);
    }

    ESP_LOGI(TAG, "Finish loading...cert");

    /* Load server key into WOLFSSL_CTX */
<<<<<<< HEAD
#ifndef NO_FILESYSTEM
    if (wolfSSL_CTX_use_PrivateKey_file(ctx, KEY_FILE, SSL_FILETYPE_PEM)
        != SSL_SUCCESS) {
        fprintf(stderSSL_SUCCESSr, "ERROR: failed to load %s, please check the file.\n",
                KEY_FILE);
        return;
    }
#else

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Update
    if((ret=wolfSSL_CTX_use_PrivateKey_buffer(ctx,
                            server_key_der_2048, sizeof_server_key_der_2048,
=======
    if((ret=wolfSSL_CTX_use_PrivateKey_buffer(ctx, 
                            server_key_der_2048, sizeof_server_key_der_2048, 
>>>>>>> Added tls_server based on wolfssl
=======
    if((ret=wolfSSL_CTX_use_PrivateKey_buffer(ctx,
                            server_key_der_2048, sizeof_server_key_der_2048,
>>>>>>> Use wolfSSLv23_server_method()
                            WOLFSSL_FILETYPE_ASN1)) != SSL_SUCCESS) {
        ESP_LOGI(TAG, "ERROR: failed to load (ret=%d,) please check.", ret);
    }

    ESP_LOGI(TAG, "Finish loading...key");

<<<<<<< HEAD
<<<<<<< HEAD
#endif

<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> Added tls_server based on wolfssl
=======
>>>>>>> Use wolfSSLv23_server_method()
=======
>>>>>>> Update
    /* Register callbacks */
    /* wolfSSL_SetIORecv(ctx, my_IORecv); */
    /* wolfSSL_SetIOSend(ctx, my_IOSend); */

=======
>>>>>>> Added SNTP to sync time.
    /* Initialize the server address struct with zeros */
    memset(&servAddr, 0, sizeof(servAddr));

    /* Fill in the server address */
    servAddr.sin_family      = AF_INET;             /* using IPv4      */
    servAddr.sin_port        = htons(DEFAULT_PORT); /* on DEFAULT_PORT */
    servAddr.sin_addr.s_addr = INADDR_ANY;          /* from anywhere   */

    /* Bind the server socket to our port */
    if (bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
         ESP_LOGI(TAG, "ERROR: failed to bind");
    }

    /* Listen for a new connection, allow 5 pending connections */
    if (listen(sockfd, 5) == -1) {
         ESP_LOGI(TAG, "ERROR: failed to listen");
    }

    /* Continue to accept clients until shutdown is issued */
    while (!shutdown) {
         ESP_LOGI(TAG,"Waiting for a connection...");

        /* Accept client connections */
        if ((connd = accept(sockfd, (struct sockaddr*)&clientAddr, &size))
            == -1) {
             ESP_LOGI(TAG, "ERROR: failed to accept the connection");
        }

        /* Create a WOLFSSL object */
        if ((ssl = wolfSSL_new(ctx)) == NULL) {
             ESP_LOGI(TAG, "ERROR: failed to create WOLFSSL object");
        }

        /* Attach wolfSSL to the socket */
        wolfSSL_set_fd(ssl, connd);
        /* Establish TLS connection */
        ret = wolfSSL_accept(ssl);
        if (ret != SSL_SUCCESS) {
            ESP_LOGI(TAG, "wolfSSL_accept error = %d",
                wolfSSL_get_error(ssl, ret));
        }
        ESP_LOGI(TAG,"Client connected successfully");

        /* Read the client data into our buff array */
        memset(buff, 0, sizeof(buff));
        if (wolfSSL_read(ssl, buff, sizeof(buff)-1) == -1) {
            ESP_LOGI(TAG, "ERROR: failed to read");
        }

        /* Print to stdout any data the client sends */
        ESP_LOGI(TAG,"Client: %s", buff);

        /* Check for server shutdown command */
        if (strncmp(buff, "shutdown", 8) == 0) {
            ESP_LOGI(TAG,"Shutdown command issued!");
            shutdown = 1;
        }

        /* Write our reply into buff */
        memset(buff, 0, sizeof(buff));
        memcpy(buff, "I hear ya fa shizzle!", sizeof(buff));
        len = strnlen(buff, sizeof(buff));

        /* Reply back to the client */
        if (wolfSSL_write(ssl, buff, len) != len) {
            ESP_LOGI(TAG, "ERROR: failed to write");
        }

#ifdef WOLFSSL_TRACK_MEMORY
        ShowMemoryTracker();
#endif
        /* Cleanup after this connection */
        wolfSSL_free(ssl);      /* Free the wolfSSL object              */
        close(connd);           /* Close the connection to the client   */
    }

    /* Cleanup and return */
    wolfSSL_CTX_free(ctx);  /* Free the wolfSSL context object          */
    wolfSSL_Cleanup();      /* Cleanup the wolfSSL environment          */
    close(sockfd);          /* Close the socket listening for clients   */

<<<<<<< HEAD
<<<<<<< HEAD
    vTaskDelete(NULL);

=======
>>>>>>> Added tls_server based on wolfssl
=======
    vTaskDelete(NULL);

>>>>>>> Added README.md
    return;                 /* Return reporting a success               */
}
