/* 
 *	SPDX-License-Identifier:	BSD-3-Clause 
 * The above license addresses copyright obligations. Please refer to Section 10.4 of the 
 * ATIS Operating Procedures for information about patent licensing obligations under 
 * ATIS' Intellectual Property Rights Policy.
 */


/** \file onem2m.hxx
 * This file contains the constants used in the OS-IoT API .
 */


/** @cond */
#ifndef ONEM2M_HXX_
#define ONEM2M_HXX_



#include <string>
#include <vector>

#include "cdt/CDT-requestPrimitive.hxx"
#include "cdt/CDT-AE.hxx"
#include "cdt/CDT-contentInstance.hxx"
#include "cdt/CDT-container.hxx"
#include "cdt/CDT-commonTypes.hxx"
#include "cdt/CDT-CSEBase.hxx"
#include "cdt/CDT-notification.hxx"
#include "cdt/CDT-subscription.hxx"
#include "cdt/CDT-pollingChannel.hxx"
/** @endcond */

/* Notes on adding new resource types
 * 
 * To add a new resource type to the library consider the following steps:
 * - Include all needed XML source in the buildCommend in /CDT. Note that this may include selecting which part(s) of the XSD files are needed
 * - Add any new files to the #includes above
 * - Add any enumerated values needed from CDT-enumeration types to this file
 * - Edit commonTypesCustom.hxx and .cxx to add procedures to map the new resource types in to the primitiveContent field. Note that you must also add the relevant 
 *   files to the #includes in these files
 * - In onem2m.cxx add support for the new resource types to createResource and updateResource (if applicable)
 * - In onem2mxml.cxx in function "_parsePrimitiveResponseXml" add handlers for the new resource types
 * - In onem2mjson.cxx in function "_parsePrimitiveResponseJson" add handlers for resource specific attributes for the new resource types
 * - In onem2mjson.cxx in function "_jsonEncodeDomElement" add handlers for any new parameters that are supported and for which the default behaviour
 *   of encoding as a quoted string isn't appropriate
*/ 

namespace onem2m
{
  // Magic values defined in CDT-enumerationTypes.xsd

  /** 
  * Identifiers for types of resource or operations in prototol
  */
  enum onem2mResourceType: ::xml_schema::integer {
    resourceTypeUnknown = 0, ///< Unknown resource type or no resource type included
    resourceTypeAccessControlPolicy,
    resourceTypeAE,
    resourceTypeContainer,
    resourceTypeContentInstance,
    resourceTypeCSEBase,
    resourceTypePollingChannel = 15,
    resourceTypeSubscription = 23,
    operationTypeNotification = 30500 ///< Value used to designate a notification operation, which is not a resource
  };

  
  /**
  * Identifiers for operations
  */
  enum onem2mOperation: ::xml_schema::integer {
    operationCreate = 1, ///< Create a resource
    operationRetrieve,  ///< Retrieve a resource
    operationUpdate,    ///< Update a resource
    operationDelete,    ///< Delete a resource
    operationNotify     ///< Notify of a resource change

  };


  /** 
  * Identifers for notification event types
  */
  enum onem2mNotificationEventType: ::xml_schema::integer {
    updateOfResource = 1,
    deleteOfResource,
    createOfDirectChildResource,
    deleteOfDirectChildResource,
    retrieveOfContainerResourceWithNoChildResource
  };


  /** 
  * Identifiers for protocols to used sending commands
  */
  enum onem2mProtocol {
    protocolXml = 1, ///< XML protocol
    protocolJson ///< JSON protocol
  };


  /**
  * Identifiers for results and errors
  *
  * HTTP responses take their normal values. Errors reported by libCURL are returned as 1000+ their native Curl values.
  */
  enum onem2mResult: long {
    onem2mHttpCONTINUE = 100,
    onem2mHttpSWITCHING_PROTOCOLS = 101,
    onem2mHttpOK = 200,
    onem2mHttpCREATED = 201,
    onem2mHttpACCEPTED = 202,
    onem2mHttpNON_AUTHORITATIVE_INFORMATION = 203,
    onem2mHttpNO_CONTENT = 204,
    onem2mHttpRESET_CONTENT = 205,
    onem2mHttpPARTIAL_CONTENT = 206,
    onem2mHttpMULTIPLE_CHOICES = 300,
    onem2mHttpMOVED_PERMANENTLY = 301,
    onem2mHttpFOUND = 302,
    onem2mHttpSEE_OTHER = 303,
    onem2mHttpNOT_MODIFIED = 304,
    onem2mHttpUSE_PROXY = 305,
    onem2mHttpTEMPORARY_REDIRECT = 307,
    onem2mHttpBAD_REQUEST = 400,
    onem2mHttpUNAUTHORIZED = 401,
    onem2mHttpPAYMENT_REQUIRED = 402,
    onem2mHttpFORBIDDEN = 403,
    onem2mHttpNOT_FOUND = 404,
    onem2mHttpMETHOD_NOT_ALLOWED = 405,
    onem2mHttpNOT_ACCEPTABLE = 406,
    onem2mHttpPROXY_AUTHENTICATION_REQUIRED = 407,
    onem2mHttpREQUEST_TIMEOUT = 408,
    onem2mHttpCONFLICT = 409,
    onem2mHttpGONE = 410,
    onem2mHttpLENGTH_REQUIRED = 411,
    onem2mHttpPRECONDITION_FAILED = 412,
    onem2mHttpREQUEST_ENTITY_TOO_LARGE = 413,
    onem2mHttpREQUEST_URI_TOO_LONG = 414,
    onem2mHttpUNSUPPORTED_MEDIA_TYPE = 415,
    onem2mHttpREQUESTED_RANGE_NOT_SATISFIABLE = 416,
    onem2mHttpEXPECTATION_FAILED = 417,
    onem2mHttpUNPROCESSABLE_ENTITY = 422,
    onem2mHttpTOO_MANY_REQUESTS = 429,
    onem2mHttpINTERNAL_SERVER_ERROR = 500,
    onem2mHttpNOT_IMPLEMENTED = 501,
    onem2mHttpBAD_GATEWAY = 502,
    onem2mHttpSERVICE_UNAVAILABLE = 503,
    onem2mHttpGATEWAY_TIMEOUT = 504,
    onem2mHttpHTTP_VERSION_NOT_SUPPORTED = 505,
    onem2mCURLE_UNSUPPORTED_PROTOCOL = 1001,    
    onem2mCURLE_FAILED_INIT,             
    onem2mCURLE_URL_MALFORMAT,           
    onem2mCURLE_NOT_BUILT_IN,
    onem2mCURLE_COULDNT_RESOLVE_PROXY,   
    onem2mCURLE_COULDNT_RESOLVE_HOST,    
    onem2mCURLE_COULDNT_CONNECT,         
    onem2mCURLE_WEIRD_SERVER_REPLY,      
    onem2mCURLE_REMOTE_ACCESS_DENIED,
    onem2mCURLE_FTP_ACCEPT_FAILED, 
    onem2mCURLE_FTP_WEIRD_PASS_REPLY,    
    onem2mCURLE_FTP_ACCEPT_TIMEOUT,
    onem2mCURLE_FTP_WEIRD_PASV_REPLY,    
    onem2mCURLE_FTP_WEIRD_227_FORMAT,    
    onem2mCURLE_FTP_CANT_GET_HOST,       
    onem2mCURLE_HTTP2,
    onem2mCURLE_FTP_COULDNT_SET_TYPE,    
    onem2mCURLE_PARTIAL_FILE,            
    onem2mCURLE_FTP_COULDNT_RETR_FILE,   
    onem2mCURLE_OBSOLETE20,              
    onem2mCURLE_QUOTE_ERROR,             
    onem2mCURLE_HTTP_RETURNED_ERROR,     
    onem2mCURLE_WRITE_ERROR,             
    onem2mCURLE_OBSOLETE24,              
    onem2mCURLE_UPLOAD_FAILED,           
    onem2mCURLE_READ_ERROR,              
    onem2mCURLE_OUT_OF_MEMORY,           
    onem2mCURLE_OPERATION_TIMEDOUT,      
    onem2mCURLE_OBSOLETE29,              
    onem2mCURLE_FTP_PORT_FAILED,         
    onem2mCURLE_FTP_COULDNT_USE_REST,    
    onem2mCURLE_OBSOLETE32,              
    onem2mCURLE_RANGE_ERROR,             
    onem2mCURLE_HTTP_POST_ERROR,         
    onem2mCURLE_SSL_CONNECT_ERROR,       
    onem2mCURLE_BAD_DOWNLOAD_RESUME,     
    onem2mCURLE_FILE_COULDNT_READ_FILE,  
    onem2mCURLE_LDAP_CANNOT_BIND,        
    onem2mCURLE_LDAP_SEARCH_FAILED,      
    onem2mCURLE_OBSOLETE40,              
    onem2mCURLE_FUNCTION_NOT_FOUND,      
    onem2mCURLE_ABORTED_BY_CALLBACK,     
    onem2mCURLE_BAD_FUNCTION_ARGUMENT,   
    onem2mCURLE_OBSOLETE44,              
    onem2mCURLE_INTERFACE_FAILED,        
    onem2mCURLE_OBSOLETE46,              
    onem2mCURLE_TOO_MANY_REDIRECTS,      
    onem2mCURLE_UNKNOWN_OPTION,          
    onem2mCURLE_TELNET_OPTION_SYNTAX,    
    onem2mCURLE_OBSOLETE50,              
    onem2mCURLE_PEER_FAILED_VERIFICATION,
    onem2mCURLE_GOT_NOTHING,             
    onem2mCURLE_SSL_ENGINE_NOTFOUND,     
    onem2mCURLE_SSL_ENGINE_SETFAILED, 
    onem2mCURLE_SEND_ERROR,              
    onem2mCURLE_RECV_ERROR,              
    onem2mCURLE_OBSOLETE57,              
    onem2mCURLE_SSL_CERTPROBLEM,         
    onem2mCURLE_SSL_CIPHER,              
    onem2mCURLE_SSL_CACERT,              
    onem2mCURLE_BAD_CONTENT_ENCODING,    
    onem2mCURLE_LDAP_INVALID_URL,        
    onem2mCURLE_FILESIZE_EXCEEDED,       
    onem2mCURLE_USE_SSL_FAILED,          
    onem2mCURLE_SEND_FAIL_REWIND,
    onem2mCURLE_SSL_ENGINE_INITFAILED,   
    onem2mCURLE_LOGIN_DENIED,
    onem2mCURLE_TFTP_NOTFOUND,           
    onem2mCURLE_TFTP_PERM,               
    onem2mCURLE_REMOTE_DISK_FULL,        
    onem2mCURLE_TFTP_ILLEGAL,            
    onem2mCURLE_TFTP_UNKNOWNID,          
    onem2mCURLE_REMOTE_FILE_EXISTS,      
    onem2mCURLE_TFTP_NOSUCHUSER,         
    onem2mCURLE_CONV_FAILED,             
    onem2mCURLE_CONV_REQD,
    onem2mCURLE_SSL_CACERT_BADFILE,
    onem2mCURLE_REMOTE_FILE_NOT_FOUND,   
    onem2mCURLE_SSH,
    onem2mCURLE_SSL_SHUTDOWN_FAILED,
    onem2mCURLE_AGAIN,
    onem2mCURLE_SSL_CRL_BADFILE, 
    onem2mCURLE_SSL_ISSUER_ERROR,
    onem2mCURLE_FTP_PRET_FAILED,         
    onem2mCURLE_RTSP_CSEQ_ERROR,         
    onem2mCURLE_RTSP_SESSION_ERROR,      
    onem2mCURLE_FTP_BAD_FILE_LIST,       
    onem2mCURLE_CHUNK_FAILED,            
    onem2mCURLE_NO_CONNECTION_AVAILABLE,
    onem2mCURLE_SSL_PINNEDPUBKEYNOTMATCH,
    onem2mCURLE_SSL_INVALIDCERTSTATUS,   
    onem2mCURLE_HTTP2_STREAM
  };

  typedef std::function<onem2mResult(std::string, std::string&, ::onem2m::notification*)> notificationCallbackFn;

  extern bool _debug;

  std::string _getHostName();

  void initialize ();

  void terminate ();

  void setProtocol( onem2mProtocol );  
 
  void setHostName( const std::string name );

  void setFrom( const std::string newFrom );

  std::string getFrom();

  void setDebug( bool debugOut );

  std::unique_ptr< ::xml_schema::type > retrieveResource(const std::string& address, const std::string& requestId,
                                                         long& result,
                                                         ::xml_schema::integer& resObjType);    
 
  std::unique_ptr< ::xml_schema::type > deleteResource(const std::string& address, const std::string& requestId,
                                                       long& result,
                                                       ::xml_schema::integer& resObjType);  
      
  std::unique_ptr< ::xml_schema::type > createResource(const std::string& address, const std::string& requestId,
                                                       const ::xml_schema::type& resource,
                                                       long& result,
                                                       ::xml_schema::integer& resObjType);

  std::unique_ptr< ::xml_schema::type > updateResource(const std::string& address, const std::string& requestId,
                                                       const ::xml_schema::type& resource,
                                                       long& result,
                                                       ::xml_schema::integer& resObjType);         
  
  std::unique_ptr< ::xml_schema::type > send(const ::onem2m::requestPrimitive&,
                  long&,
                  ::xml_schema::integer&);

  void startHttpServer( const std::vector<std::string>& addressRegex, long port, notificationCallbackFn callback );

  void stopHttpServer( );

}

#endif
