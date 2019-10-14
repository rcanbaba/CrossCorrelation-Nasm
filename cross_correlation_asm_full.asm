;Recap Can BABAOĞLU
;150130112
segment .text
global cross_correlation_asm_full

section .data
	varC: dd 0
	varA: dd 0
	varH: dd 0
	
cross_correlation_asm_full:
	push ebp
	mov ebp,esp		
	mov edx,[ebp+28] ; outputSize	
	mov ecx,[ebp+24] ; outputArray address
	mov ebx,0 ; counter
	mov eax,0 ; zero value
	
clear_output_array:
	mov [ecx],eax
	add ecx,4
	inc ebx
	cmp ebx,edx
	jl clear_output_array

while_1: ; a < arr1_size
	mov ebx,[varA] ; varA
	mov ecx,[ebp+12] ; arr1_size
	cmp ebx,ecx ;a ? arr1_size
	jge end_while
	
atamalar: ; c = a
	mov ecx,[ebp+20] ; arr2_size
	mov [varH],ecx ; H = arr2_size
	mov ebx,[varA] ; ebx = varA
	mov [varC],ebx ; C = A
	mov ecx,[varH] ; H
	mov eax,0 ; 0
	cmp ecx,eax ; H ? 0
	jg while_2 ; H > 0 
	jmp incrementA
while_2: ;H > 0 
	mov ebx,[ebp+8] ; arr1_adress
	mov ecx,[varA] ; varA
	mov edx,[ebx+ecx*4] ; edx = arr1[varA]
	mov ebx,[ebp+16] ; arr2_adress
	mov ecx,[varH] ; varH
	dec ecx ; varH-1
	mov eax,[ebx+ecx*4] ; eax = arr2[varH-1]
	imul edx,eax ; edx = arr1[varA] * arr2[varH-1] -----
	mov ebx,[varC]
	mov eax,[ebp+24] ; outputArray address
	mov ecx,[eax+ebx*4] ; output[varC]	
	add ecx,edx ; output[varC] = output[varC] + arr1[varA] * arr2[varH-1
	mov [eax+ebx*4],ecx
	mov ebx,[varC]	
	inc ebx; varC ++
	mov [varC],ebx
	mov ebx,[varH]
	dec ebx
	mov [varH],ebx
	mov ebx,[varH]
	mov ecx,0
	cmp ebx,ecx
	jg while_2 
	jmp incrementA	
	;jmp print
	
incrementA:
	mov ebx,[varA]
	inc ebx
	mov [varA],ebx
	jmp while_1

end_while:
	xor eax,eax; clear EAX
	
zero_count: ;check output_array for 0 count
	mov ebx,[ebp+24] ; outputArray address
	mov edx,[ebp+28] ; outputSize
	mov ecx,0 ; zero
comparison:
	cmp [ebx],ecx
	jne increment
	jmp array_slide
increment:
	inc eax
array_slide:
	add ebx,4
	dec edx
	jnz comparison
	
print:	
	;mov eax,ecx ; burayı unutma kontrol kısmı
	mov ecx,0
	mov [varA],ecx ; clear all variables
	mov [varC],ecx
	mov [varH],ecx
end:
	pop ebp
	ret
