.name "zork2"
.comment "I'M ALIIIIVE"

l2:		st r1, :live
		and r1, %0, r1

live:
		zjmp %:live
