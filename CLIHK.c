#include <Windows.h>

#include "config.h"

extern const char* hkfuncpair[];

void getinput(unsigned short* alnum, unsigned short* ctl);

unsigned short checkresults(unsigned short* alnum, unsigned short* ctl,
	const char* str);


int main()
{
	/*works, hides window*/
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	/*unsigned short buffers for the keyinput*/
	unsigned short alphanum[36];
	unsigned short control[6];
	while (1) {
		/*retrieve keyboard input*/
		getinput(alphanum, control);
		/*input is done; now iteratively parse strings for matches*/
		for (int i = 0; i < sizeof(hkfuncpair)/sizeof(char*); i+=2) {
			if (checkresults(alphanum, control, hkfuncpair[i])) {
				if (!strcmp(QUIT, hkfuncpair[i + 1]))
					exit(1);
				/*continue execution if it wasn't the exitstr*/
				else
					system(hkfuncpair[i + 1]);
			}
		}
		/*1 frame on a 144hz monitor, should mean no perceivable
		  loss in response time while gaining performance*/
		Sleep(8);
	}
	return 0;
}

void getinput(unsigned short* alnum, unsigned short* ctl) {
	/*get alphanumeric keys*/
	/*use low bit because spam*/
	for (int i = 0; i < 26; i++)
		alnum[i] = GetAsyncKeyState(i + 'A') & 1 ? 0x8000 : 0;
	for (int i = 0; i < 10; i++)
		alnum[i + 26] = GetAsyncKeyState(i + '0') & 1 ? 0x8000 : 0;

	/*can't think of a better way to do this
	 *that's not a self compliment, it is just annoyance to win*/
	ctl[0] = GetAsyncKeyState(VK_LMENU) & 0x8000;
	ctl[1] = GetAsyncKeyState(VK_RMENU) & 0x8000;
	ctl[2] = GetAsyncKeyState(VK_LSHIFT) & 0x8000;
	ctl[3] = GetAsyncKeyState(VK_RSHIFT) & 0x8000;
	ctl[4] = GetAsyncKeyState(VK_LCONTROL) & 0x8000;
	ctl[5] = GetAsyncKeyState(VK_RCONTROL) & 0x8000;
}

unsigned short checkresults(unsigned short* alnum, unsigned short* ctl, 
	const char* str)
{
	unsigned short flag = 0x8000;
	for (int j = 0; str[j] != '\0'; j++) {
		switch (str[j]) {
		case 'l':
		case 'r':
			continue;
		case 'a':
			if (str[j - 1] == 'l')
				flag &= ctl[0];
			else
				flag &= ctl[1];
			break;
		case 's':
			if (str[j - 1] == 'l')
				flag &= ctl[2];
			else
				flag &= ctl[3];
			break;
		case 'c':
			if (str[j - 1] == 'l')
				flag &= ctl[4];
			else
				flag &= ctl[5];
			break;
		default:
			if (isalpha(str[j]))
				flag &= alnum[str[j] - 'A'];
			else if (isalnum(str[j]))
				flag &= alnum[str[j] - '0' + 26];
		}
	}
	return flag;
}
