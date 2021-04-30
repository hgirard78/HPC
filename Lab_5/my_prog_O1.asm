	.file	"mat_vec.c"
	.text
	.globl	mat_vec
	.type	mat_vec, @function
mat_vec:
.LFB22:
	.cfi_startproc
	testl	%ecx, %ecx
	jle	.L8
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rsi, %r10
	movl	%ecx, %ebx
	movq	%rdx, %r8
	movq	%rdi, %r9
	movslq	%ecx, %rsi
	salq	$3, %rsi
	leal	-1(%rcx), %eax
	leaq	8(%r10,%rax,8), %rdi
	movl	$0, %r11d
.L4:
	movq	%r8, %rcx
	movq	$0x000000000, (%r8)
	movq	%r10, %rax
	movq	%r9, %rdx
.L3:
	movsd	(%rdx), %xmm0
	mulsd	(%rax), %xmm0
	addsd	(%rcx), %xmm0
	movsd	%xmm0, (%rcx)
	addq	%rsi, %rdx
	addq	$8, %rax
	cmpq	%rdi, %rax
	jne	.L3
	addl	$1, %r11d
	addq	$8, %r8
	addq	$8, %r9
	cmpl	%r11d, %ebx
	jne	.L4
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore 3
	ret
	.cfi_endproc
.LFE22:
	.size	mat_vec, .-mat_vec
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
