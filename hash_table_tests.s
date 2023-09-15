	.arch armv8-a
	.file	"hash_table_tests.c"
	.text
	.align	2
	.p2align 4,,11
	.global	init_suite
	.type	init_suite, %function
init_suite:
.LFB35:
	.cfi_startproc
	mov	w0, 0
	ret
	.cfi_endproc
.LFE35:
	.size	init_suite, .-init_suite
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	""
	.align	3
.LC1:
	.string	"hash_table_tests.c"
	.align	3
.LC2:
	.string	"CU_ASSERT_PTR_NOT_NULL(ht)"
	.text
	.align	2
	.p2align 4,,11
	.global	test_create_destroy
	.type	test_create_destroy, %function
test_create_destroy:
.LFB37:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	x19, [sp, 16]
	.cfi_offset 19, -16
	bl	ioopm_hash_table_create
	cmp	x0, 0
	mov	x19, x0
	mov	w5, 0
	cset	w0, ne
	mov	w1, 19
	adrp	x4, .LC0
	adrp	x3, .LC1
	add	x4, x4, :lo12:.LC0
	add	x3, x3, :lo12:.LC1
	adrp	x2, .LC2
	add	x2, x2, :lo12:.LC2
	bl	CU_assertImplementation
	mov	x0, x19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_def_cfa_offset 0
	b	ioopm_hash_table_destroy
	.cfi_endproc
.LFE37:
	.size	test_create_destroy, .-test_create_destroy
	.section	.rodata.str1.8
	.align	3
.LC3:
	.string	"CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, i))"
	.align	3
.LC4:
	.string	"Hej"
	.align	3
.LC5:
	.string	"CU_ASSERT_STRING_EQUAL(\"Hej\",ioopm_hash_table_lookup(ht, 6))"
	.text
	.align	2
	.p2align 4,,11
	.global	test_insert_once
	.type	test_insert_once, %function
test_insert_once:
.LFB38:
	.cfi_startproc
	stp	x29, x30, [sp, -64]!
	.cfi_def_cfa_offset 64
	.cfi_offset 29, -64
	.cfi_offset 30, -56
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -48
	.cfi_offset 20, -40
	mov	w19, 0
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -32
	.cfi_offset 22, -24
	adrp	x22, .LC0
	adrp	x21, .LC1
	add	x22, x22, :lo12:.LC0
	add	x21, x21, :lo12:.LC1
	str	x23, [sp, 48]
	.cfi_offset 23, -16
	adrp	x23, .LC3
	bl	ioopm_hash_table_create
	add	x23, x23, :lo12:.LC3
	mov	x20, x0
	.p2align 3,,7
.L6:
	mov	w1, w19
	mov	x0, x20
	bl	ioopm_hash_table_lookup
	cmp	x0, 0
	add	w19, w19, 1
	cset	w0, eq
	mov	x4, x22
	mov	x3, x21
	mov	x2, x23
	mov	w5, 0
	mov	w1, 27
	bl	CU_assertImplementation
	cmp	w19, 17
	bne	.L6
	adrp	x19, .LC4
	add	x19, x19, :lo12:.LC4
	mov	x2, x19
	mov	x0, x20
	mov	w1, 6
	bl	ioopm_hash_table_insert
	mov	x0, x20
	mov	w1, 6
	bl	ioopm_hash_table_lookup
	mov	x1, x0
	mov	x0, x19
	bl	strcmp
	cmp	w0, 0
	mov	x4, x22
	mov	x3, x21
	cset	w0, eq
	mov	w5, 0
	mov	w1, 30
	adrp	x2, .LC5
	add	x2, x2, :lo12:.LC5
	bl	CU_assertImplementation
	mov	x0, x20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 23
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	b	ioopm_hash_table_destroy
	.cfi_endproc
.LFE38:
	.size	test_insert_once, .-test_insert_once
	.align	2
	.p2align 4,,11
	.global	clean_suite
	.type	clean_suite, %function
clean_suite:
.LFB41:
	.cfi_startproc
	mov	w0, 0
	ret
	.cfi_endproc
.LFE41:
	.size	clean_suite, .-clean_suite
	.section	.rodata.str1.8
	.align	3
.LC6:
	.string	"My awesome test suite"
	.align	3
.LC7:
	.string	"Test for create_destroy functionality"
	.align	3
.LC8:
	.string	"Test for insert_once functionality"
	.section	.text.startup,"ax",@progbits
	.align	2
	.p2align 4,,11
	.global	main
	.type	main, %function
main:
.LFB39:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	bl	CU_initialize_registry
	cbnz	w0, .L19
	adrp	x2, clean_suite
	adrp	x1, init_suite
	add	x2, x2, :lo12:clean_suite
	add	x1, x1, :lo12:init_suite
	adrp	x0, .LC6
	add	x0, x0, :lo12:.LC6
	str	x19, [sp, 16]
	.cfi_offset 19, -16
	bl	CU_add_suite
	mov	x19, x0
	cbz	x0, .L20
	adrp	x2, test_create_destroy
	adrp	x1, .LC7
	add	x2, x2, :lo12:test_create_destroy
	add	x1, x1, :lo12:.LC7
	bl	CU_add_test
	cbz	x0, .L20
	adrp	x2, test_insert_once
	adrp	x1, .LC8
	mov	x0, x19
	add	x2, x2, :lo12:test_insert_once
	add	x1, x1, :lo12:.LC8
	bl	CU_add_test
	cbz	x0, .L20
	mov	w0, 2
	bl	CU_basic_set_mode
	bl	CU_basic_run_tests
.L20:
	bl	CU_cleanup_registry
	ldr	x19, [sp, 16]
	.cfi_restore 19
.L19:
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa_offset 0
	b	CU_get_error
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
