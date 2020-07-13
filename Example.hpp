#include "HiddenString.hpp"

int main()
{
	// Generate the hidden string
	HideString(iafsdnbfi, HiddenString, "Hello, world!");
	// Save the hidden string in an UNICODE C-String for use
	const wchar_t * DecryptedString = HiddenString;
	// Print the string
	printf("%ws\n", DecryptedString);

	getchar();
	return 0;
}
