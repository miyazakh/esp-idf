/* client-tls-callback.c
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

/* ESP specific */
#include "my_esp_wifi.h"

/* socket includes */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

/* wolfSSL */
#include <wolfssl/options.h>
#include <wolfssl/ssl.h>
#include <wolfssl/certs_test.h>


/* #define CERT_FILE "../certs/ca-cert.pem" */
#define CERT_FILE "./ca-cert.perm"

static const char *TAG = "tls_client";

int my_IORecv(WOLFSSL *ssl, char *buff, int sz, void *ctx)
{
    /* By default, ctx will be a pointer to the file descriptor to read from.
     * This can be changed by calling wolfSSL_SetIOReadCtx(). */
    int sockfd = *(int *)ctx;
    int recvd;

    /* Receive message from socket */
    if ((recvd = recv(sockfd, buff, sz, 0)) == -1)
    {
        /* error encountered. Be responsible and report it in wolfSSL terms */

        fprintf(stderr, "IO RECEIVE ERROR: ");
        switch (errno)
        {
#if EAGAIN != EWOULDBLOCK
        case EAGAIN: /* EAGAIN == EWOULDBLOCK on some systems, but not others */
#endif
        case EWOULDBLOCK:
            if (!wolfSSL_dtls(ssl) || wolfSSL_get_using_nonblock(ssl))
            {
                ESP_LOGI(TAG, "would block\n");
                return WOLFSSL_CBIO_ERR_WANT_READ;
            }
            else
            {
                ESP_LOGI(TAG, "socket timeout\n");
                return WOLFSSL_CBIO_ERR_TIMEOUT;
            }
        case ECONNRESET:
            ESP_LOGI(TAG, "connection reset\n");
            return WOLFSSL_CBIO_ERR_CONN_RST;
        case EINTR:
            ESP_LOGI(TAG, "socket interrupted\n");
            return WOLFSSL_CBIO_ERR_ISR;
        case ECONNREFUSED:
            ESP_LOGI(TAG, "connection refused\n");
            return WOLFSSL_CBIO_ERR_WANT_READ;
        case ECONNABORTED:
            ESP_LOGI(TAG, "connection aborted\n");
            return WOLFSSL_CBIO_ERR_CONN_CLOSE;
        default:
            ESP_LOGI(TAG, "general error\n");
            return WOLFSSL_CBIO_ERR_GENERAL;
        }
    }
    else if (recvd == 0)
    {
        printf("Connection closed\n");
        return WOLFSSL_CBIO_ERR_CONN_CLOSE;
    }

    /* successful receive */
    ESP_LOGI(TAG, "my_IORecv: received %d bytes from %d\n", sz, sockfd);
    return recvd;
}

int my_IOSend(WOLFSSL *ssl, char *buff, int sz, void *ctx)
{
    /* By default, ctx will be a pointer to the file descriptor to write to.
     * This can be changed by calling wolfSSL_SetIOWriteCtx(). */
    int sockfd = *(int *)ctx;
    int sent;

    /* Receive message from socket */
    if ((sent = send(sockfd, buff, sz, 0)) == -1)
    {
        /* error encountered. Be responsible and report it in wolfSSL terms */

        ESP_LOGI(TAG, "IO SEND ERROR: ");
        switch (errno)
        {
#if EAGAIN != EWOULDBLOCK
        case EAGAIN: /* EAGAIN == EWOULDBLOCK on some systems, but not others */
#endif
        case EWOULDBLOCK:
            ESP_LOGI(TAG, "would block\n");
            return WOLFSSL_CBIO_ERR_WANT_READ;
        case ECONNRESET:
            ESP_LOGI(TAG, "connection reset\n");
            return WOLFSSL_CBIO_ERR_CONN_RST;
        case EINTR:
            ESP_LOGI(TAG, "socket interrupted\n");
            return WOLFSSL_CBIO_ERR_ISR;
        case EPIPE:
            ESP_LOGI(TAG, "socket EPIPE\n");
            return WOLFSSL_CBIO_ERR_CONN_CLOSE;
        default:
            ESP_LOGI(TAG, "general error\n");
            return WOLFSSL_CBIO_ERR_GENERAL;
        }
    }
    else if (sent == 0)
    {
        ESP_LOGI(TAG, "Connection closed\n");
        return 0;
    }

    /* successful send */
    ESP_LOGI(TAG, "my_IOSend: sent %d bytes to %d\n", sz, sockfd);
    return sent;
}

//int app_main(int argc, char** argv)
void tls_smp_client_task()
{
    int ret;
    int sockfd;
    int retry_cnt;
    struct sockaddr_in servAddr;
    char buff[256];
    size_t len;

    /* declare wolfSSL objects */
    WOLFSSL_CTX *ctx;
    WOLFSSL *ssl;

    retry_cnt = 0;

    /* Check for proper calling convention */
#ifndef WOLFSSL_ESPIDF
    if (argc != 2) {
        printf("usage: %s <IPv4 address>\n", argv[0]);
        return 0;
    }
#endif
    ESP_LOGI(TAG, "entry app_main()");

#ifdef DEBUG_WOLFSSL
    wolfSSL_Debugging_ON();
#endif

    /* Initialize wolfSSL */
    wolfSSL_Init();

    /* Create a socket that uses an internet IPv4 address,
     * Sets the socket to be stream based (TCP),
     * 0 means choose the default protocol. */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        ESP_LOGI(TAG, "ERROR: failed to create the socket\n");
        return;
    }
<<<<<<< HEAD
<<<<<<< HEAD
    /* Create and initialize WOLFSSL_CTX */
    if ((ctx = wolfSSL_CTX_new(wolfSSLv23_client_method())) == NULL)
    {
        ESP_LOGI(TAG, "ERROR: failed to create WOLFSSL_CTX\n");
    }
    ESP_LOGI(TAG, "Start loading...cert");
    /* Load client certificates into WOLFSSL_CTX */
=======

=======
>>>>>>> Added README.md
    /* Create and initialize WOLFSSL_CTX */
    if ((ctx = wolfSSL_CTX_new(wolfSSLv23_client_method())) == NULL)
    {
        ESP_LOGI(TAG, "ERROR: failed to create WOLFSSL_CTX\n");
    }
    ESP_LOGI(TAG, "Start loading...cert");
    /* Load client certificates into WOLFSSL_CTX */
<<<<<<< HEAD

>>>>>>> Add simple tls_client with wolfssl
=======
>>>>>>> Added README.md
#ifndef NO_FILESYSTEM
    if (wolfSSL_CTX_load_verify_locations(ctx, CERT_FILE, NULL)){
         ESP_LOGI(TAG, "ERROR: failed to load %s %d, please check the file.\n",
                 CERT_FILE, a);
    }
#else
<<<<<<< HEAD
<<<<<<< HEAD
    if ((ret = wolfSSL_CTX_load_verify_buffer(ctx, ca_cert_der_2048,
=======
    if ((ret = wolfSSL_CTX_load_verify_buffer(ctx, ca_cert_der_2048, 
>>>>>>> Add simple tls_client with wolfssl
=======
    if ((ret = wolfSSL_CTX_load_verify_buffer(ctx, ca_cert_der_2048,
>>>>>>> Added README.md
        sizeof_ca_cert_der_2048, WOLFSSL_FILETYPE_ASN1)) != SSL_SUCCESS)
    {
        ESP_LOGI(TAG, "ERROR: failed to load %s %d, please check the file.\n",
                 CERT_FILE, ret);
    }
    ESP_LOGI(TAG, "Finish loading...cert");
#endif
    /* Register callbacks */
    wolfSSL_SetIORecv(ctx, my_IORecv);
    wolfSSL_SetIOSend(ctx, my_IOSend);

    ESP_LOGI(TAG, "Finish Register callbacks...");
    /* Initialize the server address struct with zeros */
    memset(&servAddr, 0, sizeof(servAddr));

    /* Fill in the server address */
    servAddr.sin_family = AF_INET;           /* using IPv4      */
    servAddr.sin_port = htons(DEFAULT_PORT); /* on DEFAULT_PORT */

    ESP_LOGI(TAG, "Start inet_pton()...");
    /* Get the server IPv4 address from the command line call */
    ESP_LOGI(TAG, "inet_pton");
    if ((ret = inet_pton(AF_INET, TLS_SMP_TARGET_HOST, &servAddr.sin_addr)) != 1)
    {
        ESP_LOGI(TAG, "ERROR: invalid address ret=%d\n", ret);
        return;
    }
    ESP_LOGI(TAG, "OK");

    /* Connect to the server */
<<<<<<< HEAD
<<<<<<< HEAD
    ESP_LOGI(TAG, "Connecting to server....%s(port:%d)", TLS_SMP_TARGET_HOST,
=======
    ESP_LOGI(TAG, "Connecting to server....%s(port:%d)", TLS_SMP_TARGET_HOST, 
>>>>>>> Add simple tls_client with wolfssl
=======
    ESP_LOGI(TAG, "Connecting to server....%s(port:%d)", TLS_SMP_TARGET_HOST,
>>>>>>> Added README.md
                                                                  DEFAULT_PORT);
retry:
    if ((ret = connect(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr))) == -1)
    {
        ESP_LOGI(TAG, "ERROR: failed to connect ret=%d\n", ret);
        /* re-try */
        sleep(5);
        if(++retry_cnt>5) {
<<<<<<< HEAD
<<<<<<< HEAD
             ESP_LOGI(TAG, "ERROR: failed to connect ret=%d, retry cnt %d\n",
                    ret, retry_cnt);
            return;
        };
        ESP_LOGI(TAG, "ERROR: failed to connect ret=%d, retry cnt %d\n",
=======
             ESP_LOGI(TAG, "ERROR: failed to connect ret=%d, retry cnt %d\n", 
                    ret, retry_cnt);
            return;
        };
        ESP_LOGI(TAG, "ERROR: failed to connect ret=%d, retry cnt %d\n", 
>>>>>>> Add simple tls_client with wolfssl
=======
             ESP_LOGI(TAG, "ERROR: failed to connect ret=%d, retry cnt %d\n",
                    ret, retry_cnt);
            return;
        };
        ESP_LOGI(TAG, "ERROR: failed to connect ret=%d, retry cnt %d\n",
>>>>>>> Added README.md
                    ret, retry_cnt);
        goto retry;
    }
    ESP_LOGI(TAG, "OK");

    ESP_LOGI(TAG, "Create a WOLFSSL object");
    /* Create a WOLFSSL object */
    if ((ssl = wolfSSL_new(ctx)) == NULL)
    {
        ESP_LOGI(TAG, "ERROR: failed to create WOLFSSL object\n");
        return;
    }
    ESP_LOGI(TAG, "OK");

    /* Attach wolfSSL to the socket */
    wolfSSL_set_fd(ssl, sockfd);

    ESP_LOGI(TAG, "Connect to wolfSSL on the server side");
    /* Connect to wolfSSL on the server side */
    if (wolfSSL_connect(ssl) != SSL_SUCCESS)
    {
        ESP_LOGI(TAG, "ERROR: failed to connect to wolfSSL\n");
        return;
    }
    ESP_LOGI(TAG, "OK");
    /* Get a message for the server from stdin */
    printf("Message for server: ");
    memset(buff, 0, sizeof(buff));
<<<<<<< HEAD
<<<<<<< HEAD
    sprintf(buff, "message from client\n");
=======
    fgets(buff, sizeof(buff), stdin);
>>>>>>> Add simple tls_client with wolfssl
=======
    sprintf(buff, "message from client\n");
>>>>>>> Added README.md
    len = strnlen(buff, sizeof(buff));

    /* Send the message to the server */
    if (wolfSSL_write(ssl, buff, len) != len)
    {
        ESP_LOGI(TAG, "ERROR: failed to write\n");
        return;
    }
<<<<<<< HEAD
<<<<<<< HEAD
    ESP_LOGI(TAG, "Write OK");
=======

>>>>>>> Add simple tls_client with wolfssl
=======
    ESP_LOGI(TAG, "Write OK");
>>>>>>> Added README.md
    /* Read the server data into our buff array */
    memset(buff, 0, sizeof(buff));
    if (wolfSSL_read(ssl, buff, sizeof(buff) - 1) == -1)
    {
        ESP_LOGI(TAG, "ERROR: failed to read\n");
        return;
    }
<<<<<<< HEAD
<<<<<<< HEAD
     ESP_LOGI(TAG, "Read OK");
=======

>>>>>>> Add simple tls_client with wolfssl
=======
     ESP_LOGI(TAG, "Read OK");
>>>>>>> Added README.md
    /* Print to stdout any data the server sends */
    ESP_LOGI(TAG, "Server: %s\n", buff);

    /* Cleanup and return */
    wolfSSL_free(ssl);     /* Free the wolfSSL object                  */
    wolfSSL_CTX_free(ctx); /* Free the wolfSSL context object          */
    wolfSSL_Cleanup();     /* Cleanup the wolfSSL environment          */
    close(sockfd);         /* Close the connection to the server       */
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Added README.md

    vTaskDelete(NULL);
    return;                /* Return reporting a success               */
}
<<<<<<< HEAD
=======
    return;                /* Return reporting a success               */
}
>>>>>>> Add simple tls_client with wolfssl
=======
>>>>>>> Added README.md
