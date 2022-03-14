include test_include.asm

.data
	arr: .space 64      # 16 word long array
.text
	LTA arr

	# F
	ADD $s0, $0, $0
	ADDI $s0, 70	
	STORE $s0, 0

	# O
	ADD $s0, $0, $0
	ADDI $s0, 111	
	STORE $s0, 4

	# U
	ADD $s0, $0, $0
	ADDI $s0, 117	
	STORE $s0, 8

	# N
	ADD $s0, $0, $0
	ADDI $s0, 110	
	STORE $s0, 12

	# D
	ADD $s0, $0, $0
	ADDI $s0, 100	
	STORE $s0, 16

	# \n
	ADD $s0, $0, $0
	ADDI $s0, 10	
	STORE $s0, 20
	
	#Print array
	JAL print_arr

	#Exit
	ADD $0, $0, $0