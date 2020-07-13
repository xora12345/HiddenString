/*
	Generate a pseudo-random number
*/
#ifndef RANDOM_NUMBER_HPP
#define RANDOM_NUMBER_HPP

#include "Configuration.hpp"

namespace Protector
{
	class RandomNumber
	{
	public:

		constexpr RandomNumber() : m_State{} // Initialize all variables in the "m_State" object to zero
		{
			// Set the state to default
			this->setStateToDefault();
		}

		// Generate a random number
		constexpr unsigned int generateNumber()
		{
			unsigned int T		= {};

			T					= this->m_State.A ^ (this->m_State.A << 0xB);
			this->m_State.A		= this->m_State.B; this->m_State.B = this->m_State.C; this->m_State.C = this->m_State.D;
			this->m_State.D		^= (this->m_State.D >> 0x13) ^ (T ^ (T >> 0x8));

			return T;
		}

		// Generate a random number within a range
		constexpr unsigned int generateNumberInRange(const unsigned int Minimum, const unsigned int Maximum)
		{
			// If the maximum value is zero, exit
			if(!Maximum) return 0;
			// If the maximum value is smaller than the minimum value, exit
			if(Maximum < Minimum) return 0;
			// If the maximum value is equal to the minimum value, exit
			if(Maximum == Minimum) return 0;

			// Generate a random number
			unsigned int Random = this->generateNumber();
			// Put the number within the given range using a modulus algorithm and return it
			return Minimum + (Random % (Maximum - Minimum));
		}

	private:

		// Store the current state of the algorithm used to generate the pseudo-random number (XorShift)
		struct
		{
			unsigned int A, B, C, D;
		} m_State;

		// Set the algorithm's state to the default values
		constexpr void setStateToDefault()
		{
			// The variable "A" of the state is the seed for the random number
			// We will just use a value generated during compilation based on the current time
			this->m_State.A		= StCa(unsigned int, __TIME__[0]) * StCa(unsigned int, __TIME__[1]) * StCa(unsigned int, __TIME__[2])
				* StCa(unsigned int, __TIME__[3]) * StCa(unsigned int, __TIME__[4]);
			this->m_State.B		= 0x159A55E5;
			this->m_State.C		= 0x1F123BB5;
			this->m_State.D		= 0x05491333;
		}
	};
}

#endif
