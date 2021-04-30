	.file	"mat_vec.c"
	.text
	.p2align 4
	.globl	mat_vec
	.type	mat_vec, @function
mat_vec:
.LFB22:
	.cfi_startproc
	movq	%rsi, %r11
	movl	%ecx, %r10d
	testl	%ecx, %ecx
	jle	.L1
	movslq	%r10d, %rsi
	leal	-1(%r10), %eax
	movq	%rdi, %r8
	movq	%rdx, %rcx
	salq	$3, %rsi
	leaq	8(%r11,%rax,8), %rdi
	pxor	%xmm2, %xmm2
	xorl	%r9d, %r9d
	.p2align 4,,10
	.p2align 3
.L4:
	movq	$0x000000000, (%rcx)
	movq	%r11, %rax
	movq	%r8, %rdx
	movapd	%xmm2, %xmm1
	.p2align 4,,10
	.p2align 3
.L3:
	movsd	(%rdx), %xmm0
	mulsd	(%rax), %xmm0
	addq	$8, %rax
	addq	%rsi, %rdx
	addsd	%xmm0, %xmm1
	movsd	%xmm1, (%rcx)
	cmpq	%rdi, %rax
	jne	.L3
	addl	$1, %r9d
	addq	$8, %rcx
	addq	$8, %r8
	cmpl	%r9d, %r10d
	jne	.L4
.L1:
	ret
	.cfi_endproc
.LFE22:
	.size	mat_vec, .-mat_vec
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
