# Penguins
Project created for Computer Science study - written in C language

To run this program is necessary to use Command Line Parameters. For Linux OS:
- ./a.out generate_board board.txt (to generate random board, which will be saved in .txt file and to add players)
- ./a.out show_board board.txt(to show board in the terminal)
- ./a.out phase=placement penguins=3 board.txt board.txt (to place penguins on the tiles)
- ./a.out show_data board.txt(to show data of players)
- ./a.out id board.txt (to show id of current player)
- ./a.out phase=movement board.txt board.txt (to move the penguin)

On the tile:
- first number is number of fish
- the second number represents the player's number when penguin is placed on this tile or 0 when tile is not occupied.
