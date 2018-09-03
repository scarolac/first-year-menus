play_connect4.exe: connect4.h play_connect4.cxx game.o connect4.o
	g++ -Wall -gstabs play_connect4.cxx game.o connect4.o -o play_connect4

play_othello.exe: othello.h play_othello.cxx game.o othello.o
	g++ -Wall -gstabs play_othello.cxx game.o othello.o -o othello

game.o: game.h game.cxx
	g++ -Wall -gstabs -c game.cxx

connect4.o: connect4.h game.h connect4.cxx
	g++ -Wall -gstabs -c connect4.cxx

othello.o: othello.h game.h othello.cxx
	g++ -Wall -gstabs -c othello.cxx
