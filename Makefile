my_shell:
	gcc my_shell.c -o my_shell.out

sample:
	gcc ./docs/sample.c -o sample.out

clean:
	rm -f *.out