	.file	"combine.c"
	.text
	.p2align 4,,15
	.globl	_combine4
	.def	_combine4;	.scl	2;	.type	32;	.endef
_combine4:
	subl	$4, %esp
	xorl	%eax, %eax
	movl	8(%esp), %edx
	vmovss	LC0, %xmm7
	.p2align 4,,10
L3:
	vaddss	(%edx,%eax,4), %xmm7, %xmm0
	vaddss	4(%edx,%eax,4), %xmm0, %xmm1
	vaddss	8(%edx,%eax,4), %xmm1, %xmm2
	vaddss	12(%edx,%eax,4), %xmm2, %xmm3
	vaddss	16(%edx,%eax,4), %xmm3, %xmm4
	vaddss	20(%edx,%eax,4), %xmm4, %xmm5
	vaddss	24(%edx,%eax,4), %xmm5, %xmm6
	vaddss	28(%edx,%eax,4), %xmm6, %xmm7
	addl	$8, %eax
	cmpl	$134217728, %eax
	jne	L3
	vmovss	%xmm7, (%esp)
	flds	(%esp)
	addl	$4, %esp
	ret
	.section .rdata,"dr"
	.align 4
LC0:
	.long	1065353216
	.ident	"GCC: (GNU) 4.8.1"
