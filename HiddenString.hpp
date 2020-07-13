/*
	Create a string that is not visible in the binary
*/
#ifndef HIDDEN_STRING_HPP
#define HIDDEN_STRING_HPP

#include "Configuration.hpp"
#include "RandomNumber.hpp"

namespace Protector
{
	class HiddenString
	{
	public:

		// Create a constructor that takes in an UNICODE string
		template<int NumberOfCharacters>
		constexpr HiddenString(wchar_t(&String)[NumberOfCharacters]) : m_Buffer{}, m_CharacterCount{}, m_RandomNumber{}, m_Key{} // Initialize all members to zero
		{
			// If the reference to the string is invalid, exit
			if(!String) return;
			// If there are no characters in the string, exit
			if(!NumberOfCharacters) return;

			// Store the character count
			this->m_CharacterCount = NumberOfCharacters;

			// Generate and store a pseudo-random key
			this->generateAndStoreKey();
			// Encrypt and store the string
			this->encryptAndStoreString(String);
			// Erase the original string
			this->eraseOriginalString(String);

			// Decrypt the string
			this->decryptAndStore();
		}

		~HiddenString()
		{
			// Erase and deallocate the decrypted string
			this->eraseAndDeallocateDecryptedBuffer();
		}

		// Call overloaded operator to retrieve the decrypted string
		const wchar_t * operator()() { return this->m_DecryptedBuffer; }
		// Return type overloaded operator to retrieve the decrypted string
		operator const wchar_t * () { return this->m_DecryptedBuffer; }

	private:

		// Buffer that stores the encrypted string
		wchar_t			m_Buffer[MAX_PATH];
		// The number of characters stored in the buffer
		int				m_CharacterCount;
		// RandomNumber instance for pseudo-random number generation
		RandomNumber	m_RandomNumber;
		// XOR encryption key
		unsigned int	m_Key;
		// UNICODE string for the decrypted string
		wchar_t *		m_DecryptedBuffer;

		// Generate and store a random key
		constexpr void generateAndStoreKey()
		{
			// If the key was already generated, exit
			if(this->m_Key) return;

			this->m_Key = this->m_RandomNumber.generateNumber();
		}

		// Encrypt the original string and store inside the local buffer
		template<int NumberOfCharacters>
		constexpr void encryptAndStoreString(wchar_t(&String)[NumberOfCharacters])
		{
			// If the key was not generated, exit
			if(!this->m_Key) return;
			// If the reference to the string is invalid, exit
			if(!String) return;
			// If there are no characters in the string, exit
			if(!NumberOfCharacters) return;
			
			int CharacterCount = NumberOfCharacters;

			// If there are more characters than the local buffer can store, adjust it to the maximum possible size
			if(NumberOfCharacters > MAX_PATH) CharacterCount = MAX_PATH - 1;

			// Go trough each one of the characters in the string
			for(int i ={}; i < CharacterCount; ++i) {
				// Encrypt and store the current character into the local buffer
				this->m_Buffer[i] = String[i] ^ this->m_Key;
			}
		}
		
		// Erase the original string
		template<int NumberOfCharacters>
		constexpr void eraseOriginalString(wchar_t(&String)[NumberOfCharacters])
		{
			// If the reference to the string is invalid, exit
			if(!String) return;
			// If there are no characters in the string, exit
			if(!NumberOfCharacters) return;
			
			// Go trough each one of the characters in the string
			for(int i ={}; i < NumberOfCharacters; ++i) {
				// Set the current character to the NULL terminator
				String[i] = L'\0';
			}
		}

		// Decrypt the local buffer and store
		void decryptAndStore()
		{
			// Allocate memory for the decrypted buffer
			this->m_DecryptedBuffer = new wchar_t[this->m_CharacterCount];

			// Go trough each one of the characters in the buffer and decrypt it
			for(int i ={}; i < this->m_CharacterCount; ++i) {
				this->m_DecryptedBuffer[i] = this->m_Buffer[i] ^ this->m_Key;
			}

			// Erase the original buffer and key
			memset(this->m_Buffer, 0, MAX_PATH);
			this->m_Key = 0;
		}

		// Overwrite and deallocate the local decrypted buffer
		void eraseAndDeallocateDecryptedBuffer()
		{
			// If the buffer was never allocated, exit
			if(!this->m_DecryptedBuffer) return;

			// Overwrite the string with zero
			memset(this->m_DecryptedBuffer, 0, this->m_CharacterCount * sizeof(wchar_t));
			// Deallocate the memory
			delete[] this->m_DecryptedBuffer;
		}
	};
}

#endif
