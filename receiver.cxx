#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
extern "C" {
  #include <unistd.h>

  #include <gpio.h>
}

#include "onem2m.hxx"
using namespace ::onem2m;
#define LED "GPIO-A"

::std::string cse_root_addr = "/in-cse/in-name"; // SP-Relative address
::std::string receiver_ae_name="receiver-demo-ae";
::std::string container_name="led_status";
::std::string subscription_name="receiver-subscription";
::std::string server_addr;
::std::string my_addr;

void readSettings(::std::string& server_addr, ::std::string& my_addr) {
  std::ifstream infile("receiver_settings.txt");
  ::std::getline(infile, server_addr);
  ::std::getline(infile, my_addr);
  infile.close();
}

long createAE(const ::std::string & cse_root_addr, const std::string & receiver_ae_name, const std::string & my_addr) {
  long result;
  long del_result;
  std::unique_ptr< ::xml_schema::type > respObj;
  ::xml_schema::integer respObjType;

  respObj = ::onem2m::retrieveResource(cse_root_addr+"/"+receiver_ae_name, "1234", result, respObjType);
  std::cout << "Retrieve AE result:" << result <<  std::endl;
  std::cout << "Obj Type#:" << respObjType << std::endl;

  if (result==onem2m::onem2mHttpOK) // Delete any previous AE
    ::onem2m::deleteResource(cse_root_addr+"/"+receiver_ae_name, "1234", del_result, respObjType);

  if (result==onem2m::onem2mHttpNOT_FOUND || result==onem2m::onem2mHttpOK) {
    auto ae = ::onem2m::AE();
    ae.resourceName(receiver_ae_name);
    ae.App_ID("receiver-app");
    ae.requestReachability(true);
    auto lb = ::onem2m::labels ();
    lb.push_back("Type/actuator");
    lb.push_back("Category/led");
    ae.labels(lb);
    auto poal =  onem2m::poaList(onem2m::poaList_base(1, my_addr));
    ae.pointOfAccess( poal );
    respObj = ::onem2m::createResource(cse_root_addr, "1234", ae, result, respObjType);  
    std::cout << "Create AE result:" << result << "\n";
  }
  return result;
}

long createContainer(const ::std::string & ae_addr, const std::string & container_name) {
  long result;
  std::unique_ptr< ::xml_schema::type > respObj;
  ::xml_schema::integer respObjType;

  auto c = ::onem2m::container();
  c.resourceName(container_name);
  respObj = ::onem2m::createResource(ae_addr, "1234", c, result, respObjType);  
  std::cout << "Create container result:" << result << "\n";
  return result;
}

long createSubscription (const ::std::string & object_address, const std::string & ae_address, const ::std::string & subscription_name) {
  long result;
  
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;
  auto sub = ::onem2m::subscription();
  auto uris = ::onem2m::listOfURIs();
  auto criteria = ::onem2m::eventNotificationCriteria();
  // If the complexType is declared in-line in the XSD file then the CodeSynthesis compiler generates an
  // automatically named type within the parent class - see example below
  auto events = ::onem2m::eventNotificationCriteria::notificationEventType_sequence();

  sub.resourceName(subscription_name);
  events.push_back( ::onem2m::updateOfResource ); // Add one notification case to the list of notification events
  criteria.notificationEventType(events); // Assign the list of events to the criteria
  sub.eventNotificationCriteria(criteria); // Assign the criteria to the subscription
  uris.push_back(ae_address); // Add one notification URI
  sub.notificationURI(uris);
  sub.notificationContentType(nctAllAttributes);
  sub.latestNotify(true);
  respObj = ::onem2m::createResource(object_address, "1234", sub, result, respObjType);   
  std::cout << "Create subscription result:" << result << "\n";
  return result;
}

onem2m::onem2mResult processNotification(std::string host, std::string & from, ::onem2m::notification* notif ) {
    // Callback routine which is passed to onem2m::startHttpServer() and called when a notification is received.
    // This callback will occur in a separate thread to the main program.

    // This callback should check if the notification is a "verification request" (see code below) and respond appropriately if so.
    // This callback should also implement any application specific processing for notifications that are not verification requests.
 
    // On entry, the "host" parameter contains the "Host:" header from the HTTP request (i.e. the oneM2M "to" parameter)
    // the "from" parameter contains the "X-M2M-Origin:" header from the HTTP request (i.e. the oneM2M "from" parameter)
    // the "notif" parameter contains a pointer to a onem2m::notification object that represents the contents of the notification.

    // The value in "from" on return will be encoded in to the "X-M2M-Origin:" HTTP header of the response - ie will become the
    // "from" parameter of the primitiveResponse.
    // The return value should be an HTTP response code - eg onem2m::onem2mHttpOK for an "OK" response

  if (notif->verificationRequest().present () && notif->verificationRequest().get()) { // Check if this is a vefification request
    // Whether to accept the verificationRequest could be decided here, e.g. by checking the "host" and "from" parameters.
    // In this implmentation we accept all verification requests.
    
    std::cout << "Notification verification from:" << from << "r\n" ;
    from = onem2m::getFrom();
    return onem2m::onem2mHttpOK;
  }
  
  std::unique_ptr< ::xml_schema::type > respObj;
  ::xml_schema::integer respObjType;
  ::xml_schema::type * respObjPtr;
  respObjPtr = notif -> getRepresentationObject( respObjType ); // notif is a pointer to the notification object
    if (respObjType == resourceTypeContentInstance) {
	    auto ciPtr = static_cast< const contentInstance* >(respObjPtr);
 		std::cout << "contentInstance with content:" << ciPtr-> content () << "\r\n";	
  	if (ciPtr->content().present ()) {
  		std::cout << "Content returned:" << ciPtr-> content () . get() << "\n";
  		if (ciPtr-> content () . get()=="1")
        		digitalWrite(gpio_id(LED), HIGH);
    		else
     		digitalWrite(gpio_id(LED), LOW);
	}
 }

  return onem2m::onem2mHttpOK;

}


void startServer () {
  // Start an HTTP server
  ::onem2m::startHttpServer({"^.*$"},18888, &processNotification);
}


int main (int argc, char* argv[]) {

  if(gpio_open(gpio_id(LED), "out")){
    return (-1);
  }

  readSettings(server_addr, my_addr);
  std::cout << "Server address: "<<server_addr<<std::endl;
  ::onem2m::initialize();

  // For Eclipse OM2M default install
  ::onem2m::setHostName(server_addr);
  ::onem2m::setFrom("admin:admin");
  ::onem2m::setProtocol( ::onem2m::protocolXml);

  long result;

  startServer();
 
  result = createAE(cse_root_addr, receiver_ae_name, my_addr);
  std::cout<< "Create AE function result: " << result << std::endl;
  result = createContainer(cse_root_addr+"/"+receiver_ae_name, container_name);
  std::cout<< "Create Container function result: " << result << std::endl;
  result = createSubscription(cse_root_addr+"/"+receiver_ae_name+"/"+container_name, cse_root_addr+"/"+receiver_ae_name ,subscription_name);
  std::cout<< "Create Subscription function result: " << result << std::endl;

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
   }




  ::onem2m::terminate();

}
