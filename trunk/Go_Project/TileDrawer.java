/**
 * @(#)TileDrawer.java
 *
 *
 * @author kjyuen2
 * @version 1.00 2012/12/7
 */
 
 import javax.swing.JPanel;
 import java.awt.Color;
 import java.awt.*;

public class TileDrawer extends JPanel{
	
	private final int cellSpace = 5;
 	private final int StoneSize = 5;
 	private int dimension = 0;
 	
 	Location[][] _board;

    public TileDrawer(Location[][] board) {
    	_board = board;
    	dimension = board.length;

    }
    
    public void paint(Graphics graphics){
    	Graphics2D g = (Graphics2D)graphics;
    	
    	// drawing the board
    	Color brown = new Color(156, 93, 82);
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
    			g.setColor(_board[i][j].getAffiliation());
    			if (_board[i][j].getOccupied())
    				g.fillOval(i*cellSpace, j*cellSpace, StoneSize, StoneSize);
    		}
    }
}