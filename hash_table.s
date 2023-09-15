	.arch armv8-a
	.file	"hash_table.c"
	.text
	.align	2
	.p2align 4,,11
	.type	find_previous_entry_for_key.isra.0, %function
find_previous_entry_for_key.isra.0:
.LFB46:
	.cfi_startproc
.L3:
	ldr	x2, [x0, 16]
	cbz	x2, .L1
	ldr	w3, [x2]
	cmp	w3, w1
	ble	.L10
.L1:
	ret
	.p2align 2,,3
.L10:
	ldr	x0, [x2, 16]
	cbz	x0, .L4
	ldr	w3, [x0]
	cmp	w1, w3
	bge	.L3
.L4:
	mov	x0, x2
	ret
	.cfi_endproc
.LFE46:
	.size	find_previous_entry_for_key.isra.0, .-find_previous_entry_for_key.isra.0
	.align	2
	.p2align 4,,11
	.global	entry_destroy
	.type	entry_destroy, %function
entry_destroy:
.LFB40:
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 29, -32
	.cfi_offset 30, -24
	mov	x29, sp
	str	x19, [sp, 16]
	.cfi_offset 19, -16
	mov	x19, x0
	.p2align 3,,7
.L12:
	mov	x0, x19
	ldr	x19, [x19, 16]
	bl	free
	cbnz	x19, .L12
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 19
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE40:
	.size	entry_destroy, .-entry_destroy
	.align	2
	.p2align 4,,11
	.global	ioopm_hash_table_create
	.type	ioopm_hash_table_create, %function
ioopm_hash_table_create:
.LFB41:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x1, 136
	mov	x0, 1
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	.cfi_offset 19, -32
	.cfi_offset 20, -24
	.cfi_offset 21, -16
	bl	calloc
	mov	x21, x0
	mov	x19, x0
	add	x20, x0, 136
	.p2align 3,,7
.L16:
	mov	x1, 24
	mov	x0, 1
	bl	calloc
	str	x0, [x19], 8
	cmp	x19, x20
	bne	.L16
	mov	x0, x21
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 21
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE41:
	.size	ioopm_hash_table_create, .-ioopm_hash_table_create
	.align	2
	.p2align 4,,11
	.global	ioopm_hash_table_destroy
	.type	ioopm_hash_table_destroy, %function
ioopm_hash_table_destroy:
.LFB42:
	.cfi_startproc
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -32
	.cfi_offset 20, -24
	mov	x20, x0
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -16
	.cfi_offset 22, -8
	mov	x22, x0
	add	x21, x0, 136
	.p2align 3,,7
.L21:
	ldr	x19, [x20]
	.p2align 3,,7
.L20:
	mov	x0, x19
	ldr	x19, [x19, 16]
	bl	free
	cbnz	x19, .L20
	add	x20, x20, 8
	cmp	x20, x21
	bne	.L21
	mov	x0, x22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	b	free
	.cfi_endproc
.LFE42:
	.size	ioopm_hash_table_destroy, .-ioopm_hash_table_destroy
	.align	2
	.p2align 4,,11
	.global	ioopm_hash_table_insert
	.type	ioopm_hash_table_insert, %function
ioopm_hash_table_insert:
.LFB44:
	.cfi_startproc
	mov	w3, 30841
	stp	x29, x30, [sp, -48]!
	.cfi_def_cfa_offset 48
	.cfi_offset 29, -48
	.cfi_offset 30, -40
	movk	w3, 0x7878, lsl 16
	mov	x29, sp
	smull	x3, w1, w3
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -16
	.cfi_offset 22, -8
	mov	x22, x2
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -32
	.cfi_offset 20, -24
	mov	w19, w1
	asr	x3, x3, 35
	sub	w3, w3, w1, asr 31
	add	w3, w3, w3, lsl 4
	sub	w3, w1, w3
	ldr	x21, [x0, w3, sxtw 3]
	ldr	x20, [x21, 16]
	cbz	x20, .L26
	ldr	w0, [x20]
	cmp	w1, w0
	bge	.L42
.L28:
	mov	x1, 24
	mov	x0, 1
	bl	calloc
	str	w19, [x0]
	stp	x22, x20, [x0, 8]
	str	x0, [x21, 16]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L42:
	.cfi_restore_state
	ldr	x21, [x20, 16]
	cbz	x21, .L30
	ldr	w0, [x21]
	cmp	w1, w0
	bge	.L43
	mov	x0, x21
	mov	x21, x20
	mov	x20, x0
	b	.L28
	.p2align 2,,3
.L43:
	ldr	x20, [x21, 16]
	cbz	x20, .L26
	ldr	w0, [x20]
	cmp	w1, w0
	blt	.L28
	mov	x0, x20
	bl	find_previous_entry_for_key.isra.0
	ldr	x20, [x0, 16]
	mov	x21, x0
	cbz	x20, .L28
	ldr	w0, [x20]
	cmp	w1, w0
	bne	.L28
	str	x22, [x20, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L30:
	.cfi_restore_state
	mov	x21, x20
.L26:
	mov	x20, 0
	b	.L28
	.cfi_endproc
.LFE44:
	.size	ioopm_hash_table_insert, .-ioopm_hash_table_insert
	.align	2
	.p2align 4,,11
	.global	ioopm_hash_table_lookup
	.type	ioopm_hash_table_lookup, %function
ioopm_hash_table_lookup:
.LFB45:
	.cfi_startproc
	mov	x0, 0
	ret
	.cfi_endproc
.LFE45:
	.size	ioopm_hash_table_lookup, .-ioopm_hash_table_lookup
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
