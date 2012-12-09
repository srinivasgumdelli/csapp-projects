public class Goban
{

    Location[][] _board;
    int _size;
 
    /**
     * Constructor, _board is initialized to a size that is two units larger
     * than nessecary.  Only coordinates one through size are visible to user, 
     * the border is used to make the backend easier to code.
     */
    public Goban(int size)
    {
	_size = size;
	_board = new Location[size + 2][size + 2];
	for(int i = 0; i < _board.length; i++)
	    for(int j = 0; j < _board[0].length; j++)
		_board[i][j] = new Location();
    }

    public Goban()
    {
	this(19);
    }

    private boolean checkBounds(int x, int y )
    {
	return (x <= _size && x >= 1 && y <= _size && y >= 1); 
    }

    /**
     * capture takes in the coordinates of the LAST PIECE PLAYED
     * and checks the surrounding pieces for any to be removed
     *
     * @return true if any pieces are captured at all. 
     */
    public boolean capture(int x, int y)
    {
	boolean ret = false;
	boolean temp = false;
	if(this.checkBounds(x, y))
	    {
		if(this.checkCapture(x, y + 1))
		    {
			ret = true;
			temp = true;
		    }
		for(int i = 1; i <= _size; i++)
		    for(int j = 1; j <= _size; j++)
				
			if(_board[i][j].getChecked())
			    if(temp)
				this.removeStone(_board[i][j]);	       	
			    else
				_board[i][j].setChecked(false);
		temp = false;

		if(this.checkCapture(x - 1, y))
		    {
			ret = true;
			temp = true;
		    }
		for(int i = 1; i <= _size; i++)
		    for(int j = 1; j <= _size; j++)
				
			if(_board[i][j].getChecked())
			    if(temp)
				this.removeStone(_board[i][j]);	       	
			    else
				_board[i][j].setChecked(false);
		temp = false;

		if(this.checkCapture(x, y - 1))
		    {
			ret = true;
			temp = true;
		    }
		for(int i = 1; i <= _size; i++)
		    for(int j = 1; j <= _size; j++)
				
			if(_board[i][j].getChecked())
			    if(temp)
				this.removeStone(_board[i][j]);	       	
			    else
				_board[i][j].setChecked(false);
		temp = false;

		if(this.checkCapture(x + 1, y))
		    {
			ret = true;
			temp = true;
		    }
		for(int i = 1; i <= _size; i++)
		    for(int j = 1; j <= _size; j++)
				
			if(_board[i][j].getChecked())
			    if(temp)
				this.removeStone(_board[i][j]);	       	
			    else
				_board[i][j].setChecked(false);
		temp = false;
	    }
	return ret;

    }

    private void setBorder(Color c)
    {
	for(int i = 0; i < _board.length; i++)
	    {
		_board[0][i].setOccupied(true);
		_board[0][i].setAffiliation(c);

		_board[_board.length - 1][i].setOccupied(true);
		_board[_board.length - 1][i].setAffiliation(c);

		_board[i][0].setOccupied(true);
		_board[i][0].setAffiliation(c);

		_board[i][_board.length - 1].setOccupied(true);
		_board[i][_board.length - 1].setAffiliation(c);
	    }
    }

    /**
     * Helper function that returns whether the stone at a particular location
     * is part of a group that should be captured.  Kept private because it
     * alters the state of _board without restoring it, which could easily 
     * be lost track of in other classes.
     */
    private boolean checkCapture(int x, int y)
    {
	boolean ret = false;
	if(this.checkBounds(x, y))
	    {

		Color ownColor = _board[x][y].getAffiliation();
		if(ownColor == Color.WHITE)
		    this.setBorder(Color.BLACK);
		else if(ownColor == Color.BLACK)
		    this.setBorder(Color.WHITE);
		//System.out.println(ownColor);
		boolean hasBlankNeighbors = 
		    !(
		      (_board[x][y + 1]).getOccupied() &&
		      (_board[x + 1][y]).getOccupied() &&
		      (_board[x][y - 1]).getOccupied() &&
		      (_board[x - 1][y]).getOccupied()
		      );
		//System.out.println(hasBlankNeighbors);
		
		boolean upUnchecked, downUnchecked, rightUnchecked, leftUnchecked;	       
		upUnchecked =
		    (((_board[x][y + 1]).getAffiliation()).equals(ownColor) 
		     && !((_board[x][y + 1]).getChecked()));
		rightUnchecked =
		    (((_board[x + 1][y]).getAffiliation()).equals(ownColor) 
		     && !((_board[x + 1][y]).getChecked()));
		downUnchecked =
		    (((_board[x][y - 1]).getAffiliation()).equals(ownColor) 
		     && !((_board[x][y - 1]).getChecked()));
		leftUnchecked =
		    (((_board[x - 1][y]).getAffiliation()).equals(ownColor) &&
		     !((_board[x - 1][y]).getChecked()));
		//System.out.println((upUnchecked || rightUnchecked || downUnchecked || leftUnchecked));
		if((_board[x][y]).getOccupied())
		    {
			(_board[x][y]).setChecked(true);
			if(hasBlankNeighbors)
			    ret = false;
			else if(upUnchecked || rightUnchecked || downUnchecked || leftUnchecked)
			    {
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
	    }
	this.setBorder(Color.NONE);
	return ret;
    }


    public void paintTerritory()
    {
	for(int x = 1; x <= _size; x++)
	    for(int y = 1; y <= _size; y++)
		{
		    if(_board[x][y].getOccupied())
			{
			    if(!_board[x][y + 1].getOccupied())
				this.markTerritory(_board[x][y].getAffiliation(), x, y + 1);
			    if(!_board[x - 1][y].getOccupied())
				this.markTerritory(_board[x][y].getAffiliation(), x - 1, y);
			    if(!_board[x][y - 1].getOccupied())
				this.markTerritory(_board[x][y].getAffiliation(), x, y - 1);
			    if(!_board[x + 1][y].getOccupied())
				this.markTerritory(_board[x][y].getAffiliation(), x + 1, y);
			}
		}
    }

    private void markTerritory(Color c, int x, int y)
    {
	boolean valid = (checkBounds(x, y)) && 
	    (!(_board[x][y].getAffiliation() == c)) && 
	    (!_board[x][y].getOccupied());

	if(valid)
	    {
		if(c == Color.DISPUTED)
		    {
			_board[x][y].setAffiliation(Color.DISPUTED);
			this.markTerritory(Color.DISPUTED, x, y + 1);
			this.markTerritory(Color.DISPUTED, x + 1, y);
			this.markTerritory(Color.DISPUTED, x, y - 1);
			this.markTerritory(Color.DISPUTED, x - 1, y);
		    }
		else if( _board[x][y].getAffiliation() == Color.NONE)
		    {
			_board[x][y].setAffiliation(c);
			this.markTerritory(c , x, y + 1);
			this.markTerritory(c , x + 1, y);
			this.markTerritory(c , x, y - 1);
			this.markTerritory(c , x - 1, y);
		    }
		else 
		    this.markTerritory(Color.DISPUTED, x, y);
	    }
    }

    public boolean playStone(Color c, int x, int y)
    {
	boolean ret;
	boolean suicide;
	Location l = _board[x][y];

	if(this.checkBounds(x, y))
	    {
		if(l.getOccupied())
		    ret = false;
		else
		    {
			ret = true;
			l.setOccupied(true);
			l.setAffiliation(c);
			suicide = this.checkCapture(x, y);
			for(int i = 0; i < _board.length; i++)
			    for(int j = 0; j < _board[0].length; j++)
				(_board[i][j]).setChecked(false);
			if(suicide)
			    {
				if(!this.capture(x, y))
				    {
					this.removeStone(l);
					ret = false;
				    }
				else
				    ret = true;
			    }
		    }
	    }
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
	if(this.checkBounds(x, y))
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
	for(int j = _size; j > 0; j--)
	    {
		for(int i = 1; i <= _size; i++)
		    {
			String temp = "" +  _board[i][j].getAffiliation();
			if(temp.equals("BLACK"))
			    ans += " X";
			else if(temp.equals("WHITE"))
			    ans += " O";
			else
			    ans += " -";
		    }
		ans += "\n";
	    }
	return ans;
    }

    public static void main(String [] args)
    {
	Goban ban = new Goban();
	System.out.println(ban.toString());
	ban.playStone(Color.WHITE, 0, 8);
	ban.playStone(Color.WHITE, 1, 1);
	ban.playStone(Color.WHITE, 19, 19);
	ban.playStone(Color.BLACK, 2, 8);
	ban.playStone(Color.BLACK, 19, 19);
	ban.playStone(Color.BLACK, 1, 1);
	System.out.println(ban.toString());
	if(ban.removeStone(1, 1))
	    if(ban.removeStone(19, 19))
		{
		    ban.playStone(Color.BLACK, 19, 19);
		    System.out.println((ban.getLocation(18,18)).toString());
		    ban.playStone(Color.BLACK, 1, 1);
		    System.out.println(ban.toString());
		}

	ban = new Goban();
	ban.playStone(Color.WHITE, 10, 10);
	ban.playStone(Color.BLACK, 10, 11);
	ban.playStone(Color.BLACK, 11, 10);
	ban.playStone(Color.BLACK, 10, 9);
	ban.playStone(Color.BLACK, 9, 10);
	System.out.println(ban.toString());
	ban.capture(9, 10);	
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
	ban.capture(9, 9);	
	System.out.println(ban.toString());
	ban.markTerritory(Color.BLACK, 10, 10);
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
	ban.capture(9, 9);	
	System.out.println(ban.toString());

	ban.playStone(Color.WHITE, 9, 8);
	ban.playStone(Color.WHITE, 8, 9);
	ban.playStone(Color.WHITE, 10, 7);
	ban.playStone(Color.WHITE, 11, 8);
	ban.playStone(Color.WHITE, 12, 9);
	ban.playStone(Color.WHITE, 13, 10);
	ban.playStone(Color.WHITE, 7, 10);
	ban.playStone(Color.WHITE, 8, 11);
	ban.playStone(Color.WHITE, 9, 12);
	ban.playStone(Color.WHITE, 10, 13);
	ban.playStone(Color.WHITE, 11, 12);
	ban.playStone(Color.WHITE, 12, 11);
	ban.paintTerritory();
	System.out.println(ban.toString());
    }//passes tests so far

}
