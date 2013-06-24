	.file	"combine.c"
	.text
	.globl	_combine4
	.def	_combine4;	.scl	2;	.type	32;	.endef
_combine4:
	movl	4(%esp), %edx
	movl	$0, %eax
	fld1
L3:
	fadds	(%edx,%eax,4)
	addl	$1, %eax
	cmpl	$134217728, %eax
	jne	L3
	rep ret
	.ident	"GCC: (GNU) 4.8.1"
