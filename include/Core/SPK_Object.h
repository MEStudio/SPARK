//////////////////////////////////////////////////////////////////////////////////
// SPARK particle engine														//
// Copyright (C) 2008-2011 - Julien Fryer - julienfryer@gmail.com				//
//																				//
// This software is provided 'as-is', without any express or implied			//
// warranty.  In no event will the authors be held liable for any damages		//
// arising from the use of this software.										//
//																				//
// Permission is granted to anyone to use this software for any purpose,		//
// including commercial applications, and to alter it and redistribute it		//
// freely, subject to the following restrictions:								//
//																				//
// 1. The origin of this software must not be misrepresented; you must not		//
//    claim that you wrote the original software. If you use this software		//
//    in a product, an acknowledgment in the product documentation would be		//
//    appreciated but is not required.											//
// 2. Altered source versions must be plainly marked as such, and must not be	//
//    misrepresented as being the original software.							//
// 3. This notice may not be removed or altered from any source distribution.	//
//////////////////////////////////////////////////////////////////////////////////

#ifndef H_SPK_OBJECT
#define H_SPK_OBJECT

#include <string>

#define SPK_START_DESCRIPTION \
\
protected : \
virtual void fillAttributeList(std::vector<IO::Attribute>& attributes) const \
{

#define SPK_PARENT_ATTRIBUTES(ParentName)	ParentName::fillAttributeList(attributes);
#define SPK_ATTRIBUTE(Name,Type)			attributes.push_back(IO::Attribute(Name,IO::Type));

#define SPK_END_DESCRIPTION }

#define SPK_IMPLEMENT_SERIALIZABLE(ClassName) \
private : \
friend class IO::IOManager; \
static ClassName* createSerializable() {return SPK_NEW(ClassName);} \
static std::string getName() {return #ClassName;} \
public : \
virtual std::string getClassName() const { return ClassName::getName(); }

// For templates
#define SPK_DEFINE_DESCRIPTION_TEMPLATE	protected : virtual void fillAttributeList(std::vector<IO::Attribute>& attributes);
#define SPK_START_DESCRIPTION_TEMPLATE(ClassName) \
template<> void ClassName::fillAttributeList(std::vector<IO::Attribute>& attributes) \
{

namespace SPK
{
	class SPK_PREFIX SPKObject
	{
	friend class Transform;

	SPK_START_DESCRIPTION
	SPK_ATTRIBUTE("transform",ATTRIBUTE_TYPE_FLOATS)
	SPK_END_DESCRIPTION

	public :
		
		///////////////
		// Transform //
		///////////////

		inline Transform& getTransform();
		inline const Transform& getTransform() const;

		void updateTransform(const WeakRef<const SPKObject>& parent = SPK_NULL_REF);

		//////////
		// Name //
		//////////

		/**
		* @brief Sets the name of this nameable
		* @param name : the name
		*/
		inline void setName(const std::string& name);

		/**
		* @brief Gets the name of this nameable
		* @return the name
		*/
		inline const std::string& getName() const;
		
		/**
		* @brief Traverses this nameable to find a nameable with the given name
		*
		* The first nameable found with the given name is returned.<br>
		* This nameable is always checked first.<br>
		* If no nameable with the given name is found, null is returned.<br>
		*
		* @param name : the name of the nameable to find
		* @return : the nameable with the given name or null
		*/
		virtual inline WeakRef<SPKObject> findByName(const std::string& name);

		///////////////////
		// Serialization //
		///////////////////

		void importAttributes(const IO::Descriptor& descriptor);
		IO::Descriptor exportAttributes() const;

		virtual std::string getClassName() const { return std::string(); } // TODO Make pure virtual
		
	protected :

		// abstract class
		inline SPKObject() {}
		inline SPKObject(const SPKObject& obj) : 
			name(obj.name),
			transform(obj.transform)
		{}

		/**
		* @brief Updates all the parameters in the world coordinates
		*
		* This method can be overriden in derived classes of SPKObject (By default it does nothing).<br>
		* It is this method task to compute all parameters of the class that are dependent of the world transform.
		*/
		virtual inline void innerUpdateTransform() {}

		/**
		* @brief Propagates the update of the transform to object's children of this object
		*
		* This method can be overriden in derived classes of SPKObject (By default it does nothing).<br>
		* It is this method task to call the updateTransform method of the object's children of this object.
		*/
		virtual inline void propagateUpdateTransform() {}

		inline void transformPos(Vector3D& tPos,const Vector3D& pos);
		inline void transformDir(Vector3D& tDir,const Vector3D& dir);

		virtual void innerImport(const IO::Descriptor& descriptor);
		virtual void innerExport(IO::Descriptor& descriptor) const;

	private :

		std::string name;
		Transform transform;

		IO::Descriptor createDescriptor() const;
	};

	inline Transform& SPKObject::getTransform()
	{
		return transform;
	}

	inline const Transform& SPKObject::getTransform() const
	{
		return transform;
	}

	void SPKObject::setName(const std::string& name)
	{
		this->name = name;
	}

	const std::string& SPKObject::getName() const
	{
		return name;
	}

	WeakRef<SPKObject> SPKObject::findByName(const std::string& name)
	{
		return getName().compare(name) == 0 ? this : NULL;
	}

	inline void SPKObject::transformPos(Vector3D& tPos,const Vector3D& pos)
	{
		transform.transformPos(tPos,pos);
	}

	inline void SPKObject::transformDir(Vector3D& tDir,const Vector3D& dir)
	{
		transform.transformDir(tDir,dir);
	}
}

#endif