#include "stdio.h"
#include "stdlib.h"
#include "wsdd.nsmap"
#include "wsddapi.h"
#include "wsaapi.h"  
#include <stddef.h>







void wsdd_event_ProbeMatches(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, struct wsdd__ProbeMatchesType *matches)
{

}



void wsdd_event_ResolveMatches(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, struct wsdd__ResolveMatchType *match)
{

}



void wsdd_event_Hello(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, const char *EndpointReference, const char *Types, const char *Scopes, const char *MatchBy, const char *XAddrs, unsigned int MetadataVersion)
{

}



void wsdd_event_Bye(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, const char *EndpointReference, const char *Types, const char *Scopes, const char *MatchBy, const char *XAddrs, unsigned int *MetadataVersion)
{

}



soap_wsdd_mode wsdd_event_Resolve(struct soap *soap, const char *MessageID, const char *ReplyTo, const char *EndpointReference, struct wsdd__ResolveMatchType *match)
{
    return SOAP_WSDD_ADHOC;
}


char  g_scopes[] = "onvif://www.onvif.org/name/IPCAM_eric";

soap_wsdd_mode wsdd_event_Probe(struct soap *soap, const char *MessageID, const char *ReplyTo, const char *Types, const char *Scopes, const char *MatchBy, struct wsdd__ProbeMatchesType *matches)
{

	printf("probe match\n");
#if 0
    struct wsdd_param_t *wsdd_param = (struct wsdd_param_t *)soap->user;

    if(!wsdd_param)
        return SOAP_WSDD_ADHOC;

#endif
    soap_wsdd_init_ProbeMatches(soap, matches);

    soap_wsdd_add_ProbeMatch(soap,
                             matches,
                              soap_wsa_rand_uuid(soap), 
                            	"tds:Device",
                             g_scopes,
                             "http://schemas.xmlsoap.org/ws/2005/04/discovery/rfc3986",
                             "http://10.1.16.149:80/onvif/device_service",
                             10);

	soap_wsdd_ProbeMatches(soap,
                           NULL,
                           soap_wsa_rand_uuid(soap) ,
                           MessageID,
                           ReplyTo,
                           matches);
#if 0
    soap_wsdd_ProbeMatches(soap,
                           NULL,
                           soap_wsa_rand_uuid(soap) ,
                           MessageID,
                           ReplyTo,
                           matches);


#endif
    return SOAP_WSDD_ADHOC;
}

SOAP_FMAC5 int SOAP_FMAC6 SOAP_ENV__Fault(struct soap *pSoap, char *faultcode, char *faultstring, char *faultactor, struct SOAP_ENV__Detail *detail, struct SOAP_ENV__Code *SOAP_ENV__Code, struct SOAP_ENV__Reason *SOAP_ENV__Reason, char *SOAP_ENV__Node, char *SOAP_ENV__Role, struct SOAP_ENV__Detail *SOAP_ENV__Detail)
{
	printf("%s %s :%d\n",__FILE__,__func__, __LINE__);
//   DBG("%s %s :%d\n",__FILE__,__func__, __LINE__);
   return SOAP_OK;
}
#define MULTICAST_GROUP "239.255.255.250" 

void main(void)
{
//	int port = 8080;
	struct soap soap;
  //init_received();
  soap_init1(&soap, SOAP_IO_UDP);
  /* reuse address */
  soap.bind_flags = SO_REUSEADDR;
  /* bind */
  if (!soap_valid_socket(soap_bind(&soap, NULL, 3702, 100)))
  { soap_print_fault(&soap, stderr);
    exit(1);
  }
  /* optionally join a multicast group */
  if (MULTICAST_GROUP)
  { struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_GROUP);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(soap.socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
      exit(1);
  }
  /* serve requests */
  for (;;)
  { printf("Accepting requests\n");
    /* accept (not really needed for UDP, so can be omitted) */
    if (!soap_valid_socket(soap_accept(&soap)))
    { soap_print_fault(&soap, stderr);
      exit(1);
    }
    if (soap_serve(&soap))
      soap_print_fault(&soap, stderr);
    soap_destroy(&soap);
    soap_end(&soap);
  }
  soap_done(&soap);
  //return 0;

#if 0
soap_wsdd_Hello(soap,
  SOAP_WSDD_MANAGED,    // or SOAP_WSDD_ADHOC for ad-hoc mode
  "soap.udp://239.255.255.250:3702",         // "http(s):" URL, or "soap.udp:" UDP, or TCP/IP address
  soap_wsa_rand_uuid(soap), // a unique message ID
  NULL,
  "http://10.1.16.149/onvif/device_service",         // where they can find me for WS-Discovery
  "wsdd:DiscoveryProxy",// Types: I'm a DP
  NULL,                 // Scope
  NULL,                 // MatchBy
  NULL,                 // XAddrs
  75965);               // MDVersion
	//printf("hello\n");
#endif

}






