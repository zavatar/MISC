	.file	"combine.c"
	.text
	.p2align 4,,15
	.globl	_combine4
	.def	_combine4;	.scl	2;	.type	32;	.endef
_combine4:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	andl	$-32, %esp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	%eax, %edx
	andl	$31, %edx
	shrl	$2, %edx
	negl	%edx
	andl	$7, %edx
	je	L10
	vmovss	LC0, %xmm1
	cmpl	$1, %edx
	vaddss	(%eax), %xmm1, %xmm3
	jbe	L11
	cmpl	$2, %edx
	vaddss	4(%eax), %xmm3, %xmm3
	jbe	L12
	cmpl	$3, %edx
	vaddss	8(%eax), %xmm3, %xmm3
	jbe	L13
	cmpl	$4, %edx
	vaddss	12(%eax), %xmm3, %xmm3
	jbe	L14
	cmpl	$5, %edx
	vaddss	16(%eax), %xmm3, %xmm3
	jbe	L15
	cmpl	$6, %edx
	vaddss	20(%eax), %xmm3, %xmm3
	jbe	L16
	vaddss	24(%eax), %xmm3, %xmm3
	movl	$134217721, 8(%esp)
	movl	$7, 12(%esp)
L2:
	leal	(%eax,%edx,4), %ecx
	movl	$134217728, %edi
	subl	%edx, %edi
	movl	%ecx, %edx
	movl	%ecx, (%esp)
	movl	%edi, %ebx
	addl	$32, %edx
	vmovaps	(%ecx), %ymm0
	shrl	$3, %ebx
	movl	$1, %ecx
	leal	0(,%ebx,8), %esi
	movl	%esi, 4(%esp)
	leal	-1(%ebx), %esi
	andl	$7, %esi
	cmpl	$1, %ebx
	jbe	L68
	testl	%esi, %esi
	je	L9
	cmpl	$1, %esi
	je	L50
	cmpl	$2, %esi
	.p2align 4,,3
	je	L51
	cmpl	$3, %esi
	.p2align 4,,2
	je	L52
	cmpl	$4, %esi
	.p2align 4,,2
	je	L53
	cmpl	$5, %esi
	.p2align 4,,2
	je	L54
	cmpl	$6, %esi
	.p2align 4,,2
	je	L55
	vaddps	(%edx), %ymm0, %ymm0
	movl	$2, %ecx
	movl	(%esp), %edx
	addl	$64, %edx
L55:
	vaddps	(%edx), %ymm0, %ymm0
	addl	$1, %ecx
	addl	$32, %edx
L54:
	vaddps	(%edx), %ymm0, %ymm0
	addl	$1, %ecx
	addl	$32, %edx
L53:
	vaddps	(%edx), %ymm0, %ymm0
	addl	$1, %ecx
	addl	$32, %edx
L52:
	vaddps	(%edx), %ymm0, %ymm0
	addl	$1, %ecx
	addl	$32, %edx
L51:
	vaddps	(%edx), %ymm0, %ymm0
	addl	$1, %ecx
	addl	$32, %edx
L50:
	addl	$1, %ecx
	vaddps	(%edx), %ymm0, %ymm0
	addl	$32, %edx
	cmpl	%ecx, %ebx
	jbe	L68
	.p2align 4,,10
L9:
	vaddps	(%edx), %ymm0, %ymm2
	addl	$8, %ecx
	addl	$256, %edx
	vaddps	-224(%edx), %ymm2, %ymm4
	vaddps	-192(%edx), %ymm4, %ymm5
	vaddps	-160(%edx), %ymm5, %ymm6
	vaddps	-128(%edx), %ymm6, %ymm7
	vaddps	-96(%edx), %ymm7, %ymm1
	vaddps	-64(%edx), %ymm1, %ymm0
	vaddps	-32(%edx), %ymm0, %ymm0
	cmpl	%ecx, %ebx
	ja	L9
L68:
	vhaddps	%ymm0, %ymm0, %ymm2
	movl	4(%esp), %ebx
	movl	12(%esp), %edx
	movl	8(%esp), %esi
	vhaddps	%ymm2, %ymm2, %ymm4
	addl	%ebx, %edx
	vperm2f128	$1, %ymm4, %ymm4, %ymm5
	vaddps	%ymm4, %ymm5, %ymm6
	subl	%ebx, %esi
	cmpl	%ebx, %edi
	vmovaps	%xmm6, %xmm7
	vmovaps	%xmm7, %xmm1
	vaddss	%xmm3, %xmm1, %xmm3
	je	L7
	vaddss	(%eax,%edx,4), %xmm3, %xmm3
	leal	1(%edx), %ecx
	cmpl	$1, %esi
	je	L7
	vaddss	(%eax,%ecx,4), %xmm3, %xmm3
	leal	2(%edx), %edi
	cmpl	$2, %esi
	je	L7
	vaddss	(%eax,%edi,4), %xmm3, %xmm3
	leal	3(%edx), %ebx
	cmpl	$3, %esi
	je	L7
	vaddss	(%eax,%ebx,4), %xmm3, %xmm3
	leal	4(%edx), %ecx
	cmpl	$4, %esi
	je	L7
	vaddss	(%eax,%ecx,4), %xmm3, %xmm3
	leal	5(%edx), %edi
	cmpl	$5, %esi
	je	L7
	addl	$6, %edx
	vaddss	(%eax,%edi,4), %xmm3, %xmm3
	cmpl	$6, %esi
	je	L7
	vaddss	(%eax,%edx,4), %xmm3, %xmm3
L7:
	vmovss	%xmm3, 12(%esp)
	vzeroupper
	flds	12(%esp)
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,10
L10:
	movl	$134217728, 8(%esp)
	vmovss	LC0, %xmm3
	movl	$0, 12(%esp)
	jmp	L2
	.p2align 4,,10
L12:
	movl	$134217726, 8(%esp)
	movl	$2, 12(%esp)
	jmp	L2
	.p2align 4,,10
L13:
	movl	$134217725, 8(%esp)
	movl	$3, 12(%esp)
	jmp	L2
	.p2align 4,,10
L11:
	movl	$134217727, 8(%esp)
	movl	$1, 12(%esp)
	jmp	L2
	.p2align 4,,10
L16:
	movl	$134217722, 8(%esp)
	movl	$6, 12(%esp)
	jmp	L2
	.p2align 4,,10
L14:
	movl	$134217724, 8(%esp)
	movl	$4, 12(%esp)
	jmp	L2
	.p2align 4,,10
L15:
	movl	$134217723, 8(%esp)
	movl	$5, 12(%esp)
	jmp	L2
	.section .rdata,"dr"
	.align 4
LC0:
	.long	1065353216
	.ident	"GCC: (GNU) 4.8.1"
