/* 
 *	SPDX-License-Identifier:	BSD-3-Clause 
 * The above license addresses copyright obligations. Please refer to Section 10.4 of the 
 * ATIS Operating Procedures for information about patent licensing obligations under 
 * ATIS' Intellectual Property Rights Policy.
 */

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "onem2m.hxx"
#include "SimpleOpt.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

using namespace ::onem2m;


void parseCommaList( const ::std::string str, ::std::vector<long> & vect ) {
  std::stringstream ss(str);
  long i;

  while (ss >> i) {
    vect.push_back(i);
    if (ss.peek() == ',')
      ss.ignore();
  }
}

bool checkResult(const ::std::vector<long> &vect, const long result) {
  return std::find(vect.begin(), vect.end(), result) != vect.end();
}


long createContentInstance(const ::std::string & cse_root_addr) {
  long result;
  
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;

  // *** Create a contentInstance ***
  
  auto ci = contentInstance();
  ci.contentInfo("application/text");
  ci.content ("Temp: "+ std::to_string(rand() % 100));
  respObj = createResource(cse_root_addr+"/MY_SENSOR/DESCRIPTOR", "1234", ci, result, respObjType); 
  std::cout << "Create content instance result:" << result << "\n";
  return result;
}

long createAE(const ::std::string & cse_root_addr, const ::std::string & poa) {
  long result;
  
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;
 
  // *** Create a "MY_SENSOR" AE ***

  auto ae = AE();
  ae.resourceName("MY_SENSOR");
  ae.App_ID("app-sensor");
  //ae.requestReachability(false); // The CSE can't send us a requestPrimitive directly (because we don't have an HTTP server to receive it)
  ae.requestReachability(true);
  auto lb = labels ();
  lb.push_back("Type/sensor");
  lb.push_back("Category/temperature");
  ae.labels(lb);

  // How to set the contentSerialization parameter - commented out in this version due to incompatibility with IoTDM server
  /*
  auto pmt = permittedMediaTypes( permittedMediaTypes::application_xml );
  auto sb = serializations_base ();
  sb.push_back( pmt );
  ae.contentSerialization( serializations(sb) );
  */

  // How to set the accessControlListID (acpi) parameter - commented out as not needed for basic test
  /*
  ae.accessControlPolicyIDs( acpType() );
  ae.accessControlPolicyIDs().get().push_back( onem2m::ID( "ACPI1" ) );
  ae.accessControlPolicyIDs().get().push_back( onem2m::ID( "ACPI2" ) );
  */
 
  auto poal =  poaList(poaList_base(1, poa));
  ae.pointOfAccess( poal );

  respObj = createResource(cse_root_addr, "1234", ae, result, respObjType);  
  std::cout << "Create AE result:" << result << "\n";
  // Example of how to check the type of an object returned by the send operation and extract its contents
  if (respObjType == resourceTypeAE) {
    auto aePtr = static_cast< AE* >(respObj.get()); // Cast generic object to pointer to the appropriate specific child class
    if (aePtr->AE_ID().present ())
      std::cout << "AE-ID:" << aePtr->AE_ID() . get() << "\n";
  }

  return result;
}

long createContainer (const ::std::string & cse_root_addr) {
  long result;
  
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;

  // *** Create a "DESCRIPTOR" container ***

  auto c = container();
  c.resourceName("DESCRIPTOR");
  respObj = createResource(cse_root_addr+"/MY_SENSOR", "1234", c, result, respObjType);  
  std::cout << "Create container result:" << result << "\n";

  return result;
}


long createSubscription (const ::std::string & cse_root_addr, const ::std::string & poa) {
  long result;
  
  // *** Create a subscription ***
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;

  auto sub = subscription();
  auto uris = listOfURIs();
  auto criteria = eventNotificationCriteria();
  // If the complexType is declared in-line in the XSD file then the CodeSynthesis compiler generates an
  // automatically named type within the parent class - see example below
  auto events = eventNotificationCriteria::notificationEventType_sequence();

  sub.resourceName("MY_SUBSCRIPTION");
  events.push_back( createOfDirectChildResource); // Add one notification case to the list of notification events
  criteria.notificationEventType(events); // Assign the list of events to the criteria
  sub.eventNotificationCriteria(criteria); // Assign the criteria to the subscription
  sub.notificationContentType(nctAllAttributes); // Ask for everything in the notification
  if (poa=="") // Choose whether to send notifications to the PoA in the AE resource or an explicit URL in the subscription resource
    uris.push_back(cse_root_addr+"/MY_SENSOR"); // Add one notification URI
  else
    uris.push_back(poa);
  sub.notificationURI(uris);
  sub.latestNotify(true);
  respObj = createResource(cse_root_addr+"/MY_SENSOR/DESCRIPTOR", "1234", sub, result, respObjType);  
  //respObj = createResource(cse_root_addr, "1234", sub, result, respObjType);  
  std::cout << "Create subscription result:" << result << "\n";
  return result;
}

long createPollingChannel(const ::std::string & cse_root_addr) {
  long result;
  
  // *** Create a pollingChannel ***
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;

  auto pollChan = pollingChannel();
  pollChan.resourceName("MY_POLLING_CHANNEL");
  respObj = createResource(cse_root_addr+"/MY_SENSOR", "1234", pollChan, result, respObjType);  
  //respObj = createResource(cse_root_addr, "1234", pollChan, result, respObjType); 
  std::cout << "Create pollingChannel result:" << result << "\n";
  std::cout << "Type:"<< respObjType << "\n";
  return result;

}

long createAccessControlPolicy(const ::std::string & cse_root_addr) {
  long result;

  // *** create an ACP **
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;

  auto acp = accessControlPolicy();
  acp.resourceName("MY_ACP");
  
  auto acOriginators = listOfURIs ();
  acOriginators.push_back("*");
  auto acOperations = accessControlOperations( accessControlAll );
  auto acr = accessControlRule(acOriginators, acOperations);
  // accessControlAuthenticationFlag is not supported in all CSEs.
  // acr.accessControlAuthenticationFlag(false);

  // Set accessControlContext - acc
  // not fully supported in all CSEs
  /*
  auto acc = accessControlContexts(); 
  acc.accessControlWindow( ).push_back( "* * * * * *" );
  acc.accessControlWindow( ).push_back( "* * * * * *" ); // Normally not useful to duplicate contents, but for testing...
  auto ipa=accessControlIpAddresses();
  auto ip4a=ipv4Addresses();
  ip4a.push_back("127.0.0.1");
  ip4a.push_back("192.168.0.1"); // Normally not useful to duplicate contents, but for testing...
  ipa.ipv4Addresses(ip4a);
  acc.accessControlIpAddresses( ipa );
  
  auto aclr = locationRegion();
  auto cc = countryCode("US"); // One country code
  auto ccl = countryCode1(); // A list of country codes
  ccl.push_back(cc);
  ccl.push_back(countryCode("UK"));
  aclr.countryCode(ccl);
  acc.accessControlLocationRegion( aclr );
  acr.accessControlContexts( ).push_back(acc);
  */

  // Set accessControlRules - acrs
  auto acrs = setOfAcrs();
  acrs.accessControlRule().push_back( acr );

  acp.privileges( acrs );
  acp.selfPrivileges( acrs );

  respObj = createResource(cse_root_addr+"/MY_SENSOR", "1234", acp, result, respObjType); 
  std::cout << "Create accessControlPolicy result:" << result << "\n";
  std::cout << "Type:"<< respObjType << "\n";
  return result;
}


void outputObject( const ::xml_schema::integer objType, const ::xml_schema::type * objPtr) {
  // For now, just support a few objects.

  // Check the type of the object, cast to the appropriate pointer type and then process
  // the object specific fields.

  std::cout << "Obj Type#:" << objType << "\n";
  // Example of how to check the type of an object returned by an operation and extract its contents
  if (objType == resourceTypeCSEBase) {
    auto csePtr = static_cast< const CSEBase* >(objPtr);
    if (csePtr->supportedResourceType().present ())
      std::cout << "Supported resource types:" << csePtr-> supportedResourceType () . get() << "\n";
    if (csePtr->accessControlPolicyIDs().present ()) {
      std::cout << "Access Control Policy ID(s):";
      for (uint i=0; i< csePtr->accessControlPolicyIDs().get().size(); i++)
        std::cout << csePtr->accessControlPolicyIDs().get()[i] << " ";
      std::cout << "\n";
    } 
  } 
  if (objType == resourceTypeContentInstance) {
    auto ciPtr = static_cast< const contentInstance* >(objPtr);
    if (ciPtr->content().present ())
      std::cout << "contentInstance with content:" << ciPtr-> content () . get() << "\r\n";
  }
  if (objType == operationTypeNotification) {
    auto notif = static_cast< const notification* >(objPtr);
    if (notif->subscriptionReference().present())
      std::cout << "Notification for subs:" << notif->subscriptionReference().get() << "\r\n" ; 
    else
      std::cout << "Notification\r\n";
    if (notif->notificationEvent().present() && notif->notificationEvent().get().notificationEventType().present() )
      std::cout << " Notification event type:" << notif->notificationEvent().get().notificationEventType().get() << "\r\n";
    if (notif->subscriptionDeletion().present() && notif->subscriptionDeletion().get())
      std::cout << " Subscription Deletion\r\n";
    ::xml_schema::integer respObjType;
    ::xml_schema::type * respObjPtr;
    respObjPtr = notif -> getRepresentationObject( respObjType );
    if (respObjType != resourceTypeUnknown) {
      std::cout <<" Notification representation included:\r\n";
      outputObject(respObjType, respObjPtr);
    }
  }
}


long retrieveResources (const ::std::string & cse_root_addr) {
  long result;
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;
  

   // *** Retrieve a resource ***
  respObj = retrieveResource(cse_root_addr, "1234", result, respObjType);
  std::cout << "Retrieve result:" << result << "\n";  
  outputObject( respObjType, respObj.get());

  return result;
}

long updateResources(const ::std::string & cse_root_addr) {
  long result;
  requestPrimitive reqPrim = requestPrimitive( );
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;

  // ** Update the AE **

  auto ae = AE();
  auto lb = labels ();
  lb.push_back("Type/updateSensor");
  ae.labels(lb);
  respObj = updateResource(cse_root_addr+"/MY_SENSOR", "9876", ae, result, respObjType); 
  std::cout << "Delete AE result:" << result << "\n";
  return result;
}

long deleteResources (const ::std::string & cse_root_addr) {
  long result;
  requestPrimitive reqPrim = requestPrimitive( );
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;

  // ** Delete the AE **
  respObj = deleteResource(cse_root_addr+"/MY_SENSOR", "9876", result, respObjType); 
  std::cout << "Delete AE result:" << result << "\n";
  return result;
}

long poll (const ::std::string & cse_root_addr) {
  long result;
  while (1) {
    result = retrieveResources(cse_root_addr+"/MY_SENSOR/MY_POLLING_CHANNEL/pcu");
    if (result >=300 && result !=408) // If result isn't success and isn't a timeout then wait before resending 
      sleep(10);
  }
  return result;
}


onem2mResult processNotification(std::string host, std::string& from, notification* notif ) {
    // Callback routine which is passed to startHttpServer() and called when a notification is received.
    // This callback will occur in a separate thread to the main program.

    // This callback should check if the notification is a "verification request" (see code below) and respond appropriately if so.
    // This callback should also implement any application specific processing for notifications that are not verification requests.
 
    // On entry, the "host" parameter contains the "Host:" header from the HTTP request (i.e. the oneM2M "to" parameter)
    // the "from" parameter contains the "X-M2M-Origin:" header from the HTTP request (i.e. the oneM2M "from" parameter)
    // the "notif" parameter contains a pointer to a notification object that represents the contents of the notification.

    // The value in "from" on return will be encoded in to the "X-M2M-Origin:" HTTP header of the response - ie will become the
    // "from" parameter of the primitiveResponse.
    // The return value should be an HTTP response code - eg onem2mHttpOK for an "OK" response

  if (notif->verificationRequest().present () && notif->verificationRequest().get()) { // Check if this is a vefification request
    // Whether to accept the verificationRequest could be decided here, e.g. by checking the "host" and "from" parameters.
    // In this implmentation we accept all verification requests.
    
    std::cout << "Notification verification from:" << from << "r\n" ;
    from = getFrom();
    return onem2mHttpOK;
  }
  from = getFrom();
  std::cout << "\r\n";
  outputObject( operationTypeNotification, notif);
 
  return onem2mHttpOK;

}


long startServer (const std::string & poaPort) {
  // Start an HTTP server
  long result;
  result = startHttpServer({"^.*$"},::std::stoi( poaPort ), &processNotification);
  if (result == long(onem2mHttpOK))
    std::cout << "HTTP Server started OK\n";
  else
    std::cout << "HTTP Server didn't start. Check port is not already in use. Result =" << result << "\n";
  return result;
}

static const char * getLastErrorText( int a_nError ) {
    switch (a_nError) {
    case SO_SUCCESS:            return "Success";
    case SO_OPT_INVALID:        return "Unrecognized option";
    case SO_OPT_MULTIPLE:       return "Option matched multiple strings";
    case SO_ARG_INVALID:        return "Option does not accept argument";
    case SO_ARG_INVALID_TYPE:   return "Invalid argument format";
    case SO_ARG_MISSING:        return "Required argument is missing";
    case SO_ARG_INVALID_DATA:   return "Invalid argument data";
    default:                    return "Unknown error";
    }
}

int outputAns(bool pass, bool printTestRes) {
  if (printTestRes) {
    if (pass)
      std::cout << "### TEST PASS ###\n";
    else
      std::cout << "=== TEST FAIL ===\n";
  }
  return (pass)? 0:1;
}

std::string stringToHexString(const std::string& input) {
  static const char* const lut = "0123456789abcdef";
  size_t len = input.length();

  std::string output;
  output.reserve(2 * len);
  for (size_t i = 0; i < len; ++i) {
    const unsigned char c = input[i];
    output.push_back(lut[c >> 4]);
    output.push_back(lut[c & 15]);
  }
  return output;
}

int main (int argc, char* argv[]) {
  ::std::vector<long> passResults; // OS-IoT result codes that would cause a test to pass

  passResults.push_back(onem2mHttpOK);
  passResults.push_back(onem2mHttpCREATED);
  passResults.push_back(onem2mHttpACCEPTED);
  
  ::onem2m::initialize();

  // For Eclipse OM2M
  setHostName("127.0.0.1:8080");
  ::std::string cse_root_addr = "/in-cse/in-name"; // SP-Relative address
  ::std::string poaAddr = "localhost";
  ::std::string poaPort = "18888";
  // For Open Daylight IoTDM
  // setHostName("127.0.0.1:8282");
  //::std::string cse_root_addr = "InCSE1"; // Relative address

  // This setting of "from" is not compliant to oneM2M specs - 
  // Per TS001 Section 7.2, Table 7.2-1, The AE-ID specified in the From parameter in the AE 
  // create request should start with ‘C’ or ‘S’.  
  // However, this setting is correct for testing with the OM2M CSE
  setFrom("admin:admin");

  enum { optCreate, optDelete, optUpdate, optSubscribe, optSubscribeExplicitUrl, optPollingChannel, optRetrieve,
         optContentInstance, optListenPolling, optListenHttp, optWait, optAcp,
         optHostName, optAddress, optFrom, optXml,
         optHttp, optJson, optQuiet, optHttps,
         optNoVerifyPeer, optNoVerifyHost, optCaPath, optCaInfo, optSslCert, optSslKey, optKeyPasswd, optSubjectANA,
         optCipherList, optPassResultCodes, optPrintTestRes, optPoaAddr, optPoaPort, 
         optHttpsPsk, optPskIdentity, optPskKey, optPskKeyAscii};
  
  CSimpleOpt::SOption  cmdOptions[] = {
  { optCreate, "-c", SO_NONE },
  { optDelete, "-d", SO_NONE },
  { optUpdate, "-u", SO_NONE },
  { optSubscribe, "-s", SO_NONE },
  { optSubscribeExplicitUrl, "--su", SO_NONE },
  { optPollingChannel, "-p", SO_NONE},
  { optRetrieve, "-r", SO_NONE },
  { optContentInstance, "--ci", SO_NONE },
  { optListenPolling, "-l", SO_NONE },
  { optListenHttp, "-L", SO_NONE },
  { optWait, "-W", SO_NONE },
  { optAcp, "--acp", SO_NONE },
  { optHttps, "--https", SO_NONE },
  { optHttpsPsk, "--httpsPsk", SO_NONE},

  { optNoVerifyPeer, "--noVerifyPeer", SO_NONE },
  { optNoVerifyHost, "--noVerifyHost", SO_NONE },
  { optCaPath, "--caPath", SO_REQ_SEP },
  { optCaInfo, "--caInfo", SO_REQ_SEP },
  { optSslCert, "--sslCert", SO_REQ_SEP },
  { optSslKey, "--sslKey", SO_REQ_SEP },
  { optKeyPasswd, "--keyPasswd", SO_REQ_SEP },
  { optSubjectANA, "--subjectANA", SO_REQ_SEP },
  { optCipherList, "--cipherList", SO_REQ_SEP },
  { optPassResultCodes, "--passResCodes", SO_REQ_SEP },
  { optPrintTestRes, "--printTestRes", SO_NONE },
  { optPoaAddr, "--poaAddr", SO_REQ_SEP},
  { optPoaPort, "--poaPort", SO_REQ_SEP},
  { optPskIdentity, "--pskIdentity", SO_REQ_SEP},
  { optPskKey, "--pskKey", SO_REQ_SEP},
  { optPskKeyAscii, "--pskKeyAscii", SO_REQ_SEP},

  { optHostName, "-h", SO_REQ_SEP },
  { optAddress, "-a", SO_REQ_SEP },
  { optFrom, "-f", SO_REQ_SEP },
  { optXml, "-x", SO_NONE },
  { optJson, "-j", SO_NONE },
  { optQuiet, "-q", SO_NONE },
  SO_END_OF_OPTIONS 
  };

  ::std::vector<int> ops;
  bool printTestRes = false;

  CSimpleOpt args(argc, argv, cmdOptions, SO_O_NOSLASH | SO_O_SHORTARG | SO_O_CLUMP);
  while(args.Next()) {
    if (args.LastError() == SO_SUCCESS) {
      switch (args.OptionId()) {
        case optQuiet:
          setDebug( false );
          break;
        case optHttps:
          setTransport( transportHttpsCertificate );
          break;
        case optHttpsPsk:
          setTransport( transportHttpsPsk );
          break;
        case optXml:
          setProtocol( protocolXml);
          break;
        case optJson:
           setProtocol( protocolJson);
           break;
        case optHostName:
           setHostName( args.OptionArg() );
           break;
        case optAddress:
          cse_root_addr=std::string( args.OptionArg() );
          break;
        case optFrom:
          setFrom( args.OptionArg() );
          break;

        case optNoVerifyPeer:
          setVerifyPeer( false );
          break;
        case optNoVerifyHost:
          setVerifyHost( false );
          break;
        case optCaPath:
          setCaPath( args.OptionArg() );
          break;
        case optCaInfo:
          setCaInfo( args.OptionArg() );
          break;
        case optSslCert:
          setSslCert( args.OptionArg() );
          break;
        case optSslKey:
          setSslKey( args.OptionArg() );
          break;
        case optKeyPasswd:
          setKeyPasswd( args.OptionArg() );
          break;
        case optSubjectANA:
           setSubjectAltNameAllowed( args.OptionArg() );
           break;
        case optCipherList:
           setCipherList( args.OptionArg() );
           break;
        case optPassResultCodes:
           passResults.clear();
           parseCommaList( args.OptionArg(), passResults );
           break;
        case optPrintTestRes:
           printTestRes = true;
           break;
        case optPoaAddr:
           poaAddr=args.OptionArg();
           break;
        case optPoaPort:
           poaPort=args.OptionArg();
           break;
        case optPskIdentity:
           setPskIdentity( args.OptionArg() );
           break;
        case optPskKey:
           setPskKey( args.OptionArg() );
           break;
        case optPskKeyAscii:
           setPskKey( stringToHexString( args.OptionArg() ) );
           break;
        default:
          ops.push_back(args.OptionId());
          break;
      }
    } else { // Error in arguments
      std::cout << "Error in arguments. See http://www.os-iot.org/documentation/\r\n";
      std::cout << "Option: " << args.OptionText() << " Error: " << getLastErrorText(args.LastError()) << "\r\n";
      std::cout << "Data: " << args.OptionArg() <<"\r\n";
      return outputAns(false, printTestRes);
    }
  }


  bool fail = false;
  long result;

  if (ops.size() == 0) {
    ::std::cout << "No action specified. See http://www.os-iot.org/documentation/\r\n";
    return outputAns(false, printTestRes);
  } else

    for( auto opType: ops) {
      switch (opType) {
        case optCreate:
          result=createAE (cse_root_addr, "http://"+poaAddr+":"+poaPort+"/");
          fail |= ! checkResult(passResults, result); 
          result=createContainer (cse_root_addr);
          fail |= ! checkResult(passResults, result); 
          result=createContentInstance(cse_root_addr);
          fail |= ! checkResult(passResults, result); 
          break;
        case optDelete:
          result=deleteResources (cse_root_addr);
          fail |= ! checkResult(passResults, result); 
          break;
        case optUpdate:
          result=updateResources(cse_root_addr);
          fail |= ! checkResult(passResults, result); 
          break;
        case optRetrieve:
          result=retrieveResources(cse_root_addr);
          fail |= ! checkResult(passResults, result); 
          break;
        case optSubscribe:
          result=createSubscription(cse_root_addr, ""); // Use PoA in AE resource
          fail |= ! checkResult(passResults, result); 
          break;
        case optPollingChannel:
          result=createPollingChannel(cse_root_addr);
          fail |= ! checkResult(passResults, result); 
          break;
        case optContentInstance:
          result=createContentInstance(cse_root_addr);
          fail |= ! checkResult(passResults, result); 
          break;
        case optListenPolling:
          result=poll(cse_root_addr);
          fail |= ! checkResult(passResults, result); 
          break;
        case optListenHttp:
          result=startServer( poaPort );
          fail |= ! checkResult(passResults, result); 
          break;
        case optWait:
           while ( getHttpServerRunning() ) {
             std::this_thread::sleep_for(std::chrono::seconds(1));
           }
           break;
        case optSubscribeExplicitUrl:
          result=createSubscription(cse_root_addr, "http://"+poaAddr+":"+poaPort+"/"); // Include URL in AE resource
          fail |= ! checkResult(passResults, result); 
          break;
        case optAcp:
          result=createAccessControlPolicy(cse_root_addr);
          fail |= ! checkResult(passResults, result); 
          break;
      }
    }
	
  ::onem2m::terminate();
  return outputAns(!fail, printTestRes);
}





