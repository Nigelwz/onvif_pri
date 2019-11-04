#include <stddef.h>


#include "wsddapi.h"
#include "wsdd_param.h"





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



soap_wsdd_mode wsdd_event_Probe(struct soap *soap, const char *MessageID, const char *ReplyTo, const char *Types, const char *Scopes, const char *MatchBy, struct wsdd__ProbeMatchesType *matches)
{
 #if 1
printf("%s,%d\n",__FUNCTION__, __LINE__); 
printf("MessageID:%s\n", MessageID); 
printf("ReplyTo:%s\n", ReplyTo); 
printf("Types:%s\n", Types); 
printf("Scopes:%s\n", Scopes); 
printf("MatchBy:%s\n", MatchBy); 
#endif
#if 1 
soap_wsdd_init_ProbeMatches(soap, matches); 
soap_wsdd_add_ProbeMatch(soap, matches, 
"urn:uuid:464A4854-4656-5242-4530-313035394100", 
"dn:NetworkVideoTransmitter", 
"onvif://www.onvif.org/type/video_encoder onvif://www.onvif.org/type/audio_encoder onvif://www.onvif.org/type/ptz onvif://www.onvif.org/type/video_analytics onvif://www.onvif.org/hardware/HD-IPCAM onvif://www.onvif.org/location/country/china onvif://www.onvif.org/name/IPCAM", 
NULL, 
"http://10.1.16.117/onvif/device_service",10); 

#endif
return SOAP_WSDD_MANAGED; 



#if 0
	struct wsdd_param_t *wsdd_param = (struct wsdd_param_t *)soap->user;

    if(!wsdd_param)
        return SOAP_WSDD_ADHOC;


    soap_wsdd_init_ProbeMatches(soap, matches);

    soap_wsdd_add_ProbeMatch(soap,
                             matches,
                             wsdd_param->endpoint,
                             wsdd_param->type,
                             wsdd_param->scope,
                             NULL,
							NULL,
							 //                             get_xaddr(wsdd_param),
                             wsdd_param->metadata_ver);

    soap_wsdd_ProbeMatches(soap,
                           NULL,
                           soap_wsa_rand_uuid(soap) ,
                           MessageID,
                           ReplyTo,
                           matches);


    return SOAP_WSDD_ADHOC;
#endif
}
