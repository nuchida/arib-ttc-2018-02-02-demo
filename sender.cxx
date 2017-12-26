#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>

extern "C" {
  #include <unistd.h>
  #include <gpio.h>
}

#include "onem2m.hxx"

#define BUTTON "GPIO-A"

void readSettings(::std::string& server_addr) {
  std::ifstream infile("sender_settings.txt");
  ::std::getline(infile, server_addr);
  infile.close();
}

long write_contentInstance(const std::string& address, const std::string value) {
  long result;
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;
  
  auto ci = ::onem2m::contentInstance();
  ci.contentInfo("application/text");
  ci.content (value);
  respObj = ::onem2m::createResource(address, "1234", ci, result, respObjType); 
  std::cout << "Create content instance result:" << result << "\n";
  return result;
} 

int main (int argc, char* argv[]) {

  if (gpio_open(gpio_id(BUTTON), "in")){
    return(-1);
  }

  ::onem2m::initialize();

  ::std::string server_addr;
  readSettings(server_addr);
  ::onem2m::setHostName(server_addr);
  ::std::string cse_root_addr = "/in-cse/in-name"; // SP-Relative address
  ::std::string ae_name="demo-ae";
  ::std::string container_name="receiver-1";
  ::onem2m::setFrom("admin:admin");
  ::onem2m::setProtocol( ::onem2m::protocolXml);

  long result;
  ::xml_schema::integer respObjType;
  std::unique_ptr< ::xml_schema::type > respObj;
  

   // *** Wait for an AE and Container to be created ***
  while (true) {
    respObj = ::onem2m::retrieveResource(cse_root_addr+"/"+ae_name, "1234", result, respObjType);
    std::cout << "Retrieve AE result:" << result <<  std::endl;
    std::cout << "Obj Type#:" << respObjType << std::endl;
    if (result==200) {
      respObj = ::onem2m::retrieveResource(cse_root_addr+"/"+ae_name+"/"+container_name, "1234", result, respObjType);
      std::cout << "Retrieve container result:" << result << std::endl;
      if (result==200) 
        break;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Found AE and contaier" << std::endl;

/*
  ::std::string input_line;

  while (true) {
    ::std::getline(std::cin, input_line);
    if (input_line == "q")
      break;
    ::std::cout << "Input: " << input_line << std::endl;
    write_contentInstance(cse_root_addr+"/"+ae_name+"/"+container_name, input_line);
  }
*/

  int t = 0;
  int last_t = 0;
  int value = 0;
  ::std::string strValue;
  while (true) {
    	t = digitalRead(gpio_id(BUTTON));
    if (t && !last_t){
      value = (value+1) % 2;
      ::std::cout << "Value: " << value << std::endl;
      strValue=std::to_string( value );
      write_contentInstance(cse_root_addr+"/"+ae_name+"/"+container_name, strValue);
      usleep(100000);
    }
    last_t = t;
    usleep(1);
  }


  ::onem2m::terminate();

}
