/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/* This file configures mbed TLS for FreeRTOS. */

#ifndef MBEDTLS_CONFIG_H_
#define MBEDTLS_CONFIG_H_

/* FreeRTOS include. */
#include "FreeRTOS.h"
#if 0
/* Generate errors if deprecated functions are used. */
#define MBEDTLS_DEPRECATED_REMOVED

/* Place AES tables in ROM. */
#define MBEDTLS_AES_ROM_TABLES

/* Enable the following cipher modes. */
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CIPHER_MODE_CFB
#define MBEDTLS_CIPHER_MODE_CTR

/* Enable the following cipher padding modes. */
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_CIPHER_PADDING_ONE_AND_ZEROS
#define MBEDTLS_CIPHER_PADDING_ZEROS_AND_LEN
#define MBEDTLS_CIPHER_PADDING_ZEROS

/* Cipher suite configuration. */
#define MBEDTLS_REMOVE_ARC4_CIPHERSUITES
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECP_NIST_OPTIM
#define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED

/* Enable all SSL alert messages. */
#define MBEDTLS_SSL_ALL_ALERT_MESSAGES

/* Enable the following SSL features. */
//#define MBEDTLS_SSL_ENCRYPT_THEN_MAC @kazuki.mochizuki
//#define MBEDTLS_SSL_EXTENDED_MASTER_SECRET @kazuki.mochizuki
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH
#define MBEDTLS_SSL_KEEP_PEER_CERTIFICATE // @kazuki.mochizuki
// #define MBEDTLS_SSL_PROTO_TLS1_2 // @kazuki.mochizuki
#define MBEDTLS_SSL_PROTO_TLS1_3 // @kazuki.mochizuki
#define MBEDTLS_SSL_ALPN
#define MBEDTLS_SSL_SERVER_NAME_INDICATION

/* Check certificate key usage. */
#define MBEDTLS_X509_CHECK_KEY_USAGE
#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
#define MBEDTLS_X509_CREATE_C
#define MBEDTLS_X509_CSR_WRITE_C

/* Disable platform entropy functions. */
#define MBEDTLS_NO_PLATFORM_ENTROPY

/* Enable the following mbed TLS features. */
#define MBEDTLS_AES_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_BASE64_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ECP_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_ERROR_C
#define MBEDTLS_ENTROPY_HARDWARE_ALT

#define MBEDTLS_GCM_C
#define MBEDTLS_HKDF_C // @kazuki.mochizuki
#define MBEDTLS_MD_C
#define MBEDTLS_OID_C
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PK_WRITE_C
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_PSA_CRYPTO_C // @kazuki.mochizuki
#define MBEDTLS_RSA_C
#define MBEDTLS_SHA1_C
#define MBEDTLS_SHA224_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA384_C // @kazuki.mochizuki
#define MBEDTLS_SHA512_C // @kazuki.mochizuki
#define MBEDTLS_SSL_CLI_C
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_THREADING_ALT
#define MBEDTLS_THREADING_C
#define MBEDTLS_X509_USE_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_CMAC_C
#define MBEDTLS_PEM_WRITE_C


/* Set the memory allocation functions on FreeRTOS. */
void * mbedtls_platform_calloc( size_t nmemb,
                                size_t size );
void mbedtls_platform_free( void * ptr );
#define MBEDTLS_PLATFORM_MEMORY
#define MBEDTLS_PLATFORM_CALLOC_MACRO    mbedtls_platform_calloc
#define MBEDTLS_PLATFORM_FREE_MACRO      mbedtls_platform_free

/* The network send and receive functions on FreeRTOS. */
int mbedtls_platform_send( void * ctx,
                           const unsigned char * buf,
                           size_t len );
int mbedtls_platform_recv( void * ctx,
                           unsigned char * buf,
                           size_t len );

/* These two macro used by mbedtls_ssl_set_bio in using_mbedtls network
 * transport layer. */
#define MBEDTLS_SSL_SEND mbedtls_platform_send
#define MBEDTLS_SSL_RECV mbedtls_platform_recv

/* The entropy poll function. */
int mbedtls_platform_entropy_poll( void * data,
                                   unsigned char * output,
                                   size_t len,
                                   size_t * olen );
#endif

#define MBEDTLS_HAVE_ASM
#define MBEDTLS_DEPRECATED_REMOVED
#define MBEDTLS_ENTROPY_HARDWARE_ALT
#define MBEDTLS_AES_ROM_TABLES
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CIPHER_MODE_CFB
#define MBEDTLS_CIPHER_MODE_CTR
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_CIPHER_PADDING_ONE_AND_ZEROS
#define MBEDTLS_CIPHER_PADDING_ZEROS_AND_LEN
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECP_NIST_OPTIM
#define MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_SSL_ALL_ALERT_MESSAGES
#define MBEDTLS_SSL_KEEP_PEER_CERTIFICATE // @kazuki.mochizuki
#define MBEDTLS_SSL_RENEGOTIATION
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH
#define MBEDTLS_SSL_PROTO_TLS1_3 // @kazuki.mochizuki
#define MBEDTLS_SSL_SERVER_NAME_INDICATION
#define MBEDTLS_THREADING_ALT
#define MBEDTLS_AES_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_BASE64_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_CMAC_C
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ECP_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_GCM_C
#define MBEDTLS_HKDF_C // @kazuki.mochizuki
#define MBEDTLS_MD_C
#define MBEDTLS_OID_C
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_PEM_WRITE_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PK_WRITE_C
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_PSA_CRYPTO_C // @kazuki.mochizuki
#define MBEDTLS_SHA1_C
#define MBEDTLS_SHA224_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA384_C // @kazuki.mochizuki
#define MBEDTLS_SHA512_C // @kazuki.mochizuki
#define MBEDTLS_SSL_CLI_C
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_THREADING_C
#define MBEDTLS_X509_USE_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_CREATE_C
#define MBEDTLS_X509_CSR_WRITE_C

/* frtos_config/mbedtls_config.h */

#define MBEDTLS_REMOVE_ARC4_CIPHERSUITES
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED // @kazuki.mochizuki
#define MBEDTLS_GENPRIME // @kazuki.mochizuki

#define MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE // @kazuki.mochizuki
#define MBEDTLS_SSL_ALPN
//#undef MBEDTLS_SSL_ALPN
#define MBEDTLS_X509_CHECK_KEY_USAGE
#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
#define MBEDTLS_ENTROPY_FORCE_SHA256 // @kazuki.mochizuki
#define MBEDTLS_PK_RSA_ALT_SUPPORT // @kazuki.mochiuzki
#define MBEDTLS_ERROR_C
#define MBEDTLS_RSA_C // @kazuki.mochizuki
#define MBEDTLS_USE_PSA_CRYPTO // @kazuki.mochizuki
#define MBEDTLS_SSL_DEBUG_ALL // @kazuki.mochizuki
#define MBEDTLS_DEBUG_C // @kazuki.mochizuki
#define MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED // @kazuki.mochizuki
#define MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED // @kazuki.mochizuki
#define MBEDTLS_DHM_C // @kazuki.mochizuki

void * mbedtls_platform_calloc( size_t nmemb,
                                size_t size );

void mbedtls_platform_free( void * ptr );

#define MBEDTLS_HAVE_ASM // @kazuki.mochizuki
#define MBEDTLS_PLATFORM_MEMORY
#define MBEDTLS_PLATFORM_CALLOC_MACRO    mbedtls_platform_calloc
#define MBEDTLS_PLATFORM_FREE_MACRO      mbedtls_platform_free

/* The network send and receive functions on FreeRTOS. */
int mbedtls_platform_send( void * ctx,
                           const unsigned char * buf,
                           size_t len );

int mbedtls_platform_recv( void * ctx,
                           unsigned char * buf,
                           size_t len );

int mbedtls_platform_entropy_poll( void * data,
                                   unsigned char * output,
                                   size_t len,
                                   size_t * olen );


#define MBEDTLS_SSL_SEND mbedtls_platform_send
#define MBEDTLS_SSL_RECV mbedtls_platform_recv


/* Soren - ensure that all TLS 1.2 options are disabled */
#define MBEDTLS_SSL_PROTO_TLS1_3
#define MBEDTLS_SSL_TLS1_3_COMPATIBILITY_MODE

#undef MBEDTLS_SHA1_C
#undef MBEDTLS_SSL_ENCRYPT_THEN_MAC
#undef MBEDTLS_SSL_EXTENDED_MASTER_SECRET
#undef MBEDTLS_SSL_PROTO_TLS1_2
#undef MBEDTLS_SSL_PROTO_DTLS
#undef MBEDTLS_SSL_DTLS_ANTI_REPLAY
#undef MBEDTLS_SSL_DTLS_HELLO_VERIFY
#undef MBEDTLS_SSL_DTLS_CLIENT_PORT_REUSE

#ifdef MBEDTLS_SSL_PROTO_TLS1_2
    #error Should not be using TLS1_2
#endif
#include "mbedtls/check_config.h"


#endif /* ifndef MBEDTLS_CONFIG_H_ */
