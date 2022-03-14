.text
print_arr:
	LTA arr
	ADD $t0, $0, $0
	ADDI $t0, 16
	print_char:
		ADDI $t0, -1
		#LOAD CHARACTER:
		LOAD $t1, 0
		SEND $t1, 0		# PRINT char	
		ADDI $at, 4
		BNZ $t0, print_char
	JR $ra, 0	# Return