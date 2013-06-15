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
	cmpl	$1, %edx
	vmovss	(%eax), %xmm0
	jbe	L11
	vmulss	4(%eax), %xmm0, %xmm0
	cmpl	$2, %edx
	jbe	L12
	vmulss	8(%eax), %xmm0, %xmm0
	cmpl	$3, %edx
	jbe	L13
	vmulss	12(%eax), %xmm0, %xmm0
	cmpl	$4, %edx
	jbe	L14
	vmulss	16(%eax), %xmm0, %xmm0
	cmpl	$5, %edx
	jbe	L15
	vmulss	20(%eax), %xmm0, %xmm0
	cmpl	$6, %edx
	jbe	L16
	vmulss	24(%eax), %xmm0, %xmm0
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
	vmovaps	(%ecx), %ymm1
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
	vmulps	(%edx), %ymm1, %ymm1
	movl	(%esp), %edx
	movl	$2, %ecx
	addl	$64, %edx
L55:
	vmulps	(%edx), %ymm1, %ymm1
	addl	$1, %ecx
	addl	$32, %edx
L54:
	vmulps	(%edx), %ymm1, %ymm1
	addl	$1, %ecx
	addl	$32, %edx
L53:
	vmulps	(%edx), %ymm1, %ymm1
	addl	$1, %ecx
	addl	$32, %edx
L52:
	vmulps	(%edx), %ymm1, %ymm1
	addl	$1, %ecx
	addl	$32, %edx
L51:
	vmulps	(%edx), %ymm1, %ymm1
	addl	$1, %ecx
	addl	$32, %edx
L50:
	addl	$1, %ecx
	vmulps	(%edx), %ymm1, %ymm1
	addl	$32, %edx
	cmpl	%ecx, %ebx
	jbe	L68
	.p2align 4,,10
L9:
	addl	$8, %ecx
	vmulps	(%edx), %ymm1, %ymm2
	addl	$256, %edx
	vmulps	-224(%edx), %ymm2, %ymm3
	vmulps	-192(%edx), %ymm3, %ymm4
	vmulps	-160(%edx), %ymm4, %ymm5
	vmulps	-128(%edx), %ymm5, %ymm6
	vmulps	-96(%edx), %ymm6, %ymm7
	vmulps	-64(%edx), %ymm7, %ymm1
	vmulps	-32(%edx), %ymm1, %ymm1
	cmpl	%ecx, %ebx
	ja	L9
L68:
	vmovaps	%xmm1, %xmm2
	vshufps	$85, %xmm1, %xmm1, %xmm6
	vunpckhps	%xmm1, %xmm1, %xmm5
	vmovaps	%xmm2, %xmm7
	vshufps	$255, %xmm1, %xmm1, %xmm4
	vextractf128	$0x1, %ymm1, %xmm1
	vmulss	%xmm6, %xmm7, %xmm7
	vmovaps	%xmm1, %xmm3
	vshufps	$85, %xmm1, %xmm1, %xmm2
	movl	4(%esp), %ebx
	vextractps	$2, %xmm1, (%esp)
	vshufps	$255, %xmm1, %xmm1, %xmm1
	movl	12(%esp), %edx
	movl	8(%esp), %esi
	vmulss	%xmm0, %xmm7, %xmm0
	addl	%ebx, %edx
	subl	%ebx, %esi
	cmpl	%ebx, %edi
	vmulss	%xmm5, %xmm0, %xmm6
	vmulss	%xmm4, %xmm6, %xmm5
	vmulss	%xmm3, %xmm5, %xmm4
	vmulss	%xmm2, %xmm4, %xmm3
	vmulss	(%esp), %xmm3, %xmm2
	vmulss	%xmm1, %xmm2, %xmm7
	je	L7
	vmulss	(%eax,%edx,4), %xmm7, %xmm7
	cmpl	$1, %esi
	leal	1(%edx), %ecx
	je	L7
	vmulss	(%eax,%ecx,4), %xmm7, %xmm7
	cmpl	$2, %esi
	leal	2(%edx), %edi
	je	L7
	vmulss	(%eax,%edi,4), %xmm7, %xmm7
	cmpl	$3, %esi
	leal	3(%edx), %ebx
	je	L7
	vmulss	(%eax,%ebx,4), %xmm7, %xmm7
	cmpl	$4, %esi
	leal	4(%edx), %ecx
	je	L7
	vmulss	(%eax,%ecx,4), %xmm7, %xmm7
	cmpl	$5, %esi
	leal	5(%edx), %edi
	je	L7
	vmulss	(%eax,%edi,4), %xmm7, %xmm7
	addl	$6, %edx
	cmpl	$6, %esi
	je	L7
	vmulss	(%eax,%edx,4), %xmm7, %xmm7
L7:
	vmovss	%xmm7, 12(%esp)
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
	vmovss	LC0, %xmm0
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
