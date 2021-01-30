.name "man i said"
.comment "one, two, free, four. I wanna live "forevere I wana live forever dont ask me anymore 
I wanna live forever""

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
	sti r4, %:here, %0
	sti r9, %:here, %1
	sti r8, %:here, %2
	sti r9, %-50, %0
	sti r10, %-50, %1
	sti r8, %-50, %2
	sti  r2, %-50, %3
here:
		live %2
living:
		live %1
