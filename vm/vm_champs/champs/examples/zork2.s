.name "zork2"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and 8, 8, r1

live:
		zjmp %:live
