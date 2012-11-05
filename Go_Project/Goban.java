public class Goban
{

    Location[][] _board;

    public Goban()
    {
	_board = new Location[19][19];
	for(int i = 0; i < _board.length; i++)
	    for(int j = 0; j < _board[0].length; j++)
		_board[i][j] = new Location();
    }

 
    public boolean checkCapture(int x, int y)
    {
	boolean ret;
	Color ownColor = _board[x][y].getAffiliation();
	//System.out.println(ownColor);
	boolean hasBlankNeighbors = 
	    !((_board[x][y + 1]).getOccupied() &&
	      (_board[x + 1][y]).getOccupied() &&
	      (_board[x][y - 1]).getOccupied() &&
	      (_board[x - 1][y]).getOccupied());
	//System.out.println(hasBlankNeighbors);
	boolean upUnchecked =
	    (((_board[x][y + 1]).getAffiliation()).equals(ownColor) &&
	     !((_board[x][y + 1]).getChecked()));
	boolean rightUnchecked =
	    (((_board[x + 1][y]).getAffiliation()).equals(ownColor) &&
	     !((_board[x + 1][y]).getChecked()));
	boolean downUnchecked =
	    (((_board[x][y - 1]).getAffiliation()).equals(ownColor) &&
	     !((_board[x][y - 1]).getChecked()));
	boolean leftUnchecked =
	    (((_board[x - 1][y]).getAffiliation()).equals(ownColor) &&
	     !((_board[x - 1][y]).getChecked()));
	//System.out.println((upUnchecked || rightUnchecked || downUnchecked || leftUnchecked));
	if((_board[x][y]).getOccupied())
	    {
		if(hasBlankNeighbors)
		    ret = false;
		else if(upUnchecked || rightUnchecked || downUnchecked || leftUnchecked)
		    {
			(_board[x][y]).setChecked(true);
			ret = 
			    (upUnchecked ? checkCapture(x, y + 1) : true) &&
			    (rightUnchecked ? checkCapture(x + 1, y) : true) &&
			    (downUnchecked ? checkCapture(x, y - 1) : true) &&
			    (leftUnchecked ? checkCapture(x - 1, y) : true);
		    }
		else
		    ret = true;
	    }		
	else
	    {
		System.out.println
		    ("Warning, checkCapture called on empty location");
		ret = false;
	    }
	return ret;
    }
	    
    public boolean playStone(Color c, Location l)
    {
	boolean ret;
	if(l.getOccupied())
	    {
		ret = false;
	    }
	else
	    {
		ret = true;
		l.setOccupied(true);
		l.setAffiliation(c);
	    }
	return ret;
    }

    public boolean playStone(Color c, int x, int y)
    {
	boolean ret;
	if(x < _board.length && y < _board[0].length)
	    ret = this.playStone(c, _board[x][y]);
	else 
	    ret = false;
	return ret;
    }

    public boolean removeStone(Location l)
    {
	boolean ret;
	if(l.getOccupied())
	    {
		l.setOccupied(false);
		l.setChecked(false);		
		l.setAffiliation(Color.NONE);
		ret = true;
	    }
	else
	    {
		ret = false;
	    }
	return ret;
    }

    public boolean removeStone(int x, int y)
    {
	boolean ret;
	if(x < _board.length && y < _board[0].length)
	    ret = this.removeStone(_board[x][y]);
	else
	    ret = false;
	return ret;
    }
    public Location getLocation(int x, int y)
    {
	Location ret = new Location();
	if(x < _board.length && y < _board[0].length)
	    ret =  _board[x][y];
	return ret;
    }

    public String toString()
    {
	String ans = "";
	for(int j = _board[0].length - 1; j >= 0; j--)
	    {
		for(int i = 0; i < _board.length; i++)
		    ans += _board[i][j].getAffiliation();
		ans += "\n";
	    }
	return ans;
    }

    public static void main(String [] args)
    {
	Goban ban = new Goban();
	System.out.println(ban.toString());
	ban.playStone(Color.WHITE, 1, 8);
	ban.playStone(Color.WHITE, 0, 0);
	ban.playStone(Color.WHITE, 18, 18);
	ban.playStone(Color.BLACK, 2, 8);
	ban.playStone(Color.BLACK, 18, 18);
	ban.playStone(Color.BLACK, 0, 0);
	System.out.println(ban.toString());
	if(ban.removeStone(0, 0))
	    if(ban.removeStone(18, 18))
		{
		    ban.playStone(Color.BLACK, 18, 18);
		    System.out.println((ban.getLocation(18,18)).toString());
		    ban.playStone(Color.BLACK, 0, 0);
		    System.out.println(ban.toString());
		}

	ban = new Goban();
	ban.playStone(Color.WHITE, 10, 10);
	ban.playStone(Color.BLACK, 10, 11);
	ban.playStone(Color.BLACK, 11, 10);
	ban.playStone(Color.BLACK, 10, 9);
	ban.playStone(Color.BLACK, 9, 10);
	System.out.println(ban.toString());
	System.out.println(ban.checkCapture(10, 10));
	ban.removeStone(10,10);
	System.out.println(ban.toString());

	ban = new Goban();
	ban.playStone(Color.WHITE, 10, 10);
	ban.playStone(Color.WHITE, 10, 11);
	ban.playStone(Color.WHITE, 11, 10);
	ban.playStone(Color.WHITE, 10, 9);
	ban.playStone(Color.WHITE, 9, 10);
	ban.playStone(Color.BLACK, 10, 12);
	ban.playStone(Color.BLACK, 11, 11);
	ban.playStone(Color.BLACK, 12, 10); 
	ban.playStone(Color.BLACK, 9, 11);
	ban.playStone(Color.BLACK, 8, 10);
	ban.playStone(Color.BLACK, 10, 8);
	ban.playStone(Color.BLACK, 11, 9);
	ban.playStone(Color.BLACK, 9, 9);
	System.out.println(ban.toString());
	System.out.println(ban.checkCapture(10,10));
    }//passes tests so far

}
