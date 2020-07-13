#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <Windows.h>
#include <intrin.h>
#include <iostream>
#include <vector>
#include <string>

// Quicker version of reinterpret_cast
#define ReCa(Type, Object) reinterpret_cast<Type>(Object)

// Quicker version of static_cast
#define StCa(Type, Object) static_cast<Type>(Object)

// Set a local object to 0. 
#define ZERO(Object) (memset(&Object, 0, sizeof(Object)))

// Set a referenced object to 0.
#define ZERO_REF(Object) (memset(Object, 0, sizeof(*Object)))

// Initialize an object to 0.
#define INIT_ZERO(Type, Name) (Type Name; ZERO(Name))

#endif
