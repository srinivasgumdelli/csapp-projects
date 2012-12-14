HeisenGo 
========

Welcome to HeisenGo, the non-deterministic Go game.  This program allows two people to play either a normal game of go toghether, or turn on the option for HeisenGo mode where the location you enter may no be exactly where your stone is placed.  HeisenGo mode can be a useful teaching tool for new players, forcing them to focus more on strategy and the overall "shape" of their stones as opposed to close quarters combat and capturing.  For more experienced players it is not recommended for learning since at higher levels even a distance of one or two spaces can make a big difference even when the overall shape is preserved.  However, it still can serve as a fun change of pace should one grow weary of the original rules.
  
Information about the game of go cna be found here: http://en.wikipedia.org/wiki/Go_%28game%29

To compile and run the game, simply running these commands should work:

javac Main.java

followed by

java Main




Features:

-- Enforces the rules of Go

   - Removes captured stones

   - Rejects illegal moves
     - Note: As of now no Ko(infinite loop) rule as been implemented(even though there is a variable for storing it in GoGame) so it is technically possible to play a never-ending game.
       - Aside from this, all rules are enforced.

   - Counts score at the end of the game and declares winner
     - White recieves an extra 6.5 points of "komi" as conpensation for going second and to avoid draws.
     - Note: Scoring right now assumes all pieces on the board are "alive".
       - As of now there is no(practical) way to programmatically determine whether groups are dead or alive.  What qualifies as "dead" may sometimes even depend on who is playing.(More information about life and death in go can be found here: http://en.wikipedia.org/wiki/Life_and_death)
       - Therefore, in order for scoring to work properly, all dead groups must be properly captured and removed before the end of the game is triggered.  Any floating dead groups left on the board at the end will interfere with the scoring algorithm.
 
-- HeisenGo game mode that introduces random uncertainty

   - This can be turned on or off when the game is first started.

   - Note: There are no illegal moves in this mode.  If attempt to input an illegal coordiante the randomizer will still generate a legal play for you, even if the end result has to be very different from the original input.
