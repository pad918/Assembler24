.data
	arr: .space 16      # 4 word long array

.text
	ADD $a0, $0, $0
	ADDI $a0, 3		# Satt $a0 till 3
loop:
	ADDI $a0, -1	# $a0 --
	LTA arr			# Load array pointer
	ADD $at, $at, $a1	 
	STORE $a0, 0	# Store at arr pointer
	ADDI $a1, 4		# $a1 += 4
	BNZ $a0, loop	# for(a0 = 3; $a0!=0; a0--)

end:
	ADD $0, $0, $0	# NOP