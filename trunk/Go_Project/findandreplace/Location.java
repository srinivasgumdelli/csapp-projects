import java.util.Scanner;

public class Location
{
    boolean _isChecked; 
    boolean _isOccupied;
    Affiliation _affiliation;

    public Location()
    {
	_isChecked = false;
	_isOccupied = false;
	_affiliation = Affiliation.NONE;
    }

    public boolean getChecked()
    {
	return _isChecked;
    }

    /*public boolean getCurrentCheck()
    {
	return _currentCheck;
    }
    */

    public boolean getOccupied()
    {
	return _isOccupied;
    }

    public Affiliation getAffiliation()
    {
	return _affiliation;
    }

    /*public boolean setCurrentCheck(boolean q)
    {
	_currentCheck = q;
	return _currentCheck;
    }
    */
    public boolean setChecked(boolean q)
    {
	_isChecked = q;
	return _isChecked;
    }

    public boolean setOccupied(boolean q)
    {
	_isOccupied = q;
	return _isOccupied;
    }

    public void setAffiliation(Affiliation c)
    {
	_affiliation = c;
    }

    public String toString()
    {
	return ("isChecked: " + _isChecked +  "\n isOccupied: " + _isOccupied + "\n affiliation: " + _affiliation);
    }

    public static void main(String [] args)
    {
	Scanner stdin = new Scanner(System.in);
	Location l = new Location();
	String input = "";
	System.out.println("press q to quit");
	while(!input.equals("q"))
	    {
		input = stdin.nextLine();
		if(input.equals("tc"))
		    l.setChecked(!l.getChecked());
		/*else if(input.equals("tcc"))
		  l.setCurrentCheck(!l.getCurrentCheck());*/
		else if(input.equals("to"))
		    l.setOccupied(!l.getOccupied());
		System.out.println(l.toString());
	    }
	l.setAffiliation(Affiliation.WHITE);
	System.out.println(l.toString());
	l.setAffiliation(Affiliation.BLACK);
	System.out.println(l.toString());
    }//tests pass
    

}