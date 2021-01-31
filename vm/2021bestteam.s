.name "man i said you got trouble"
.comment "one, two, free, four. i wanna live forevere i wana live forever dont ask me anymore 
i wanna live forever"

start:
	sti		r1, %:live, %1
	sti		r1, %:living, %1
live:
	live %2
wall:
	and r3, r3, r3
	ld %12, r4
	ld %-50, r8
	ld %10, r9
	ld %-1, r10
	live %1
	and r3, r3, r3
	fork %:here
	zjmp %:live
here:
		live %2
living:
		live %1
