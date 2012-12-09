import java.util.Scanner;

public class GoGame
{
    private Goban _board;
    private int _turns;
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


		System.out.println("Enter X coodinate, enter 9000 to quit");
		int x = sc.nextInt();
		if(x == 9000)
		    break;
		System.out.println("Enter Y coordinate");
		int y = sc.nextInt();
		if(_turns%2 == 0)
		    {
			legalMove = _board.playStone(Color.BLACK, x, y);
			legalMove = (_board.capture(x, y) || legalMove);
		    }	
		else
		    {
			legalMove = _board.playStone(Color.WHITE, x, y);
			legalMove = (_board.capture(x, y) || legalMove);
		    }	
	      	
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
			    {
				legalMove = _board.playStone(Color.BLACK, x, y);
				if(_board.capture(x, y))
				  legalMove = true;
			    }	
			else
			    {
				legalMove = _board.playStone(Color.WHITE, x, y);
				if(_board.capture(x, y))
				  legalMove = true;
			    }	
		    }

		_turns++;
		System.out.println(_board.toString());    
	    }


    }

    public static void main(String[] args)
    {
	GoGame test = new GoGame();
	test.go();
    }

}