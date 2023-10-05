This includes demonstration tasks for the following AWS services:
* [AWS IoT Device Shadow](https://docs.aws.amazon.com/iot/latest/developerguide/iot-device-shadows.html)
* [AWS IoT Device Defender](https://docs.aws.amazon.com/iot/latest/developerguide/device-defender.html)
* [AWS IoT Jobs](https://docs.aws.amazon.com/iot/latest/developerguide/iot-jobs.html)
* [MQTT File Delivery](https://docs.aws.amazon.com/iot/latest/developerguide/mqtt-based-file-delivery.html)
* [AWS IoT OTA Update](https://docs.aws.amazon.com/freertos/latest/userguide/freertos-ota-dev.html)

The demo projects both connect to AWS IoT core via the included Ethernet or Cellular and use the [CoreMQTT-Agent](https://github.com/FreeRTOS/coreMQTT-Agent) library to share a single MQTT connection among multiple tasks. These tasks publish environemnt and motion sensor data from a subset of the sensor available on the development board, and demonstrate use of the AWS IoT Device Shadow and Device Defender services.

## AWS IoT Core Demo Tasks
* MQTT Agent
* IoT Defender
* OTA Update
* Environment Sensor Publishing

## Cloning the Repository
For long path name:
```
git config --global core.longpaths true
```
To clone using HTTPS:
```
git clone https://github.com/renesas/iot-reference-rx.git --recurse-submodules
```
Using SSH:
```
git clone git@github.com:renesas/iot-reference-rx --recurse-submodules
```
If you have downloaded the repo without using the `--recurse-submodules` argument, you should run:
```
git submodule update --init --recursive
```

## 1 Prerequisites

### 1.1 Hardware Requirements

* [CK-RX65N](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/rx-32-bit-performance-efficiency-mcus/ck-rx65n-cloud-kit-based-rx65n-mcu-group)
* [Cellular RYZ014A](https://www.renesas.com/us/en/products/wireless-connectivity/cellular-iot-modules/ryz014a-lte-cat-m1-cellular-iot-module)


### 1.2 Software Requirements
* A Windows development environment as the [CC-RX toolchain](https://www.renesas.com/us/en/software-tool/cc-compiler-package-rx-family)
used for this project
only is available for windows.
* e2studio 2022-07. To download, visit the
     [e2studio page](https://www.renesas.com/us/en/software-tool/e-studio#download).
     (A user account is required to download.)

* [OpenSSL for Windows](https://www.openssl.org/) to create the OTA signing
    key and certificate. If you have git installed on your machine, you can also use the openssl.exe
    that comes with the git installation.

* A serial terminal application, such as [Tera Term](https://ttssh2.osdn.jp/index.html.en).

## 2 Hardware and Software Setup
1. Plug in the Cellular RYZ014A to the PMOD1 on the CK-RX65N board for using cellular
2. Plug in the Ethernet cable to the CK-RX65N board for using ethernet


## 3 Porting project 
### 3.1 Structure skeleton

### 3.2 Build mbed network transport implementation
#### 3.2.1 Using Ethernet
Using [FreeRTOS-Plus-TCP] layer to porting ethernet

* Copy [tcp_sockets_wrapper/ports/freertos_plus_tcp](https://github.com/FreeRTOS/FreeRTOS/tree/202212.01/FreeRTOS-Plus/Source/Application-Protocols/network_transport/tcp_sockets_wrapper/ports/freertos_plus_tcp) to Middleware/abstractions/secure_sockets
* Copy [mbedtls_pk_pkcs11.c and mbedtls_pkcs11.h files](https://github.com/FreeRTOS/FreeRTOS/tree/202212.01/FreeRTOS-Plus/Source/Application-Protocols/network_transport) to Middleware/mbedtls_utils
* Copy [transport_mbedtls_pkcs11 files](https://github.com/FreeRTOS/FreeRTOS/blob/202212.01/FreeRTOS-Plus/Source/Application-Protocols/network_transport) to Middleware/mbedtls_utils
*Note:Using [mbedtls_bio_tcp_sockets_wrapper.c](https://github.com/FreeRTOS/FreeRTOS/blob/202212.01/FreeRTOS-Plus/Source/Application-Protocols/network_transport/mbedtls_bio_tcp_sockets_wrapper.c)*

#### 3.2.1 Using Cellular
Using .h [FreeRTOS-Plus-TCP] layer to port

* Copy and modify [tcp_sockets_wrapper/ports/cellular](https://github.com/FreeRTOS/FreeRTOS/blob/202212.01/FreeRTOS-Plus/Source/Application-Protocols/network_transport/tcp_sockets_wrapper/ports/cellular/tcp_sockets_wrapper.c) to Middleware/abstractions/secure_sockets
* Copy [mbedtls_pk_pkcs11.c and mbedtls_pkcs11.h files](https://github.com/FreeRTOS/FreeRTOS/tree/202212.01/FreeRTOS-Plus/Source/Application-Protocols/network_transport) to Middleware/mbedtls_utils
* Copy [transport_mbedtls_pkcs11 files](https://github.com/FreeRTOS/FreeRTOS/blob/202212.01/FreeRTOS-Plus/Source/Application-Protocols/network_transport) to Middleware/mbedtls_utils to Middleware/mbedtls_utils. 
*Note:Using mbedtls_bio_freertos_cellular.c*

| RX MCU and Board | Old Structure|New Structure |
| :----- | :---: |:---: |
| SecureSocketsTransport | SecureSocketsTransport_Connect<br>SecureSocketsTransport_Disconnect<br>SecureSocketsTransport_Recv<br>SecureSocketsTransport_Send|TLS_FreeRTOS_Connect<br>TLS_FreeRTOS_Disconnect<br>TLS_FreeRTOS_recv<br>TLS_FreeRTOS_send|
| Sockets | SOCKETS_Socket<br>SOCKETS_Connect<br>SOCKETS_Recv<br>SOCKETS_Send<br>SOCKETS_Close<br>SOCKETS_Shutdown<br>SOCKETS_Bind|Sockets_Connect<br>Sockets_Disconnect<br>Sockets_Send<br>Sockets_Recv|
| TLS layer | TLS_Init<br>TLS_Connect<br>TLS_Send<br>TLS_Recv<br>TLS_Cleanup|initMbedtls<br>tlsSetup<br>|


#####  Modify [socket_wrapper/cellular](Middleware/Application-Protocols/network_transport/sockets_wrapper/ports/cellular_ryz014a/sockets_wrapper.c): 
* Because sockets_wrapper.c is using [FreeRTOS-Plus-TCP] layer APIs, we need to change to use RYZ014A cellular API into each of function belows : Sockets_Connect, Sockets_Recv, Sockets_Send, Sockets_Disconnect


## 4. Select a Project to Run
This repository has five different distinct projects.

1. [aws_cellular_ck_rx65n](Projects/aws_cellular_ck_rx65n/e2studio_ccrx/)
1. [aws_ether_ck_rx65n](Projects/aws_ether_ck_rx65n/e2studio_ccrx)
1. [boot_loader_ck_rx65n](Projects/boot_loader_ck_rx65n/e2studio_ccrx)
1. [test_aws_ether_ck_rx65n](Projects/test_aws_ether_ck_rx65n/e2studio_ccrx)
1. [test_aws_cellular_ck_rx65n](Projects/test_aws_cellular_ck_rx65n/e2studio_ccrx)

## 5. Select a Demo To Run
This repository contains multiple projects designed to run on the
[CK-RX65N](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/rx-32-bit-performance-efficiency-mcus/ck-rx65n-cloud-kit-based-rx65n-mcu-group)
. These demos are as follows:
1. The [Fleet Provisioning With CSR Demo](Demos/Fleet_Provisioning_With_CSR_Demo/FleetProvisioningDemoExample.c)
1. The [MQTT Subscribe and Publish Demo](Demos/SimplePubSub/simple_pub_sub_task.c)
1. The [MQTT Mutual Authentication Demo](Demos/MutualAuthMQTT/MutualAuthMQTTExample.c)
1. The [OTA Over MQTT Demo](Demos/OtaOverMqtt/OtaOverMqttDemoExample.c)

## 6. Getting Ready
### 6.1 Device Provisioning
When running a demo the device will currently expect to be provisioned
through the use of the
[aws_dev_mode_key_provisioning.c](Demos/dev_mode_key_provisioning/src/aws_dev_mode_key_provisioning.c)
file. This requires setting up an AWS IoT Console Role to perform device
provisioning. More information about the requirements of setting this up
can be found on the [FreeRTOS.org](https://www.freertos.org/iot-fleet-provisioning/demo.html)
website.

### 6.2 Setting the compiler
When selecting a project and demo inside of the
[e2 studio IDE](https://www.renesas.com/us/en/software-tool/e-studio)
you will need to setup the Renesas RX Family
[CC-RX compiler](https://www.renesas.com/us/en/software-tool/cc-compiler-package-rx-family).

1. After following the instructions on the previous link you can
then go to `Help->Add Renesas Toolchains` to add it to the IDE.
1. After this you will need to right click the project in the `Project Explorer`
view in the IDE and select `properties`.
1. In this menu expand the `C/C++ Build` menu.
1. Select `Settings` in this drop-down and select the `Toolchain` tab.
1. Select the `Renesas CC-RX` toolchain in the `Toolchain` menu


1. Sockets_Connect
* Create socket [R_CELLULAR_CreateSocket]
* Convert an IP address [SOCKETS_GetHostByName]
* Connect to socket [R_CELLULAR_ConnectSocket]
2. Sockets_Recv
* Call R_CELLULAR_ReceiveSocket to receive data
3. Sockets_Send
* Call R_CELLULAR_SendSocket to send data
4. Sockets_Disconnect
* Call R_CELLULAR_ShutdownSocket
* Call R_CELLULAR_CloseSocket

