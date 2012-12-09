import java.awt.Color;
import java.awt.*;

public class TileDrawer{
	
	private final int cellSpace = 5;
 	private final int StoneSize = 5;
 	private int dimension = 0;
 	
 	Color brown = new Color(156, 93, 82);
 	
 	Goban _board;

    public TileDrawer(Goban board) {
    	_board = board;
    	dimension = _board.getSize();

    }
    
    public void init(Graphics graphics){
    	Graphics2D g = (Graphics2D)graphics;
    	
    	// drawing the board
    	g.setColor(brown);
    	g.fillRect(0, 0, cellSpace*dimension, cellSpace*dimension);
    	
    	// drawing the lines
    	g.setColor(Color.DARK_GRAY);
    	for (int i = 0; i < dimension; i++){
    		g.drawLine(i*cellSpace, 0, i*cellSpace, dimension*cellSpace);
    		g.drawLine(0, i*cellSpace, dimension*cellSpace, i*cellSpace);
    	}
    			
    	
    	// drawing stones with their color
    	for(int i = 0; i < dimension; i++)
    		for(int j = 0; j < dimension; j++){
		    switch(_board.getLocation(i, j).getAffiliation()){
    				case BLACK: g.setColor(Color.BLACK); break;
    				case WHITE: g.setColor(Color.WHITE); break;
    				default: g.setColor(brown);
    			}
		    if (_board.getLocation(i, j).getOccupied())
    				g.fillOval(i*cellSpace, j*cellSpace, StoneSize, StoneSize);
    		}
    }
    
    public void paint(int x, int y, Color side, Graphics graphics){
    	// assumes the checks have been made
    	Graphics2D g = (Graphics2D)graphics;
    	if (side != Color.WHITE && side != Color.BLACK){
    		g.setColor(brown);
    		g.fillOval(x*cellSpace, y*cellSpace, StoneSize, StoneSize);
    	} else {
    		g.setColor(side);
    		g.fillOval(x*cellSpace, y*cellSpace, StoneSize, StoneSize);
    	}
    }
    
    public static void main(String [] args){
    	Goban ban = new Goban();
    	TileDrawer draw = new TileDrawer(ban);
    	ban.playStone(Affiliation.WHITE, 1, 8);
    }
}