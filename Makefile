main: main.o operation.o job.o processPlan.o file.o func.o
	gcc -o main main.o operation.o job.o processPlan.o file.o func.o

main.o operation.o job.o processPlan.o file.o func.o: main.c class/operation/operation.c class/job/job.c class/processPlan/processPlan.c utils/file/file.c utils/func/func.c
	gcc -c main.c class/operation/operation.c class/job/job.c class/processPlan/processPlan.c utils/file/file.c utils/func/func.c
