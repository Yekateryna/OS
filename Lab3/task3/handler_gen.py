with open("handlers.c","w") as f:
	f.write("//auto gen start\n")
	for i in range(1,33):
		f.write("void handler"+str(i)+'(void)\n{\n\tsleep(1);\n\tprintf("handler'+str(i)+'\\'+'n'+'");\n}\n\n')
	f.write("//auto gen end")

with open("handlers.h","w") as f:
	f.write("//auto gen start\n")
	for i in range(1,33):
		f.write('void handler'+str(i)+'(void);\n')
	f.write("//auto gen end")