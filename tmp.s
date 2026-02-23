	.file	"array_to_array.c"
	.intel_syntax noprefix
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "> NULL\0"
.LC1:
	.ascii "> %d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 96
	.seh_stackalloc	96
	.seh_endprologue
	call	__main
	pxor	xmm0, xmm0
	movups	XMMWORD PTR -32[rbp], xmm0
	movq	QWORD PTR -16[rbp], xmm0
	mov	DWORD PTR -32[rbp], 12
	mov	DWORD PTR -28[rbp], 3
	mov	DWORD PTR -24[rbp], 4
	mov	DWORD PTR -20[rbp], 5
	mov	DWORD PTR -4[rbp], 0
	jmp	.L2
.L5:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	mov	edx, DWORD PTR -32[rbp+rax*4]
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	mov	DWORD PTR -64[rbp+rax*4], edx
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	mov	eax, DWORD PTR -32[rbp+rax*4]
	test	eax, eax
	jne	.L3
	lea	rax, .LC0[rip]
	mov	rcx, rax
	call	puts
	jmp	.L4
.L3:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	mov	eax, DWORD PTR -64[rbp+rax*4]
	lea	edx, [rax+rax]
	lea	rax, .LC1[rip]
	mov	rcx, rax
	call	printf
.L4:
	add	DWORD PTR -4[rbp], 1
.L2:
	cmp	DWORD PTR -4[rbp], 5
	jle	.L5
	mov	eax, 0
	add	rsp, 96
	pop	rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev8, Built by MSYS2 project) 15.2.0"
	.def	puts;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
