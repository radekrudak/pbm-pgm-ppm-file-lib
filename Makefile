default: 
	gcc -g -o pbm pbm_example.c  -lm
	gcc -g -o pgm pgm_example.c  -lm
pbm:pbm_example.c
	gcc -g -o pbm pbm_example.c  -lm
pgm:pgm_example.c
	gcc -g -o pgm pgm_example.c  -lm
