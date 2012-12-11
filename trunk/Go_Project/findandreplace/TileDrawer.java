import java.awt.Color;
import java.awt.*;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TileDrawer extends JPanel implements ActionListener{
	
	private final int cellSpace = 20;
 	private final int StoneSize = 20;
 	private int dimension = 19;
 	
 	Color brown = new Color(156, 93, 82);
 	_board = 
 	
 	Goban _board;
 	
 	private void init(){
 		repaint();
 	}
 	
 	public TileDrawer(){
 		init();
 	}
 	
 	public void paintComponent(Graphics g){
 		super.paintComponents(g);
 		Graphics2D g2d = (Graphics2D)g;
 		
 		g2d.setColor(brown);
    	g2d.fillRect(50, 50, cellSpace*dimension, cellSpace*dimension);
    	
    	// drawing the lines
    	g2d.setColor(Color.DARK_GRAY);
    	for (int i = 0; i < dimension+1; i++){
    		g2d.drawLine(i*cellSpace+50, 50, 50+i*cellSpace, 50+dimension*cellSpace);
    		g2d.drawLine(50, i*cellSpace+50, 50+dimension*cellSpace, 50+i*cellSpace);
    	}
 	}
 	
 	public void paint(int x, int y, Affiliation aff){
 		Graphics g = getGraphics();
 		super.paint(g);
 		
 		switch(aff){
 			case BLACK: g.setColor(Color.BLACK); break;
 			case WHITE: g.setColor(Color.WHITE); break;
 			default: g.setColor(brown);
 		}
 			
 		g.fillOval(x*cellSpace + 50, y*cellSpace + 50, StoneSize, StoneSize);
 	}
 
    /*	
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
    }*/
    
    /*public void updateLoc(int x, int y, Affiliation side){
    	Location[x][y].setAffiliation(side);
    	if (side != Affiliation.NONE && side != Affiliation.DISPUTED)
    		_board[x][y].setOccupied(true);
    	else
    		_board[x][y].setOccupied(false);
    }*/
    
    /*public void paint(int x, int y, Color side, Graphics graphics){
    	// assumes the checks have been made
    	Graphics2D g = (Graphics2D)graphics;
    	if (side != Color.WHITE && side != Color.BLACK){
    		g.setColor(brown);
    		g.fillOval(x*cellSpace, y*cellSpace, StoneSize, StoneSize);
    	} else {
    		g.setColor(side);
    		g.fillOval(x*cellSpace, y*cellSpace, StoneSize, StoneSize);
    	}
    }*/
    
    
    
    public void actionPerformed(ActionEvent actionevent){
        run();
    }

    public static void main(String args[]){
        //(new TileDrawer()).run();
        JFrame frame = new JFrame("Heisen Go");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(new TileDrawer());
        frame.setSize(500,500);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        
        SwingUtilities.invokeLater(new Runnable(){
        	public void run(){
        		TileDrawer app = new TileDrawer();
        		app.setVisible(true);
        	}
        });
    }
    
    public void run(){
        paint(1,5);
    }
}