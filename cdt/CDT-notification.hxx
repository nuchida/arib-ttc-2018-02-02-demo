// Copyright (c) 2005-2014 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef XSD_V3_2_0_ED_CDT_NOTIFICATION_HXX
#define XSD_V3_2_0_ED_CDT_NOTIFICATION_HXX

#ifndef XSD_CXX11
#define XSD_CXX11
#endif

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 4000000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/parsing/byte.hxx>
#include <xsd/cxx/tree/parsing/unsigned-byte.hxx>
#include <xsd/cxx/tree/parsing/short.hxx>
#include <xsd/cxx/tree/parsing/unsigned-short.hxx>
#include <xsd/cxx/tree/parsing/int.hxx>
#include <xsd/cxx/tree/parsing/unsigned-int.hxx>
#include <xsd/cxx/tree/parsing/long.hxx>
#include <xsd/cxx/tree/parsing/unsigned-long.hxx>
#include <xsd/cxx/tree/parsing/boolean.hxx>
#include <xsd/cxx/tree/parsing/float.hxx>
#include <xsd/cxx/tree/parsing/double.hxx>
#include <xsd/cxx/tree/parsing/decimal.hxx>

#include <xsd/cxx/xml/dom/serialization-header.hxx>
#include <xsd/cxx/tree/serialization.hxx>
#include <xsd/cxx/tree/serialization/byte.hxx>
#include <xsd/cxx/tree/serialization/unsigned-byte.hxx>
#include <xsd/cxx/tree/serialization/short.hxx>
#include <xsd/cxx/tree/serialization/unsigned-short.hxx>
#include <xsd/cxx/tree/serialization/int.hxx>
#include <xsd/cxx/tree/serialization/unsigned-int.hxx>
#include <xsd/cxx/tree/serialization/long.hxx>
#include <xsd/cxx/tree/serialization/unsigned-long.hxx>
#include <xsd/cxx/tree/serialization/boolean.hxx>
#include <xsd/cxx/tree/serialization/float.hxx>
#include <xsd/cxx/tree/serialization/double.hxx>
#include <xsd/cxx/tree/serialization/decimal.hxx>

#include <xsd/cxx/tree/std-ostream-operators.hxx>

namespace xml_schema
{
  // anyType and anySimpleType.
  //
  typedef ::xsd::cxx::tree::type type;
  typedef ::xsd::cxx::tree::simple_type< char, type > simple_type;
  typedef ::xsd::cxx::tree::type container;

  // 8-bit
  //
  typedef signed char byte;
  typedef unsigned char unsigned_byte;

  // 16-bit
  //
  typedef short short_;
  typedef unsigned short unsigned_short;

  // 32-bit
  //
  typedef int int_;
  typedef unsigned int unsigned_int;

  // 64-bit
  //
  typedef long long long_;
  typedef unsigned long long unsigned_long;

  // Supposed to be arbitrary-length integral types.
  //
  typedef long long integer;
  typedef long long non_positive_integer;
  typedef unsigned long long non_negative_integer;
  typedef unsigned long long positive_integer;
  typedef long long negative_integer;

  // Boolean.
  //
  typedef bool boolean;

  // Floating-point types.
  //
  typedef float float_;
  typedef double double_;
  typedef double decimal;

  // String types.
  //
  typedef ::xsd::cxx::tree::string< char, simple_type > string;
  typedef ::xsd::cxx::tree::normalized_string< char, string > normalized_string;
  typedef ::xsd::cxx::tree::token< char, normalized_string > token;
  typedef ::xsd::cxx::tree::name< char, token > name;
  typedef ::xsd::cxx::tree::nmtoken< char, token > nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, simple_type, nmtoken > nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, name > ncname;
  typedef ::xsd::cxx::tree::language< char, token > language;

  // ID/IDREF.
  //
  typedef ::xsd::cxx::tree::id< char, ncname > id;
  typedef ::xsd::cxx::tree::idref< char, ncname, type > idref;
  typedef ::xsd::cxx::tree::idrefs< char, simple_type, idref > idrefs;

  // URI.
  //
  typedef ::xsd::cxx::tree::uri< char, simple_type > uri;

  // Qualified name.
  //
  typedef ::xsd::cxx::tree::qname< char, simple_type, uri, ncname > qname;

  // Binary.
  //
  typedef ::xsd::cxx::tree::buffer< char > buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, simple_type > base64_binary;
  typedef ::xsd::cxx::tree::hex_binary< char, simple_type > hex_binary;

  // Date/time.
  //
  typedef ::xsd::cxx::tree::time_zone time_zone;
  typedef ::xsd::cxx::tree::date< char, simple_type > date;
  typedef ::xsd::cxx::tree::date_time< char, simple_type > date_time;
  typedef ::xsd::cxx::tree::duration< char, simple_type > duration;
  typedef ::xsd::cxx::tree::gday< char, simple_type > gday;
  typedef ::xsd::cxx::tree::gmonth< char, simple_type > gmonth;
  typedef ::xsd::cxx::tree::gmonth_day< char, simple_type > gmonth_day;
  typedef ::xsd::cxx::tree::gyear< char, simple_type > gyear;
  typedef ::xsd::cxx::tree::gyear_month< char, simple_type > gyear_month;
  typedef ::xsd::cxx::tree::time< char, simple_type > time;

  // Entity.
  //
  typedef ::xsd::cxx::tree::entity< char, ncname > entity;
  typedef ::xsd::cxx::tree::entities< char, simple_type, entity > entities;

  typedef ::xsd::cxx::tree::content_order content_order;
  // Namespace information and list stream. Used in
  // serialization functions.
  //
  typedef ::xsd::cxx::xml::dom::namespace_info< char > namespace_info;
  typedef ::xsd::cxx::xml::dom::namespace_infomap< char > namespace_infomap;
  typedef ::xsd::cxx::tree::list_stream< char > list_stream;
  typedef ::xsd::cxx::tree::as_double< double_ > as_double;
  typedef ::xsd::cxx::tree::as_decimal< decimal > as_decimal;
  typedef ::xsd::cxx::tree::facet facet;

  // Flags and properties.
  //
  typedef ::xsd::cxx::tree::flags flags;
  typedef ::xsd::cxx::tree::properties< char > properties;

  // Parsing/serialization diagnostics.
  //
  typedef ::xsd::cxx::tree::severity severity;
  typedef ::xsd::cxx::tree::error< char > error;
  typedef ::xsd::cxx::tree::diagnostics< char > diagnostics;

  // Exceptions.
  //
  typedef ::xsd::cxx::tree::exception< char > exception;
  typedef ::xsd::cxx::tree::bounds< char > bounds;
  typedef ::xsd::cxx::tree::duplicate_id< char > duplicate_id;
  typedef ::xsd::cxx::tree::parsing< char > parsing;
  typedef ::xsd::cxx::tree::expected_element< char > expected_element;
  typedef ::xsd::cxx::tree::unexpected_element< char > unexpected_element;
  typedef ::xsd::cxx::tree::expected_attribute< char > expected_attribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > unexpected_enumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > expected_text_content;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > no_prefix_mapping;
  typedef ::xsd::cxx::tree::serialization< char > serialization;

  // Error handler callback interface.
  //
  typedef ::xsd::cxx::xml::error_handler< char > error_handler;

  // DOM interaction.
  //
  namespace dom
  {
    // Automatic pointer for DOMDocument.
    //
    using ::xsd::cxx::xml::dom::unique_ptr;

#ifndef XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
    // DOM user data key for back pointers to tree nodes.
    //
    const XMLCh* const tree_node_key = ::xsd::cxx::tree::user_data_keys::node;
#endif
  }
}

// Forward declarations.
//
namespace onem2m
{
  class notification;
  class notificationEvent;
  class operationMonitor;
}


#include <memory>    // ::std::unique_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search
#include <utility>   // std::move

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

#include <xsd/cxx/tree/containers-wildcard.hxx>

#include "CDT-commonTypes.hxx"

namespace onem2m
{
  class notification: public ::xml_schema::type
  {
    public:
    // notificationEvent
    //
    typedef ::onem2m::notificationEvent notificationEvent_type;
    typedef ::xsd::cxx::tree::optional< notificationEvent_type > notificationEvent_optional;
    typedef ::xsd::cxx::tree::traits< notificationEvent_type, char > notificationEvent_traits;

    const notificationEvent_optional&
    notificationEvent () const;

    notificationEvent_optional&
    notificationEvent ();

    void
    notificationEvent (const notificationEvent_type& x);

    void
    notificationEvent (const notificationEvent_optional& x);

    void
    notificationEvent (::std::unique_ptr< notificationEvent_type > p);

    // verificationRequest
    //
    typedef ::xml_schema::boolean verificationRequest_type;
    typedef ::xsd::cxx::tree::optional< verificationRequest_type > verificationRequest_optional;
    typedef ::xsd::cxx::tree::traits< verificationRequest_type, char > verificationRequest_traits;

    const verificationRequest_optional&
    verificationRequest () const;

    verificationRequest_optional&
    verificationRequest ();

    void
    verificationRequest (const verificationRequest_type& x);

    void
    verificationRequest (const verificationRequest_optional& x);

    // subscriptionDeletion
    //
    typedef ::xml_schema::boolean subscriptionDeletion_type;
    typedef ::xsd::cxx::tree::optional< subscriptionDeletion_type > subscriptionDeletion_optional;
    typedef ::xsd::cxx::tree::traits< subscriptionDeletion_type, char > subscriptionDeletion_traits;

    const subscriptionDeletion_optional&
    subscriptionDeletion () const;

    subscriptionDeletion_optional&
    subscriptionDeletion ();

    void
    subscriptionDeletion (const subscriptionDeletion_type& x);

    void
    subscriptionDeletion (const subscriptionDeletion_optional& x);

    // subscriptionReference
    //
    typedef ::xml_schema::uri subscriptionReference_type;
    typedef ::xsd::cxx::tree::optional< subscriptionReference_type > subscriptionReference_optional;
    typedef ::xsd::cxx::tree::traits< subscriptionReference_type, char > subscriptionReference_traits;

    const subscriptionReference_optional&
    subscriptionReference () const;

    subscriptionReference_optional&
    subscriptionReference ();

    void
    subscriptionReference (const subscriptionReference_type& x);

    void
    subscriptionReference (const subscriptionReference_optional& x);

    void
    subscriptionReference (::std::unique_ptr< subscriptionReference_type > p);

    // creator
    //
    typedef ::onem2m::ID creator_type;
    typedef ::xsd::cxx::tree::optional< creator_type > creator_optional;
    typedef ::xsd::cxx::tree::traits< creator_type, char > creator_traits;

    const creator_optional&
    creator () const;

    creator_optional&
    creator ();

    void
    creator (const creator_type& x);

    void
    creator (const creator_optional& x);

    void
    creator (::std::unique_ptr< creator_type > p);

    // notificationForwardingURI
    //
    typedef ::xml_schema::uri notificationForwardingURI_type;
    typedef ::xsd::cxx::tree::optional< notificationForwardingURI_type > notificationForwardingURI_optional;
    typedef ::xsd::cxx::tree::traits< notificationForwardingURI_type, char > notificationForwardingURI_traits;

    const notificationForwardingURI_optional&
    notificationForwardingURI () const;

    notificationForwardingURI_optional&
    notificationForwardingURI ();

    void
    notificationForwardingURI (const notificationForwardingURI_type& x);

    void
    notificationForwardingURI (const notificationForwardingURI_optional& x);

    void
    notificationForwardingURI (::std::unique_ptr< notificationForwardingURI_type > p);

    // Constructors.
    //
    notification ();

    notification (const ::xercesc::DOMElement& e,
                  ::xml_schema::flags f = 0,
                  ::xml_schema::container* c = 0);

    notification (const notification& x,
                  ::xml_schema::flags f = 0,
                  ::xml_schema::container* c = 0);

    virtual notification*
    _clone (::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0) const;

    notification&
    operator= (const notification& x);

    virtual 
    ~notification ();

    // Implementation.
    //
    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::flags);

    protected:
    notificationEvent_optional notificationEvent_;
    verificationRequest_optional verificationRequest_;
    subscriptionDeletion_optional subscriptionDeletion_;
    subscriptionReference_optional subscriptionReference_;
    creator_optional creator_;
    notificationForwardingURI_optional notificationForwardingURI_;
  };

  class notificationEvent: public ::xml_schema::type
  {
    public:
    // representation
    //
    typedef ::xml_schema::type representation_type;
    typedef ::xsd::cxx::tree::optional< representation_type > representation_optional;
    typedef ::xsd::cxx::tree::traits< representation_type, char > representation_traits;

    const representation_optional&
    representation () const;

    representation_optional&
    representation ();

    void
    representation (const representation_type& x);

    void
    representation (const representation_optional& x);

    void
    representation (::std::unique_ptr< representation_type > p);

    // operationMonitor
    //
    typedef ::onem2m::operationMonitor operationMonitor_type;
    typedef ::xsd::cxx::tree::optional< operationMonitor_type > operationMonitor_optional;
    typedef ::xsd::cxx::tree::traits< operationMonitor_type, char > operationMonitor_traits;

    const operationMonitor_optional&
    operationMonitor () const;

    operationMonitor_optional&
    operationMonitor ();

    void
    operationMonitor (const operationMonitor_type& x);

    void
    operationMonitor (const operationMonitor_optional& x);

    void
    operationMonitor (::std::unique_ptr< operationMonitor_type > p);

    // notificationEventType
    //
    typedef ::onem2m::notificationEventType notificationEventType_type;
    typedef ::xsd::cxx::tree::optional< notificationEventType_type > notificationEventType_optional;
    typedef ::xsd::cxx::tree::traits< notificationEventType_type, char > notificationEventType_traits;

    const notificationEventType_optional&
    notificationEventType () const;

    notificationEventType_optional&
    notificationEventType ();

    void
    notificationEventType (const notificationEventType_type& x);

    void
    notificationEventType (const notificationEventType_optional& x);

    void
    notificationEventType (::std::unique_ptr< notificationEventType_type > p);

    // Constructors.
    //
    notificationEvent ();

    notificationEvent (const ::xercesc::DOMElement& e,
                       ::xml_schema::flags f = 0,
                       ::xml_schema::container* c = 0);

    notificationEvent (const notificationEvent& x,
                       ::xml_schema::flags f = 0,
                       ::xml_schema::container* c = 0);

    virtual notificationEvent*
    _clone (::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0) const;

    notificationEvent&
    operator= (const notificationEvent& x);

    virtual 
    ~notificationEvent ();

    // Implementation.
    //
    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::flags);

    protected:
    representation_optional representation_;
    operationMonitor_optional operationMonitor_;
    notificationEventType_optional notificationEventType_;
  };

  class operationMonitor: public ::xml_schema::type
  {
    public:
    // operation
    //
    typedef ::onem2m::operation operation_type;
    typedef ::xsd::cxx::tree::optional< operation_type > operation_optional;
    typedef ::xsd::cxx::tree::traits< operation_type, char > operation_traits;

    const operation_optional&
    operation () const;

    operation_optional&
    operation ();

    void
    operation (const operation_type& x);

    void
    operation (const operation_optional& x);

    void
    operation (::std::unique_ptr< operation_type > p);

    // originator
    //
    typedef ::onem2m::ID originator_type;
    typedef ::xsd::cxx::tree::optional< originator_type > originator_optional;
    typedef ::xsd::cxx::tree::traits< originator_type, char > originator_traits;

    const originator_optional&
    originator () const;

    originator_optional&
    originator ();

    void
    originator (const originator_type& x);

    void
    originator (const originator_optional& x);

    void
    originator (::std::unique_ptr< originator_type > p);

    // Constructors.
    //
    operationMonitor ();

    operationMonitor (const ::xercesc::DOMElement& e,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

    operationMonitor (const operationMonitor& x,
                      ::xml_schema::flags f = 0,
                      ::xml_schema::container* c = 0);

    virtual operationMonitor*
    _clone (::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0) const;

    operationMonitor&
    operator= (const operationMonitor& x);

    virtual 
    ~operationMonitor ();

    // Implementation.
    //
    protected:
    void
    parse (::xsd::cxx::xml::dom::parser< char >&,
           ::xml_schema::flags);

    protected:
    operation_optional operation_;
    originator_optional originator_;
  };
}

#include <iosfwd>

namespace onem2m
{
  ::std::ostream&
  operator<< (::std::ostream&, const notification&);

  ::std::ostream&
  operator<< (::std::ostream&, const notificationEvent&);

  ::std::ostream&
  operator<< (::std::ostream&, const operationMonitor&);
}

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

namespace onem2m
{
  // Parse a URI or a local file.
  //

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (const ::std::string& uri,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (const ::std::string& uri,
                 ::xml_schema::error_handler& eh,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (const ::std::string& uri,
                 ::xercesc::DOMErrorHandler& eh,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  // Parse std::istream.
  //

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::std::istream& is,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::std::istream& is,
                 ::xml_schema::error_handler& eh,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::std::istream& is,
                 ::xercesc::DOMErrorHandler& eh,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::std::istream& is,
                 const ::std::string& id,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::std::istream& is,
                 const ::std::string& id,
                 ::xml_schema::error_handler& eh,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::std::istream& is,
                 const ::std::string& id,
                 ::xercesc::DOMErrorHandler& eh,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  // Parse xercesc::InputSource.
  //

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::xercesc::InputSource& is,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::xercesc::InputSource& is,
                 ::xml_schema::error_handler& eh,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::xercesc::InputSource& is,
                 ::xercesc::DOMErrorHandler& eh,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  // Parse xercesc::DOMDocument.
  //

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (const ::xercesc::DOMDocument& d,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());

  ::std::unique_ptr< ::onem2m::notification >
  notification_ (::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument > d,
                 ::xml_schema::flags f = 0,
                 const ::xml_schema::properties& p = ::xml_schema::properties ());
}

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

namespace onem2m
{
  // Serialize to std::ostream.
  //

  void
  notification_ (::std::ostream& os,
                 const ::onem2m::notification& x, 
                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                 const ::std::string& e = "UTF-8",
                 ::xml_schema::flags f = 0);

  void
  notification_ (::std::ostream& os,
                 const ::onem2m::notification& x, 
                 ::xml_schema::error_handler& eh,
                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                 const ::std::string& e = "UTF-8",
                 ::xml_schema::flags f = 0);

  void
  notification_ (::std::ostream& os,
                 const ::onem2m::notification& x, 
                 ::xercesc::DOMErrorHandler& eh,
                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                 const ::std::string& e = "UTF-8",
                 ::xml_schema::flags f = 0);

  // Serialize to xercesc::XMLFormatTarget.
  //

  void
  notification_ (::xercesc::XMLFormatTarget& ft,
                 const ::onem2m::notification& x, 
                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                 const ::std::string& e = "UTF-8",
                 ::xml_schema::flags f = 0);

  void
  notification_ (::xercesc::XMLFormatTarget& ft,
                 const ::onem2m::notification& x, 
                 ::xml_schema::error_handler& eh,
                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                 const ::std::string& e = "UTF-8",
                 ::xml_schema::flags f = 0);

  void
  notification_ (::xercesc::XMLFormatTarget& ft,
                 const ::onem2m::notification& x, 
                 ::xercesc::DOMErrorHandler& eh,
                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                 const ::std::string& e = "UTF-8",
                 ::xml_schema::flags f = 0);

  // Serialize to an existing xercesc::DOMDocument.
  //

  void
  notification_ (::xercesc::DOMDocument& d,
                 const ::onem2m::notification& x,
                 ::xml_schema::flags f = 0);

  // Serialize to a new xercesc::DOMDocument.
  //

  ::xml_schema::dom::unique_ptr< ::xercesc::DOMDocument >
  notification_ (const ::onem2m::notification& x, 
                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                 ::xml_schema::flags f = 0);

  void
  operator<< (::xercesc::DOMElement&, const notification&);

  void
  operator<< (::xercesc::DOMElement&, const notificationEvent&);

  void
  operator<< (::xercesc::DOMElement&, const operationMonitor&);
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // XSD_V3_2_0_ED_CDT_NOTIFICATION_HXX
