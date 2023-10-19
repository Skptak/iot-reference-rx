/*
 * FreeRTOS V202111.00
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

#ifndef DEMO_CONFIG_H
#define DEMO_CONFIG_H

/* FreeRTOS include. */
#include "FreeRTOS.h"
#include "aws_clientcredential.h"
#include "aws_clientcredential_keys.h"
#include "iot_default_root_certificates.h"

/* Soren - I put my certs and relevant info in this file */
#include "sorenCerts.h"
/**************************************************/
/******* DO NOT CHANGE the following order ********/
/**************************************************/

/* Include logging header files and define logging macros in the following order:
 * 1. Include the header file "logging_levels.h".
 * 2. Define the LIBRARY_LOG_NAME and LIBRARY_LOG_LEVEL macros depending on
 * the logging configuration for DEMO.
 * 3. Include the header file "logging_stack.h", if logging is enabled for DEMO.
 */

#include "logging_levels.h"

/* Logging configuration for the Demo. */
#ifndef LIBRARY_LOG_NAME
#define LIBRARY_LOG_NAME    "MQTTDemo"
#endif

#ifndef LIBRARY_LOG_LEVEL
#define LIBRARY_LOG_LEVEL    LOG_DEBUG
#endif

#include "iot_logging_task.h"

//#define democonfigCLIENT_CERTIFICATE_PEM    keyCLIENT_CERTIFICATE_PEM
//#define democonfigCLIENT_PRIVATE_KEY_PEM    keyCLIENT_PRIVATE_KEY_PEM
//#define democonfigCLIENT_USERNAME			  keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM

/* Select only one demo task to run. */
//#define SIMPLE_PUBSUB_DEMO
#define PKCS_MUTUAL_AUTH_DEMO  // Soren - Using the PKCS Mutual Auth Demo
//#define OTA_OVER_MQTT_DEMO
//#define FLEET_PROVISIONING_DEMO

/* Soren - The project won't build without this, regardless of demo selected
 */
#include "ota_demo_config.h"

#define AmazonRootCA3PEM \
"-----BEGIN CERTIFICATE-----\n" \
"MIIBtjCCAVugAwIBAgITBmyf1XSXNmY/Owua2eiedgPySjAKBggqhkjOPQQDAjA5\n" \
"MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24g\n" \
"Um9vdCBDQSAzMB4XDTE1MDUyNjAwMDAwMFoXDTQwMDUyNjAwMDAwMFowOTELMAkG\n" \
"A1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJvb3Qg\n" \
"Q0EgMzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABCmXp8ZBf8ANm+gBG1bG8lKl\n" \
"ui2yEujSLtf6ycXYqm0fc4E7O5hrOXwzpcVOho6AF2hiRVd9RFgdszflZwjrZt6j\n" \
"QjBAMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgGGMB0GA1UdDgQWBBSr\n" \
"ttvXBp43rDCGB5Fwx5zEGbF4wDAKBggqhkjOPQQDAgNJADBGAiEA4IWSoxe3jfkr\n" \
"BqWTrBqYaGFy+uGh0PsceGCmQ5nFuMQCIQCcAu/xlJyzlvnrxir4tiz+OpAUFteM\n" \
"YyRIHN8wfdVoOw==\n" \
"-----END CERTIFICATE-----\n"

#define AmazonRootCA1PEM \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n"

#if defined(FLEET_PROVISIONING_DEMO)
    #define democonfigROOT_CA_PEM             "...insert here..."
#else
    #define democonfigROOT_CA_PEM               AmazonRootCA1PEM
#endif

/**
 * @brief Path of the file containing the provisioning claim certificate. This
 * certificate is used to connect to AWS IoT Core and use Fleet Provisioning
 * APIs to provision the client device. This is used for the "Provisioning by
 * Claim" provisioning workflow.
 *
 * For information about provisioning by claim, see the following AWS documentation:
 * https://docs.aws.amazon.com/iot/latest/developerguide/provision-wo-cert.html#claim-based
 *
 * @note This certificate should be PEM-encoded. The certificate should be
 * registered on AWS IoT Core beforehand. It should have an AWS IoT policy to
 * allow it to access only the Fleet Provisioning APIs. An example policy for
 * the claim certificates for this demo is available in the
 * example_claim_policy.json file in the demo directory. In the example,
 * replace <aws-region> with your AWS region, <aws-account-id> with your
 * account ID, and <template-name> with the name of your provisioning template.
 *
 */
// Soren - Set this to your proper cert
#define democonfigCLAIM_CERT_PEM sorenClientCertPem

/**
 * @brief Path of the file containing the provisioning claim private key. This
 * key corresponds to the provisioning claim certificate and is used to
 * authenticate with AWS IoT for provisioning by claim.
 *
 * For information about provisioning by claim, see the following AWS documentation:
 * https://docs.aws.amazon.com/iot/latest/developerguide/provision-wo-cert.html#claim-based
 *
 * @note This private key should be PEM-encoded.
 *
 */
// Soren - Set this to your proper key
#define democonfigCLAIM_PRIVATE_KEY_PEM sorenPrivateRSAKey

/**
 * @brief An option to disable Server Name Indication.
 *
 * @note When using a local Mosquitto server setup, SNI needs to be disabled
 * for an MQTT broker that only has an IP address but no hostname. However,
 * SNI should be enabled whenever possible.
 */
#define democonfigDISABLE_SNI                ( pdFALSE )

/**
 * @brief Configuration that indicates if the demo connection is made to the AWS IoT Core MQTT broker.
 *
 * If username/password based authentication is used, the demo will use appropriate TLS ALPN and
 * SNI configurations as required for the Custom Authentication feature of AWS IoT.
 * For more information, refer to the following documentation:
 * https://docs.aws.amazon.com/iot/latest/developerguide/custom-auth.html#custom-auth-mqtt
 *
 * #define democonfigUSE_AWS_IOT_CORE_BROKER    ( 1 )
 */
#define democonfigUSE_AWS_IOT_CORE_BROKER    ( 1 )

/**
 * @brief The unique ID used by the demo to differentiate instances.
 *
 *!!! Please note a #defined constant is used for convenience of demonstration
 *!!! only.  Production devices can use something unique to the device that can
 *!!! be read by software, such as a production serial number, instead of a
 *!!! hard coded constant.
 */
#define democonfigFP_DEMO_ID    "FPDemoID"__TIME__

/**
 * @brief The MQTT client identifier used in this example.  Each client identifier
 * must be unique so edit as required to ensure no two clients connecting to the
 * same broker use the same client identifier.
 *
 * @note Appending __TIME__ to the client id string will reduce the possibility of a
 * client id collision in the broker. Note that the appended time is the compilation
 * time. This client id can cause collision, if more than one instance of the same
 * binary is used at the same time to connect to the broker.
 */
#ifndef democonfigCLIENT_IDENTIFIER
    #if defined(FLEET_PROVISIONING_DEMO)
        #define democonfigCLIENT_IDENTIFIER    "client"democonfigFP_DEMO_ID
    #else
        #define democonfigCLIENT_IDENTIFIER    sorenClient_Identifier
    #endif
#endif

/**
 * @brief Details of the MQTT broker to connect to.
 *
 * This is the Claim's Rest API Endpoint for AWS IoT.
 *
 * @note Your AWS IoT Core endpoint can be found in the AWS IoT console under
 * Settings/Custom Endpoint, or using the describe-endpoint API.
 *
 */
#define democonfigMQTT_BROKER_ENDPOINT     clientcredentialMQTT_BROKER_ENDPOINT

/**
 * @brief AWS IoT MQTT broker port number.
 *
 * In general, port 8883 is for secured MQTT connections.
 *
 * @note Port 443 requires use of the ALPN TLS extension with the ALPN protocol
 * name. When using port 8883, ALPN is not required.
 */
#define democonfigMQTT_BROKER_PORT    ( clientcredentialMQTT_BROKER_PORT )

/**
 * @brief Name of the provisioning template to use for the RegisterThing
 * portion of the Fleet Provisioning workflow.
 *
 * For information about provisioning templates, see the following AWS documentation:
 * https://docs.aws.amazon.com/iot/latest/developerguide/provision-template.html#fleet-provision-template
 *
 * The example template used for this demo is available in the
 * example_demo_template.json file in the DemoSetup directory. In the example,
 * replace <provisioned-thing-policy> with the policy provisioned devices
 * should have.  The demo template uses Fn::Join to construct the Thing name by
 * concatenating fp_demo_ and the serial number sent by the demo.
 *
 * @note The provisioning template MUST be created in AWS IoT before running the
 * demo.
 *
 * @note If you followed the manual setup steps on https://freertos.org/iot-fleet-provisioning/demo.html,
 * the provisioning template name is "FleetProvisioningDemoTemplate".
 * However, if you used CloudFormation to set up the demo, the template name is "CF_FleetProvisioningDemoTemplate"
 */
 #define democonfigPROVISIONING_TEMPLATE_NAME    sorenProvisioningTemplateName

/**
 * @brief Subject name to use when creating the certificate signing request (CSR)
 * for provisioning the demo client with using the Fleet Provisioning
 * CreateCertificateFromCsr APIs.
 *
 * This is passed to MbedTLS; see https://tls.mbed.org/api/x509__csr_8h.html#a954eae166b125cea2115b7db8c896e90
 */
#ifndef democonfigCSR_SUBJECT_NAME
    #define democonfigCSR_SUBJECT_NAME    "CN="democonfigFP_DEMO_ID
#endif

/**
 * @brief Set the stack size of the main demo task.
 *
 * In the Windows port, this stack only holds a structure. The actual
 * stack is created by an operating system thread.
 */
#define democonfigDEMO_STACKSIZE        configMINIMAL_STACK_SIZE * 8

/**
 * @brief Set the stack size of the main demo task.
 *
 * In the Windows port, this stack only holds a structure. The actual
 * stack is created by an operating system thread.
 */
#define democonfigDEMO_TASK_PRIORITY    ( tskIDLE_PRIORITY + 1 )

#define democonfigNETWORK_BUFFER_SIZE    ( configMINIMAL_STACK_SIZE  )

#include "core_mqtt.h" /* Include coreMQTT header for MQTT_LIBRARY_VERSION macro. */
#define democonfigMQTT_LIB    "core-mqtt@"MQTT_LIBRARY_VERSION

/**
 * @brief ALPN (Application-Layer Protocol Negotiation) protocol name for AWS IoT MQTT.
 *
 * This will be used if democonfigMQTT_BROKER_PORT is configured as 443 for the AWS IoT MQTT broker.
 * Please see more details about the ALPN protocol for AWS IoT MQTT endpoint
 * in the link below.
 * https://aws.amazon.com/blogs/iot/mqtt-with-tls-client-authentication-on-port-443-why-it-is-useful-and-how-it-works/
 */
#define AWS_IOT_MQTT_ALPN           "x-amzn-mqtt-ca"

/**
 * @brief This is the ALPN (Application-Layer Protocol Negotiation) string
 * required by AWS IoT for password-based authentication using TCP port 443.
 */
#define AWS_IOT_CUSTOM_AUTH_ALPN    "mqtt"
/**
 * @brief The MQTT metrics string expected by AWS IoT.
 */
/**
 * @brief The name of the operating system that the application is running on.
 * The current value is given as an example. Please update for your specific
 * operating system.
 */
#define democonfigOS_NAME       "FreeRTOS"

/**
 * @brief The version of the operating system that the application is running
 * on. The current value is given as an example. Please update for your specific
 * operating system version.
 */
#define democonfigOS_VERSION    "V10.5.1"

/**
 * @brief The name of the hardware platform the application is running on. The
 * current value is given as an example. Please update for your specific
 * hardware platform.
 */
#define democonfigHARDWARE_PLATFORM_NAME    "CK-RX65N"

/**
 * @brief The MQTT metrics string expected by AWS IoT.
 */
/* Soren - Use the metric string with the platform name */
#define AWS_IOT_METRICS_STRING                                 \
    "?SDK=" democonfigOS_NAME "&Version=" democonfigOS_VERSION \
    "&Platform=" democonfigHARDWARE_PLATFORM_NAME "&MQTTLib=" democonfigMQTT_LIB

/**
 * @brief The length of the MQTT metrics string expected by AWS IoT.
 */
#define AWS_IOT_METRICS_STRING_LENGTH    ( ( uint16_t ) ( sizeof( AWS_IOT_METRICS_STRING ) - 1 ) )


#ifdef democonfigCLIENT_USERNAME

/**
 * @brief Append the username with the metrics string if #democonfigCLIENT_USERNAME is defined.
 *
 * This is to support both metrics reporting and username/password based client
 * authentication by AWS IoT.
 */
#define CLIENT_USERNAME_WITH_METRICS    democonfigCLIENT_USERNAME AWS_IOT_METRICS_STRING
#endif

//#define democonfigUSE_TLS                   0
#endif /* DEMO_CONFIG_H */
