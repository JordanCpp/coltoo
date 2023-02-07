#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *f;
	char debug = 0;
	char buf[MAX_PATH + 1], cmd[MAX_PATH + 100];

	puts("Enter your Mingw32 tools (make, gcc etc.) path:");
	puts("(if you have Dev-Cpp, enter path to the bin directory)");
	fgets(buf, MAX_PATH, stdin);
	if(!*buf) return 1;
	if(buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = 0;

	strcpy(cmd, buf);
	f = fopen(strcat(cmd, "\\mingw32-make.exe"), "r");
	if(!f)
	{
		puts("mingw32-make.exe not found. Exiting.");
		return 1;
	}
	fclose(f);
	strcpy(cmd, buf);
	f = fopen(strcat(cmd, "\\gcc.exe"), "r");
	if(!f)
	{
		puts("gcc.exe not found. Exiting.");
		return 1;
	}
	fclose(f);
	strcpy(cmd, buf);
	f = fopen(strcat(cmd, "\\g++.exe"), "r");
	if(!f)
	{
		puts("g++.exe not found. Exiting.");
		return 1;
	}
	fclose(f);

	while(debug != 'Y' && debug != 'y' && debug != 'N' && debug != 'n')
	{
		printf("Enable ColToo debug output? (Y/N) (if unsure, choose N) ");
		debug = getche();
		putchar('\n');
	}
	puts("Executing batch file...\n");

	if(debug == 'Y' || debug == 'y')
		sprintf(cmd, "call mingw-debug.bat \"%s\"", buf);
	else
		sprintf(cmd, "call mingw-release.bat \"%s\"", buf);
	system(cmd);
	return 0;
}
