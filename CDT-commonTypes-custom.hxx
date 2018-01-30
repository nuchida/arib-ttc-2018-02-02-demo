/* 
 *	SPDX-License-Identifier:	BSD-3-Clause 
 * The above license addresses copyright obligations. Please refer to Section 10.4 of the 
 * ATIS Operating Procedures for information about patent licensing obligations under 
 * ATIS' Intellectual Property Rights Policy.
 */

#include "cdt/CDT-AE.hxx"
#include "cdt/CDT-contentInstance.hxx"
#include "cdt/CDT-container.hxx"
#include "cdt/CDT-subscription.hxx"
#include "cdt/CDT-pollingChannel.hxx"
#include "cdt/CDT-accessControlPolicy.hxx"

namespace onem2m
{
	class primitiveContent: public primitiveContentBase
	{
	public:
	 primitiveContent ();
// This constructor is not defined if polymorphism is on
 	primitiveContent (const ::xercesc::DOMElement& e,
                          ::xml_schema::flags f = 0,
                          ::xml_schema::container* c = 0);

	primitiveContent (const primitiveContent& x,
                          ::xml_schema::flags f = 0,
                          ::xml_schema::container* c = 0);

    	virtual primitiveContent*
    	_clone (::xml_schema::flags f = 0,
            ::xml_schema::container* c = 0) const;


	public:
	 void setPrimitiveContent( const ::onem2m::AE& );

	public:
	 void setPrimitiveContent( const ::onem2m::contentInstance& );

	public:
	 void setPrimitiveContent( const ::onem2m::container& );

	public:
	 void setPrimitiveContent( const ::onem2m::subscription& );

	public:
	 void setPrimitiveContent( const ::onem2m::pollingChannel& );

        public:
         void setPrimitiveContent( const ::onem2m::accessControlPolicy& );


	};
}
