twixt: main.c board.c game.c play.c
	gcc main.c board.c game.c play.c -o twixt

clean:
	rm -f twixt
 