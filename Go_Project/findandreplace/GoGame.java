import java.util.Scanner;

public class GoGame
{
    private Goban _board;
    private int _turns;
    private int _passes;
    private double _komi;
    private boolean _heisen;
    private GameTreenode _current;
    private GameTreenode _root;

    private enum Korule
    {
	SIMPLE, POSITIONAL, SITUATIONAL;
    }
    private Korule _ko;

    public GoGame()
    {
	_board = new Goban();
	_passes = 0;
	_turns = 0;
	_komi = 6.5;
	_heisen = false;
	_root = _current = new GameTreenode();
	_ko = Korule.SIMPLE; //Ko rule set to simple by default

    }

    public void go()
    {
	System.out.println(_board.toString());
	boolean legalMove;
	Scanner sc = new Scanner(System.in);

	System.out.println("Press 1 to turn on HeisenGo, Press any other number to proceed normally.");
	_heisen = (sc.nextInt() == 1);

	while(true)
	    {
		int x, y;

		System.out.println("Enter X coodinate, enter -1 to quit and 0 to pass");
		x = sc.nextInt();
		if(x == 0)
		    _passes++;		
		else if(x == -1)
		    break;
		else
		    _passes = 0;		

		if(_passes == 2)
		    break;

		if(x != 0)
		    {
			System.out.println("Enter Y coordinate");
			y = sc.nextInt();

			if(_heisen)
			    {
				int distance = 0 ;
				int dx;
				int dy;
				boolean legal = false;

				while(!legal)
				    {
					double temp = (Math.random()*(64.2 + 13.1*4 + 4.2*8 + 0.2*12));
					if(temp > 64.2 + 13.1*4 + 4.2*8 + 0.2*12 - 0.0001)
					    {
						distance = 0;
						x = (int)(Math.random()*20);
						y = (int)(Math.random()*20);
					    }
					else if(temp > (64.2 + 13.1*4 + 4.2*8))
					    distance = 3;
					else if(temp > (64.2 + 13.1*4))
					    distance = 2;
					else if(temp > 64.2)
					    distance = 1;
					if(distance > 0)
					    {
						dx = (int)(Math.random()*distance + 1);
						dy = distance - dx;
						if(Math.random() > 0.5)
						    x = x + dx;
						else 
						    x = x - dx;
						if(Math.random() > 0.5)
						    y = y + dy;
						else
						    y = y - dy;
					    }
					if(_turns%2 == 0)
					    legal = _board.playStone(Affiliation.BLACK, x, y);
					else
					    legal = _board.playStone(Affiliation.WHITE, x, y);

				    }
			    }

			if(!_heisen)
			    {
				if(_turns%2 == 0)
				    legalMove = _board.playStone(Affiliation.BLACK, x, y);
				else
				    legalMove = _board.playStone(Affiliation.WHITE, x, y);
		    
				while(legalMove == false)
				    {	    
					System.out.println("Illegal Move try again");
				    
					System.out.println("Enter X coodinate");
					x = sc.nextInt();
					if(x == 9000)
					    break;
					System.out.println("Enter Y coordinate");
					y = sc.nextInt();
					if(_turns%2 == 0)
					    legalMove = _board.playStone(Affiliation.BLACK, x, y);
					else
					    legalMove = _board.playStone(Affiliation.WHITE, x, y);   	
				    }
			    }
		    }
		_turns++;
		System.out.println(_board.toString());    
	    }
	if(_passes == 2)
	    endGame(); 
    }

    private void endGame()
    {
	double whiteScore, blackScore;

	_board.paintTerritory();
	System.out.println(_board.toString());

	blackScore = _board.countTerritory(Affiliation.BLACK, "Chinese");
	whiteScore = _board.countTerritory(Affiliation.WHITE, "Chinese") + _komi;

	System.out.printf("Black: %.1f points  White: %.1f points\n", blackScore, whiteScore); 

	if(blackScore > whiteScore)
	    System.out.println("Black wins!");
	else
	    System.out.println("White wins!");	    
    }
    public static void main(String[] args)
    {
	GoGame test = new GoGame();
	test.go();
    }

}