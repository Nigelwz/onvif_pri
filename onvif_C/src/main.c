//#include "stdio.h"
//#include "stdlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
 #include "soapH.h"  
//#include "wsdd.nsmap"   
//#include "wsddapi.h"
//#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
//#include <unistd.h>
//#include <errno.h>

// my headers
//#include "daemon.h"
//#include "wsdd_param.h"
//#include "net_utils.h"


// gsoap headers
#include "wsdd.nsmap"
#include "wsddapi.h"





int main(void)
{
     int m, s;
    struct ip_mreq mcast;
    struct soap soap;
    soap_init1(&soap, SOAP_IO_UDP);  
    soap_set_namespaces(&soap, namespaces);
    soap_set_mode(&soap, SOAP_C_UTFSTRING);
	soap.ipv4_multicast_ttl = 1;
	soap.connect_flags = SO_BROADCAST;
    soap.bind_flags        = SO_REUSEADDR;
    //soap.connect_timeout   = 0;
    //soap.recv_timeout      = 0;
    //soap.send_timeout      = 0;
    soap_register_plugin(&soap, soap_wsa);  //這個很重要，我分析了很久才得出的
// 開啟除錯資訊
    soap_set_recv_logfile(&soap, "./log/recv.xml");
    soap_set_sent_logfile(&soap, "./log/send.xml");
    soap_set_test_logfile(&soap, "./log/test.log");
    if(!soap_valid_socket(soap_bind(&soap, NULL, 3702, 16)))
     {
  soap_print_fault(&soap, stderr);
  exit(1);
     }
    mcast.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
    mcast.imr_interface.s_addr = inet_addr("0.0.0.0");
    if(setsockopt(soap.master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast)) < 0) {
        printf("setsockopt error!\n");
        return 0;
    }  
printf("socket bind sucess\n");
	   send_hello(&soap, NULL);

	//成功繫結之後，便開始監聽
    for (;;) {
        //監聽直到有連線請求
//        send_bye(&soap, NULL);
		soap_wsdd_listen(&soap, 0);
        printf("wssd listen fail\n");
		soap_destroy(&soap);
        soap_end(&soap);
        fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);
    }
    soap_done(&soap);
    return 0;	
	//printf("fff");
}
