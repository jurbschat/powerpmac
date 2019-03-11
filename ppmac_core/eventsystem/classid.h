#pragma once 

namespace ppmac
{
	// this works inside clang/g++ in -03 but seems to now in visual studio
	// i am not sure if this is UB or an linker bug

// 	template<typename T>
// 	class ClassID
// 	{
// 	public:
// 		static const uint64_t ID;
// 	};
// 	template<typename T> const uint64_t ClassID<T>::ID = reinterpret_cast<const uint64_t>(&ClassID<T>::ID);

	// visual studio workaround
	template<typename T>
	class ClassID
	{
	private:
		static char _internal_storage;
	public:
		static const uint64_t ID;
	};
	template<typename T> char ClassID<T>::_internal_storage;
	template<typename T> const uint64_t ClassID<T>::ID = reinterpret_cast<const uint64_t>(&ClassID<T>::_internal_storage);
}