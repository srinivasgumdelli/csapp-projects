public class GoGame
{
    private Goban _board;
    private int _turns;
    private GameTreenode current;
    private GameTreenode root;

    public GoGame()
    {
	_board = new Goban();
	turns = 0;
	root = current = new GameTreenode;
    }


}