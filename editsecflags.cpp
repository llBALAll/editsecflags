#include <windows.h>
#include <imagehlp.h>
#include <iostream>

BOOL EditSecFlags(LPCSTR path, bool ASLR, bool DEP) {

	LOADED_IMAGE PE;

	if (MapAndLoad(path, 0, &PE, 0, 0))	{
	if (ASLR) PE.FileHeader->OptionalHeader.DllCharacteristics |= IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE;
        else PE.FileHeader->OptionalHeader.DllCharacteristics &= ~IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE;

        if (DEP) PE.FileHeader->OptionalHeader.DllCharacteristics |= IMAGE_DLLCHARACTERISTICS_NX_COMPAT;
        else PE.FileHeader->OptionalHeader.DllCharacteristics &= ~IMAGE_DLLCHARACTERISTICS_NX_COMPAT;

		UnMapAndLoad(&PE);
        return EXIT_SUCCESS;
    } else
		return EXIT_FAILURE;
}

int main (int argc , char** argv) {

	system("Title C:\\Windows\\system32\\cmd.exe");

	if ((argc != 4) || (strcmp(argv[2], "0") && strcmp(argv[2], "1")) || (strcmp(argv[3], "0") && strcmp(argv[3], "1"))) {
		std::cout << "\nThis program edit the security flags ASLR & DEP of 32b/64b Portable Executable files.";
		std::cout << "\n  Usage: editsecflags pathfilename ASLR DEP";
		std::cout << "\n  ASLR/DEP : 0(disable) 1(enable)";
		std::cout << "\n  Example to disable ASLR & DEP: editsecflags pathfilename 0 0\n";
		return EXIT_FAILURE;
	}

	if (EditSecFlags(argv[1], atoi(argv[2]), atoi(argv[3])) == EXIT_SUCCESS) {
		std::cout << "Flags changed.";
	} else {
		std::cout << "Error: can not change flags!";
		return EXIT_FAILURE;
	}
}
