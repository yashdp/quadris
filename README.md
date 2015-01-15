How to Play:
There are 2 versions of this game – text-based and Graphical
Both versions will patiently awaiting your commands
The 3 rows at the top are reserve rows: You may freely rotate in these rows
before actually moving or drop the block
All blocks will be created on the top left corner. The game is over if there’s not
enough room on the board to drop the block right on that spot


All available commands:
• left – moves block 1 space to the left
• right – moves block 1 space to the right
• down – moves block 1 space down
• clockwise – rotates the block 90 degrees clockwise
• counterclockwise – rotates the block 90 degrees counterclockwise
• drop – drops the block as far down as possible
• levelup – increase the difficulty level by 1
• leveldown – decrease the difficulty level by 1
• restart – new game

Quadris also recognize multipliers to speed up gameplay. For example, “5right”
for moving 5 spaces to the right, “10down” for moving block 10 spaces down
It will also recognize half-completed commands. For example, “3l” for “3left”, and
“5do” for “5down”
Ambiguous commands will be ignored, such commands includes “r”, “d”, “l”
Quadris supports the following parameters for command line interface (CLI):
•text
•seed X
•scriptfile X
•startlevel X
•startlevel X
•keyboard
text – runs text version only, the default is to run in Graphic version
seed X – randomly generates blocks sequence
scriptfile X – uses file X instead of sequence.txt for blocks in level 0
startlevel X – starts the game in level X, the default is to start at level 0
