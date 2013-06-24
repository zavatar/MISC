	.file	"combine.c"
	.text
	.globl	_combine4
	.def	_combine4;	.scl	2;	.type	32;	.endef
_combine4:
	subl	$4, %esp
	movl	8(%esp), %edx
	movl	$0, %eax
	vmovss	LC0, %xmm0
L3:
	vaddss	(%edx,%eax,4), %xmm0, %xmm0
	addl	$1, %eax
	cmpl	$134217728, %eax
	jne	L3
	vmovss	%xmm0, (%esp)
	flds	(%esp)
	addl	$4, %esp
	ret
	.section .rdata,"dr"
	.align 4
LC0:
	.long	1065353216
	.ident	"GCC: (GNU) 4.8.1"
