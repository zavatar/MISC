; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.60315.1 

	TITLE	H:\openSource\MISC\samples\masm\main.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRT
INCLUDELIB OLDNAMES

PUBLIC	_main
EXTRN	_sum__cdecl:PROC
EXTRN	_sum__stdcall@8:PROC
EXTRN	@sum__fastcall@8:PROC
EXTRN	_sum_vararg:PROC
; Function compile flags: /Ogtp
;	COMDAT _main
_TEXT	SEGMENT
_main	PROC						; COMDAT
; File h:\opensource\misc\samples\masm\main.c
; Line 16
	push	esi
; Line 20
	push	-2					; fffffffeH
	push	2
	push	-7					; fffffff9H
	push	-5					; fffffffbH
	call	_sum_vararg
	mov	edx, 7
	add	esp, 16					; 00000010H
	lea	ecx, DWORD PTR [edx-2]
	mov	esi, eax
	call	@sum__fastcall@8
	push	3
	push	1
	add	esi, eax
	call	_sum__cdecl
	add	esp, 8
	add	esi, eax
	push	-3					; fffffffdH
	push	-1
	call	_sum__stdcall@8
	add	eax, esi
	pop	esi
; Line 21
	ret	0
_main	ENDP
_TEXT	ENDS
END
