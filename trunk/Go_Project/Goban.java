public class Goban
{

    Location[][] board = new Location[19][19];

    public Goban()
    {
	for(int i = 0; i < Location.length; i++)
	    for(int j = 0; j < Location[0].length; j++)
		Location[i][j] = new Location();
    }


    public boolean playStone(Color c, Location l)
    {
	boolean ret;
	if(l.getIsOccupied())
	    {
		ret = false;
	    }
	else
	    {
		ret = true;
		l.toggleIsOccupied();
		l.setAffiliation(c);
	    }
	return ret;
    }

    public boolean playStone(Color c, int x, int y)
    {
    }

}