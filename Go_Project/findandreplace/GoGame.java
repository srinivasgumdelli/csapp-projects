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

    private TileDrawer _gui;

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

    public GoGame(TileDrawer drawer)
    {
	this();
	_gui = drawer;
    }

    public boolean setHeisen(boolean x)
    {
	_heisen = x;
	return _heisen;
    }

    public void updateGui()
    {
	Affiliation currentLocAff;
	for(int j = _board.getSize(); j > 0; j--)
	    for(int i = 1; i <= _board.getSize(); i++)
		{
		    currentLocAff = _board.getLocation(i, j).getAffiliation();
		    if(currentLocAff == Affiliation.WHITE || currentLocAff == Affiliation.BLACK)
			{
			    _gui.addStone(i, 1 + _board.getSize() - j, currentLocAff);
			}
		}
    }

    /**
     * Fuction to play move called by the gui, normally returns true, returns
     * false when the game is over.  Takes two ints as parameters, if either are
     * -1 it will interpret it as a pass.
     */
    public boolean makeMove(int x, int y)
    {
	boolean ans = true;
	boolean legalMove;
	Affiliation currentPlayer;

	if(x == -1 || y == -1)
	    {
		_passes++;
		_turns++;
	    }
	else
	    {
		if(_turns%2 == 0)
		    currentPlayer = Affiliation.BLACK;
		else
		    currentPlayer = Affiliation.WHITE;
		if(_heisen)
		    {
			int loopCounter = 0;
			int[] coord = {x, y};
			int[] randomCoord = heisenfy(coord, false);
			x = randomCoord[0];
			y = randomCoord[1];
			legalMove = _board.playStone(currentPlayer, x, y);
			while(!legalMove)
			    {
				loopCounter++;
				if(loopCounter < 1000)
				    randomCoord = heisenfy(coord, false);
				else
				    randomCoord = heisenfy(coord, true);
				x = randomCoord[0];
				y = randomCoord[1];
				legalMove = _board.playStone(currentPlayer, x, y);
			    }
			_passes = 0;
			_turns++;;     	
		    }
		else
		    {
		
			legalMove = _board.playStone(currentPlayer, x, y);     	
			if(legalMove)
			    {
				_passes = 0;
				_turns++;
			    }
		    }
	    }

	if(_passes == 2)
	    ans = false;
	return ans;
    }

    /**
     * HeisenGo function to introduce randomness, takes in a array of 
     * size 2 {x,y} and a boolean and returns a new array with randomized 
     * cooordinates.  If the boolean value is true, it will eschew the normal 
     * selection process and pick a totally random coordinate.  Boolean will be
     * set to true if is has been called too many times(see makeMove above).
     */
    private int[] heisenfy(int[] coord, boolean over)
    {
	int[] ans = new int[2];
	int distance = 0 ;
	int dx;
	int dy;

	int x = coord[0];
	int y = coord[1];

	if(over)
	    {
		distance = 0;
		x = (int)(Math.random()*20);
		y = (int)(Math.random()*20);
	    }
	else
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
	    }
	ans[0] = x;
	ans[1] = y;
	return ans;				 			    
    }

    public String endGame()
    {
	String ans;
	double whiteScore, blackScore;

	_board.paintTerritory();


	blackScore = _board.countTerritory(Affiliation.BLACK, "Chinese");
	whiteScore = _board.countTerritory(Affiliation.WHITE, "Chinese") + _komi;

	ans  = String.format("Black: %.1f points  White: %.1f points   \n", blackScore, whiteScore); 

	if(blackScore > whiteScore)
	    ans += ("Black wins!");
	else
	    ans += ("White wins!");	  
	return ans;  
    }

    //Just a method we used to test things in text mode
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
	    {
		System.out.println(endGame()); 
		System.out.println(_board.toString());
	    }
    }

    public static void main(String[] args)
    {
	GoGame test = new GoGame();
	test.go();
    }

}