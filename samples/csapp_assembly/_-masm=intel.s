	.file	"combine.c"
	.intel_syntax noprefix
	.text
	.p2align 4,,15
	.globl	_combine4
	.def	_combine4;	.scl	2;	.type	32;	.endef
_combine4:
LFB0:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	edi
	push	esi
	push	ebx
	and	esp, -32
	sub	esp, 32
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	mov	ebx, DWORD PTR [ebp+8]
	mov	edx, ebx
	and	edx, 31
	shr	edx, 2
	neg	edx
	and	edx, 7
	je	L8
	fld1
	xor	eax, eax
	mov	ecx, 134217728
	.p2align 4,,10
L3:
	fadd	DWORD PTR [ebx+eax*4]
	mov	esi, ecx
	add	eax, 1
	sub	esi, eax
	cmp	edx, eax
	ja	L3
L2:
	mov	DWORD PTR [esp+28], 134217728
	sub	DWORD PTR [esp+28], edx
	mov	edi, DWORD PTR [esp+28]
	shr	edi, 3
	lea	ecx, [0+edi*8]
	test	ecx, ecx
	mov	DWORD PTR [esp+24], ecx
	je	L4
	lea	ecx, [ebx+edx*4]
	xor	edx, edx
	vxorps	xmm0, xmm0, xmm0
	.p2align 4,,10
L5:
	add	edx, 1
	vaddps	ymm0, ymm0, YMMWORD PTR [ecx]
	add	ecx, 32
	cmp	edx, edi
	jb	L5
	vhaddps	ymm0, ymm0, ymm0
	mov	edx, DWORD PTR [esp+24]
	add	eax, DWORD PTR [esp+24]
	sub	esi, DWORD PTR [esp+24]
	vhaddps	ymm1, ymm0, ymm0
	cmp	DWORD PTR [esp+28], edx
	vperm2f128	ymm0, ymm1, ymm1, 1
	vaddps	ymm0, ymm0, ymm1
	vmovss	DWORD PTR [esp+20], xmm0
	fadd	DWORD PTR [esp+20]
	je	L6
L4:
	add	esi, eax
	.p2align 4,,10
L7:
	fadd	DWORD PTR [ebx+eax*4]
	add	eax, 1
	cmp	eax, esi
	jne	L7
L6:
	lea	esp, [ebp-12]
	pop	ebx
	.cfi_remember_state
	.cfi_restore 3
	pop	esi
	.cfi_restore 6
	pop	edi
	.cfi_restore 7
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	vzeroupper
	ret
L8:
	.cfi_restore_state
	fld1
	mov	esi, 134217728
	xor	eax, eax
	jmp	L2
	.cfi_endproc
LFE0:
