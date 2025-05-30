/*
 Derived from source code of TrueCrypt 7.1a, which is
 Copyright (c) 2008-2012 TrueCrypt Developers Association and which is governed
 by the TrueCrypt License 3.0.

 Modifications and additions to the original source code (contained in this file)
 and all other portions of this file are Copyright (c) 2013-2025 AM Crypto
 and are governed by the Apache License 2.0 the full text of which is
 contained in the file License.txt included in VeraCrypt binary and source
 code distribution packages.
*/

#ifndef TC_HEADER_Platform_SerializerFactory
#define TC_HEADER_Platform_SerializerFactory

#include <typeinfo>
#include "PlatformBase.h"
#include "StringConverter.h"

namespace VeraCrypt
{
	class Serializable;

	class SerializerFactory
	{
	public:
		~SerializerFactory ();

		static void Deinitialize ();
		static string GetName (const type_info &typeInfo);
		static Serializable *GetNewSerializable (const string &typeName);
		static void Initialize ();

		struct MapEntry
		{
			MapEntry () { }
			MapEntry (const string &typeName, Serializable* (*getNewPtr) ())
				: TypeName (typeName), GetNewPtr (getNewPtr) { }

			MapEntry &operator= (const MapEntry &right)
			{
				TypeName = right.TypeName;
				GetNewPtr = right.GetNewPtr;
				return *this;
			}

			string TypeName;
			Serializable* (*GetNewPtr) ();
		};

		static map <string, MapEntry> *NameToTypeMap;
		static map <string, string> *TypeToNameMap;

	protected:
		SerializerFactory ();

		static int UseCount;
	};

}

#define TC_SERIALIZER_FACTORY_ADD_EXCEPTION_SET(TYPE) \
	struct TYPE##SerializerFactoryInitializer \
	{ \
		TYPE##SerializerFactoryInitializer () \
		{ \
			SerializerFactory::Initialize(); \
			TC_EXCEPTION_SET; \
		} \
		~TYPE##SerializerFactoryInitializer () \
		{ \
			SerializerFactory::Deinitialize(); \
		} \
	}; \
	static TYPE##SerializerFactoryInitializer TYPE##SerializerFactoryInitializer

#define TC_SERIALIZER_FACTORY_ADD_CLASS(TYPE) \
	struct TYPE##SerializerFactoryInitializer \
	{ \
		TYPE##SerializerFactoryInitializer () \
		{ \
			SerializerFactory::Initialize(); \
			TC_SERIALIZER_FACTORY_ADD (TYPE); \
		} \
		~TYPE##SerializerFactoryInitializer () \
		{ \
			SerializerFactory::Deinitialize(); \
		} \
	}; \
	static TYPE##SerializerFactoryInitializer TYPE##SerializerFactoryInitializerInst

#define TC_SERIALIZER_FACTORY_ADD(TYPE) \
	(*SerializerFactory::NameToTypeMap)[#TYPE] = SerializerFactory::MapEntry (StringConverter::GetTypeName (typeid (TYPE)), &TYPE::GetNewSerializable); \
	(*SerializerFactory::TypeToNameMap)[StringConverter::GetTypeName (typeid (TYPE))] = #TYPE


#endif // TC_HEADER_Platform_SerializerFactory
