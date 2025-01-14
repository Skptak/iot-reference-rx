/*
FreeRTOS
Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
Modifications Copyright (C) 2023 Renesas Electronics Corporation. or its affiliates.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 http://aws.amazon.com/freertos
 http://www.FreeRTOS.org
*/

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Logging includes. */
#include "iot_logging_task.h"

/* Key provisioning includes. */
#include "aws_dev_mode_key_provisioning.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"

/* Demo includes */
#include "aws_clientcredential.h"
#include "demo_config.h"
#include "store.h"
#include "mqtt_agent_task.h"

extern int32_t littlFs_init(void);
bool ApplicationCounter(uint32_t xWaitTime);
signed char vISR_Routine( void );
extern KeyValueStore_t gKeyValueStore;


#ifndef UNSIGNED_SHORT_RANDOM_NUMBER_MASK
    #define UNSIGNED_SHORT_RANDOM_NUMBER_MASK         (0xFFFFUL)
#endif
/* The MAC address array is not declared const as the MAC address will
normally be read from an EEPROM and not hard coded (in real deployed
applications).*/
static uint8_t ucMACAddress[ 6 ] =
{
    configMAC_ADDR0,
    configMAC_ADDR1,
    configMAC_ADDR2,
    configMAC_ADDR3,
    configMAC_ADDR4,
    configMAC_ADDR5
}; //XXX

/* Define the network addressing.  These parameters will be used if either
ipconfigUDE_DHCP is 0 or if ipconfigUSE_DHCP is 1 but DHCP auto configuration
failed. */
static const uint8_t ucIPAddress[ 4 ] =
{
    configIP_ADDR0,
    configIP_ADDR1,
    configIP_ADDR2,
    configIP_ADDR3
};
static const uint8_t ucNetMask[ 4 ] =
{
    configNET_MASK0,
    configNET_MASK1,
    configNET_MASK2,
    configNET_MASK3
};
static const uint8_t ucGatewayAddress[ 4 ] =
{
    configGATEWAY_ADDR0,
    configGATEWAY_ADDR1,
    configGATEWAY_ADDR2,
    configGATEWAY_ADDR3
};

/* The following is the address of an OpenDNS server. */
static const uint8_t ucDNSServerAddress[ 4 ] =
{
    configDNS_SERVER_ADDR0,
    configDNS_SERVER_ADDR1,
    configDNS_SERVER_ADDR2,
    configDNS_SERVER_ADDR3
};

/**
 * @brief Application task startup hook.
 */
void vApplicationDaemonTaskStartupHook( void );

/**
 * @brief Initializes the board.
 */
void prvMiscInitialization( void );

extern void UserInitialization(void);
extern void CLI_Support_Settings(void);
extern void vUARTCommandConsoleStart( uint16_t usStackSize, UBaseType_t uxPriority );
extern void vRegisterSampleCLICommands( void );

/*-----------------------------------------------------------*/

/**
 * @brief The application entry point from a power on reset is PowerON_Reset_PC()
 * in resetprg.c.
 */
void main_task( void )
{
	int32_t xResults, Time2Wait = 1000;
	int32_t retVal = 0;
	BaseType_t xStatus = pdFALSE;

	extern TaskHandle_t xCLIHandle;

	prvMiscInitialization();
	UserInitialization();

	/* Register the standard CLI commands. */
	vRegisterSampleCLICommands();
	vUARTCommandConsoleStart( demoUART_COMMAND_CONSOLE_STACK_SIZE,
                                 demoUART_COMMAND_CONSOLE_TASK_PRIORITY );

	xResults = littlFs_init();

	xMQTTAgentInit();

	if (xResults == LFS_ERR_OK)
	{
		xResults = vprvCacheInit();
	}
    retVal = xprvWriteCacheEntry( 9,"thingname", sizeof(sorenAWSIoTThingName),           sorenAWSIoTThingName );
    configASSERT( retVal == KVS_CORE_THING_NAME );

    retVal = xprvWriteCacheEntry( 8,"endpoint",  sizeof(sorenAWSIoTEndpoint),            sorenAWSIoTEndpoint );
    configASSERT( retVal == KVS_CORE_MQTT_ENDPOINT );

    retVal = xprvWriteCacheEntry( 4,"cert",      sizeof(sorenClientCertPem),             sorenClientCertPem );
    configASSERT( retVal == KVS_DEVICE_CERT_ID );

    retVal = xprvWriteCacheEntry( 3,"key",       sizeof(sorenPrivateRSAKey),             sorenPrivateRSAKey );
    configASSERT( retVal == KVS_DEVICE_PRIVKEY_ID );

    //retVal = xprvWriteCacheEntry( 3,"pub",       sizeof(sorenPublicRSAKey),              sorenPublicRSAKey );
    //configASSERT( retVal == KVS_DEVICE_PUBKEY_ID );

    /* retVal =  xprvWriteCacheEntry( 6,"rootca",    sizeof(AmazonRootCA3PEM) - 1,       AmazonRootCA3PEM ); */
    retVal = xprvWriteCacheEntry( 6,"rootca",    sizeof(AmazonRootCA1PEM),               AmazonRootCA1PEM );
    configASSERT( retVal == KVS_ROOT_CA_ID );

    retVal = xprvWriteCacheEntry( 8,"template",  sizeof(sorenProvisioningTemplateName),  sorenProvisioningTemplateName );
    configASSERT( retVal == KVS_TEMPLATE_NAME );

    retVal = xprvWriteCacheEntry( 9,"claimcert", sizeof(sorenClientCertPem) ,            sorenClientCertPem );
    configASSERT( retVal == KVS_CLAIM_CERT_ID );

    retVal = xprvWriteCacheEntry( 8,"claimkey",  sizeof(sorenPrivateRSAKey) ,            sorenPrivateRSAKey );
    configASSERT( retVal == KVS_CLAIM_PRIVKEY_ID );

    xStatus = KVStore_xCommitChanges();
    if(xStatus != pdPASS){
        //LogError( ( "Got a value of %d from KVStore_xCommitChanges ", xStatus ) );
        xStatus = pdPASS;
        //configASSERT( xStatus == pdTRUE );
    }
	if(ApplicationCounter(Time2Wait))
	{
		/* Remove CLI task before going to demo. */
		/* CLI and Log tasks use common resources but are not exclusively controlled. */
		/* For this reason, the CLI task must be deleted before executing the Demo. */
		vTaskDelete(xCLIHandle);
		/* Initialise the RTOS's TCP/IP stack.  The tasks that use the network
			are created in the vApplicationIPNetworkEventHook() hook function
			below.  The hook function is called when the network connects. */

		FreeRTOS_IPInit( ucIPAddress,
						 ucNetMask,
						 ucGatewayAddress,
						 ucDNSServerAddress,
						 ucMACAddress );

		/* We should wait for the network to be up before we run any demos. */
		while( FreeRTOS_IsNetworkUp() == pdFALSE )
		{
			vTaskDelay(300);
		}

		FreeRTOS_printf( ( "Initialise the RTOS's TCP/IP stack\n" ) );

		FreeRTOS_printf( ( "---------STARTING DEMO---------\r\n" ) );

        #if (ENABLE_FLEET_PROVISIONING_DEMO == 1)
           vStartFleetProvisioningDemo();
        #else
           xSetMQTTAgentState( MQTT_AGENT_STATE_INITIALIZED );
        #endif

        vStartMQTTAgent (demoMQTT_AGENT_TASK_STACK_SIZE,
                         demoMQTT_AGENT_TASK_PRIORITY);

        vStartSimplePubSubDemo ();

        #if (ENABLE_OTA_UPDATE_DEMO == 1)
            vStartOtaDemo();
        #endif
	}

	while( 1 )
	{
		vTaskSuspend( NULL );
	}
}
/*-----------------------------------------------------------*/

void prvMiscInitialization( void )
{
    /* Initialize UART for serial terminal. */
	CLI_Support_Settings();

    /* Start logging task. */
    xLoggingTaskInitialize( configLOGGING_TASK_STACK_SIZE,
                            configLOGGING_TASK_PRIORITY,
                            configLOGGING_MESSAGE_QUEUE_LENGTH );

}
/*-----------------------------------------------------------*/

void vApplicationDaemonTaskStartupHook( void )
{

}

/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
    /* If the buffers to be provided to the Idle task are declared inside this
     * function then they must be declared static - otherwise they will be allocated on
     * the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle
     * task's state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/**
 * @brief This is to provide the memory that is used by the RTOS daemon/time task.
 *
 * If configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetTimerTaskMemory() to provide the memory that is
 * used by the RTOS daemon/time task.
 */
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
    /* If the buffers to be provided to the Timer task are declared inside this
     * function then they must be declared static - otherwise they will be allocated on
     * the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle
     * task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
/*-----------------------------------------------------------*/

#ifndef iotconfigUSE_PORT_SPECIFIC_HOOKS

/**
 * @brief Warn user if pvPortMalloc fails.
 *
 * Called if a call to pvPortMalloc() fails because there is insufficient
 * free memory available in the FreeRTOS heap.  pvPortMalloc() is called
 * internally by FreeRTOS API functions that create tasks, queues, software
 * timers, and semaphores.  The size of the FreeRTOS heap is set by the
 * configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h.
 *
 */
    void vApplicationMallocFailedHook()
    {
        configPRINT_STRING( ( "ERROR: Malloc failed to allocate memory\r\n" ) );
        taskDISABLE_INTERRUPTS();

        /* Loop forever */
        for( ; ; )
        {
        }
    }

/*-----------------------------------------------------------*/

/**
 * @brief Loop forever if stack overflow is detected.
 *
 * If configCHECK_FOR_STACK_OVERFLOW is set to 1,
 * this hook provides a location for applications to
 * define a response to a stack overflow.
 *
 * Use this hook to help identify that a stack overflow
 * has occurred.
 *
 */
    void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                        char * pcTaskName )
    {
        configPRINT_STRING( ( "ERROR: stack overflow\r\n" ) );
        portDISABLE_INTERRUPTS();

        /* Unused Parameters */
        ( void ) xTask;
        ( void ) pcTaskName;

        /* Loop forever */
        for( ; ; )
        {
        }
    }
#endif /* iotconfigUSE_PORT_SPECIFIC_HOOKS */
/*-----------------------------------------------------------*/

#if ( ipconfigUSE_LLMNR != 0 ) || ( ipconfigUSE_NBNS != 0 ) || ( ipconfigDHCP_REGISTER_HOSTNAME == 1 )
    /* This function will be called during the DHCP: the machine will be registered
     * with an IP address plus this name.
     * Note: Please make sure vprvCacheInit() is called before this function, because
	 * it retrieves thingname value from KeyValue table. */
    const char * pcApplicationHostnameHook( void )
    {
        /* This function will be called during the DHCP: the machine will be registered
         * with an IP address plus this name. */
        if (gKeyValueStore.table[KVS_CORE_THING_NAME].valueLength > 0)
        {
            return gKeyValueStore.table[KVS_CORE_THING_NAME].value;
        }
        else
        {
            return clientcredentialIOT_THING_NAME;
        }
    }
#endif

bool ApplicationCounter(uint32_t xWaitTime)
{
    TickType_t xCurrent;
    bool DEMO_TEST = pdTRUE;
    const TickType_t xPrintFrequency = pdMS_TO_TICKS( xWaitTime );
    xCurrent = xTaskGetTickCount();
    signed char cRxChar;
    while( xCurrent < xPrintFrequency )
    {
    	vTaskDelay(1);
    	xCurrent = xTaskGetTickCount();

    	cRxChar = vISR_Routine();
    	if ((cRxChar != 0) )
    	{

    		DEMO_TEST = pdFALSE;
    		break;
    	}
    }
    return DEMO_TEST;
}

signed char vISR_Routine( void )
{
	BaseType_t xTaskWokenByReceive = pdFALSE;
	extern signed char cRxedChar;
    return cRxedChar;
}
