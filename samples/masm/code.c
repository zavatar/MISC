int accum = 0;

#define BODY \
{\
	int t = x + y;\
	accum += t;\
	return t;\
}

// Caller cleanup Stack, Default, /Gd
int __cdecl sum__cdecl(int x, int y) BODY;

// Callee cleanup Stack, /Gz
int __stdcall sum__stdcall(int x, int y) BODY;

// Callee cleanup Stack, /Gr
int __fastcall sum__fastcall(int x, int y) BODY;

int __cdecl sum_vararg(int x, int y, ...)
{
	int t = x + y + *(&y+1) + *(&y+2);
	accum += t;
	return t;
}