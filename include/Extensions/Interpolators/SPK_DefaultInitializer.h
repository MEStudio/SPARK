//////////////////////////////////////////////////////////////////////////////////
// SPARK particle engine														//
// Copyright (C) 2008-2010 - Julien Fryer - julienfryer@gmail.com				//
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

#ifndef H_SPK_DEFAULTINITIALIZER
#define H_SPK_DEFAULTINITIALIZER

#include "Core/SPK_Interpolator.h"

namespace SPK
{
	template<typename T>
	class DefaultInitializer : public Interpolator<T>
	{
	SPK_IMPLEMENT_REGISTERABLE(DefaultInitializer<T>);

	public :

		static inline DefaultInitializer<T>* create(const T& value);

		inline void setDefaultValue(const T& value);
		inline const T& getDefaultValue() const;

	private :

		T defaultValue;

		DefaultInitializer<T>(const T& value);

		virtual inline void interpolate(T* data,Group& group,DataSet* dataSet) const {}
		virtual inline void init(T& data,Particle& particle,DataSet* dataSet) const;
	};

	typedef DefaultInitializer<Color> ColorDefaultInitializer;
	typedef DefaultInitializer<float> FloatDefaultInitializer;

	template<typename T>
	DefaultInitializer<T>::DefaultInitializer(const T& value) :
		Interpolator(false),
		defaultValue(value)
	{}

	template<typename T>
	inline DefaultInitializer<T>* DefaultInitializer<T>::create(const T& value)
	{
		return new DefaultInitializer<T>(value);
	}

	template<typename T>
	inline void DefaultInitializer<T>::setDefaultValue(const T& value)
	{
		defaultValue = value;
	}

	template<typename T>
	inline const T& DefaultInitializer<T>::getDefaultValue() const
	{
		return defaultValue;
	}

	template<typename T>
	inline void DefaultInitializer<T>::init(T& data,Particle& particle,DataSet* dataSet) const
	{
		data = defaultValue;
	}
}

#endif