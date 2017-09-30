
	.equ COEF1, 3483
	.equ COEF2, 11718
	.equ COEF3, 1183

	.text

	.global rgb2gray
	.global div16384
  	.global apply_gaussian
	.global Gray2BinaryMatrix
	.global MaximoGris

	@ return (3483*pixel->R + 11718*pixel->G + 1183*pixel->B) /16384;
rgb2gray:
		push {r4 - r7, lr}
		mov r7, #0

		ldrb r4,[r0] @ R
		ldr r5, =COEF1
		mul r6, r4, r5
		add r7, r7,r6
		add r0, r0, #1

		ldrb r4,[r0] @ G
		ldr r5, =COEF2
		mul r6, r4, r5
		add r7, r7,r6
		add r0, r0, #1

		ldrb r4,[r0] @ B
		ldr r5, =COEF3
		mul r6, r4, r5
		add r7, r7,r6
		add r0, r0, #1

		mov r0, r7
		bl div16384

		pop {r4 - r7, lr}
		mov pc, lr

div16384:
		lsr r0, r0, #14
		mov pc, lr





apply_gaussian:
	@ r0 <- dir(im1[])
	@ r1 <- dir(im2[])
	@ r2 <- width == columnas
	@ r3 <- height == filas
	push {r4 - r7, lr}

	mov r4, #0 @ i = 0
	for1: cmp r4, r3
		bge fin_for1
		mov r5, #0 @ j = 0
		for2: cmp r5, r2
			bge fin_for2

			push {r0 - r3}
			// colocar parametros para gaussian
						@ r0 <- dir(im1[])
			mov r1, r2	@ r1 <- width == columnas
			mov r2, r3	@ r2 <- height == filas
			mov r3, r4	@ r3 <- i
			push {r5}	@ Quinto parametro por pila <- j
			bl gaussian	@ gaussian(im1, width, height, i, j);
			pop {r5}

			mov r6, r0 @ r6 <- return gaussian
			pop {r0 - r3}

			mla r7, r4, r2, r5 @ r7 <- i*columnas + j
			strb r6, [r1, r7] @ dir(r1 + r7) <- r6

			add r5, r5, #1 @ j++
			b for2
		fin_for2:

		add r4, r4, #1  @ i++
		b for1
	fin_for1:

	pop {r4 - r7, lr}
	mov pc, lr


Gray2BinaryMatrix:
	@ r0 <- dir(orig[])
	@ r1 <- dir(dest[])
	@ r2 <- umbral
	@ r3 <- nfilas
	@ pila <- ncols
	push {r4 - r8}		@ 5 registros
	ldr r4, [sp, #20]	@ 5*4

	mov r5, #0 @ i = 0
	for11: cmp r5, r3
		bge fin_for11
		mov r6, #0 @ j = 0
		for22: cmp r6, r4
			bge fin_for22

			mla r7, r5, r4, r6	@ r7 <- i*ncols + j
			ldrb r8, [r0, r7]	@ r8 <- dir(r0 + r7)
			if: cmp r8, r2
			bge else
				mov r8, #0
				strb r8, [r1, r7] @ dir(r1 + r7) <- r8
			b end_if
			else:
				mov r8, #255
				strb r8, [r1, r7] @ dir(r1 + r7) <- r8
			end_if:

			add r6, r6, #1 @ j++
			b for22
		fin_for22:

		add r5, r5, #1  @ i++
		b for11
	fin_for11:
	pop {r4 - r8}
	mov pc, lr


MaximoGris:
	@ r0 <- dir(imagenGris)
	@ r1 <- N
	@ r2 <- M
	@ r3 <- dir(imagenMax)
	push {r4 - r9}
	mov r4, #0 @ i = 0
	for111: cmp r4, r1
		bge fin_for111

		mov r6, #-1 @ col = -1
		mov r7, #-1 @ max = -1

		mov r5, #0 @ j = 0
		for222: cmp r5, r2
			bge fin_for222

			mla r8, r4, r2, r5 @ r7 <- i*columnas + j
			ldrb r9, [r0, r8]
			if_1: cmp r9, r7
				ble end_if_1

				mov r7, r9 @ max = imagenGris[i][j]
				mov r6, r5 @ col = j

			end_if_1:
			add r5, r5, #1 @ j++
			b for222
		fin_for222:
		str r6, [r3]		@ imagenMax[i].col = col
		add r3, r3, #4		@ dir(imagenMax)+4
		str r7, [r3] 		@ imagenMax[i].max = max
		add r3, r3, #4		@ dir(imagenMax)+4

		add r4, r4, #1  @ i++
		b for111
	fin_for111:
	pop {r4 - r9}
	mov pc, lr


  	.end


