import java.util.Scanner;

public class GoGame
{
    private Goban _board;
    private int _turns;
    private int _passes;
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
	_root = _current = new GameTreenode();
	_ko = Korule.SIMPLE; //Ko rule set to simple by default

    }

    public void go()
    {
	System.out.println(_board.toString());
	boolean legalMove;

	while(true)
	    {

		Scanner sc = new Scanner(System.in);
		int x, y;

		System.out.println("Enter X coodinate, enter 9000 to quit, 9001 to pass");
		x = sc.nextInt();
		if(x == 9001)
		    _passes++;		
		else if(x == 9000)
		    break;
		else
		    _passes = 0;		

		if(_passes == 2)
		    break;

		if(x != 9001)
		    {
			System.out.println("Enter Y coordinate");
			y = sc.nextInt();
			if(_turns%2 == 0)
			    legalMove = _board.playStone(Color.BLACK, x, y);
			else
			    legalMove = _board.playStone(Color.WHITE, x, y);
		    
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
				    legalMove = _board.playStone(Color.BLACK, x, y);
				else
				    legalMove = _board.playStone(Color.WHITE, x, y);   	
			    }
		    }
		_turns++;
		System.out.println(_board.toString());    
	    }
	if(_passes == 2)
	    {
		_board.paintTerritory();
		System.out.println(_board.toString());
	    }
    }

    public static void main(String[] args)
    {
	GoGame test = new GoGame();
	test.go();
    }

}