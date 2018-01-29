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

int main (int argc, char* argv[]) {

  ::onem2m::initialize();

  // For Eclipse OM2M default install
  ::onem2m::setHostName("192.168.179.4:8080");
  ::onem2m::setFrom("admin:admin");
  ::onem2m::setProtocol( ::onem2m::protocolXml);
  ::std::string cse_root_addr = "/in-cse/in-name/receiver-demo-ae/led_status/la"; // SP-Relative address

  long result;
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;
  
   // *** Retrieve a resource ***
  respObj = ::oneM2M::retrieveResource(cse_root_addr, "1234", result, respObjType);
  std::cout << "Retrieve result:" << result << "\n";  
  outputObject( respObjType, respObj.get()); 

 ::onem2m::terminate();

}
