// refer to http://msdn.microsoft.com/en-us/library/k2b2ssfy.aspx
// select Configuration to RelWithDebInfo

// __clrcall virtual function, __thiscall class member function

// Caller cleanup Stack, Default, /Gd
int __cdecl sum__cdecl(int x, int y);
// Callee cleanup Stack, /Gz
int __stdcall sum__stdcall(int x, int y);
// Callee cleanup Stack, /Gr
int __fastcall sum__fastcall(int x, int y);

int __cdecl sum_vararg(int x, int y, ...);

int main()
{
	return sum__cdecl(1, 3)
		+  sum__stdcall(-1, -3)
		+  sum__fastcall(5, 7)
		+  sum_vararg(-5, -7, 2, -2);
}
