.data
arr: .space 16      # 4 word long array

.text
# INTERNAL FILE
# Factorial using only addition and branching
    ADDI $a0, 12    # Satt parametern
# a0, argumnet
# a1 = a0-1, argument minus one
# v0, totala summan
#
fact:
    ADD $v0, $0, $0     # Satt v0 till 0
    ADDI $v0, 1         # Satt v0 till 1 och returnera om argumentet ar noll, annars berakna N!
    BZ $a0, end         # Return 1 om argumentet ar noll
    
    ADD $a1, $a0, $0
    ADDI $a1, -1        # Satt $a1 till $a0 - 1

    ADD $a3, $0, $0         # set v0 to zero
    ADD $v0, $zero, $a0     # Move $a0 till $v0

    fact_loop:
        BZ $a1, end   # Om a1 = 0 ar berakningen klar, avsluta
        mul_loop: # For ($a1!=0; $a1--)
            BZ $a1, end_loop
            ADD $a3, $a3, $v0   # $a3 += $v0
            ADDI $a1, -1        # $a1--       
            BZ $zero, mul_loop  #Unconditional branch, skriver inte over $ra som JAL hade gjort

        end_loop:
        ADD $v0, $zero, $a3     # Uppdatera adder
        ADD $a3, $zero, $zero
        ADDI $a0, -1            # Minska a0 med 1

        ADD $a1, $a0, $0        # Satt $a1 till $a0 - 1
        ADDI $a1, -1        
        
        BZ $zero, fact_loop
    end:
        ADD $0, $0, $0          #NOP instruction