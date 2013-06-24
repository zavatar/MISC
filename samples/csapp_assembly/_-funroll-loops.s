	.file	"combine.c"
	.text
	.globl	_combine4
	.def	_combine4;	.scl	2;	.type	32;	.endef
_combine4:
	subl	$4, %esp
	movl	8(%esp), %edx
	movl	$0, %eax
	vmovss	LC0, %xmm7
L3:
	vaddss	(%edx,%eax,4), %xmm7, %xmm0
	addl	$1, %eax
	vaddss	(%edx,%eax,4), %xmm0, %xmm1
	leal	1(%eax), %ecx
	vaddss	(%edx,%ecx,4), %xmm1, %xmm2
	leal	2(%eax), %ecx
	vaddss	(%edx,%ecx,4), %xmm2, %xmm3
	leal	3(%eax), %ecx
	vaddss	(%edx,%ecx,4), %xmm3, %xmm4
	leal	4(%eax), %ecx
	vaddss	(%edx,%ecx,4), %xmm4, %xmm5
	leal	5(%eax), %ecx
	vaddss	(%edx,%ecx,4), %xmm5, %xmm6
	leal	6(%eax), %ecx
	vaddss	(%edx,%ecx,4), %xmm6, %xmm7
	addl	$7, %eax
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
