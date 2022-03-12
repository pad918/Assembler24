.data
	primes: .space 400	# 100 spots to store primes
.text

ADDI $s7, 1023	# NUMBER OF PRIMES
ADDI $s6, 1000	# CURRENT PRIME
ADD $s6, $s6, $s6
ADD $s6, $s6, $s6	# t6 = 4000
LTA primes
ADD $s5, $0, $at	# SET s5 to primes array pointer

main:
	#INCREMENT ARGUMENT
	ADDI $s6, 1

	#TEST IF PRIME
	ADD $a0, $0, $s6
	JAL is_prime

	#WRITE TO ARRAY IF IS PRIME
	BZ $v0, skip
	ADD $at, $0, $s5
	STORE $s6, 0
	ADDI $s5, 4
	
	skip:

	#MAIN LOOP
	ADDI $s7, -1
	BNZ $s7, main

exit:
	ADD $0, $0, $0		# NOP TO END PROGRAM!

# Test if is prime
#	For every number m smaller than n, larger than 2:
#		Add m to k untill k>n,  (k-m) = n <==> n is dividable by m
#
# s4 = n
# s0 = m
#
is_prime:
	# PUSH $ra to stack
	ADD $at, $0, $sp	# LOAD SP to ACC
	STORE $ra, 0		# Zero offset
	ADDI $sp, -4		# Decrease sp

	ADD $s4, $0, $a0	# Spara argumentet i $s4
	ADD $s0, $0, $0
	ADDI $s0, 1			#Satt t0 till 1
	prime_loop:
		ADDI $s0, 1		# m++
		SUB $s2, $s0, $s4
		BZ $s2, end_loop	# end if m == n

		# Satt argument:
		ADD $a0, $0, $s4
		ADD $a1, $0, $s0
		JAL is_dividable
		BZ $v0, prime_loop	# loop

	end_loop:
		# Return !$v0
		ADD $t0, $0, $0 
		ADDI $t0, 1			# Satt t0 till 1
		SUB $v0, $t0, $v0	# Satt v0 till !(1-v0) <==> !v0

		# POP $ra from stack
		ADDI $sp, 4
		ADD $at, $0, $sp
		LOAD $ra, 0

		JR $ra, 0

# a0 = n, a1 is m
is_dividable:	
	ADD $v0, $0, $0		# Satt v0 till 0
	LTA 32768			#0x8000 (TOP BIT on)
	ADD $t0, $0, $0		#Set t0 to zero
	div_loop:
		ADD $t0, $t0, $a1	# t0 += m

		# Continue if t0 < n
		SUB $t1, $t0, $a0	# t1 = t0 - n, (t1<0 ==> n>t0)
		AND $t1, $at, $t1	# Select top bit of t1
		BNZ $t1, div_loop	#
	
	# Test if t0 == n
	SUB $t0, $t0, $a0
	BZ $t0, is_div
	BZ $0, end		#Return if not n==t0
	is_div:
		ADDI $v0, 1	#Retrun true
	end:
		JR $ra, 0	# RI needs two arguments, but only arg[0] is used
		