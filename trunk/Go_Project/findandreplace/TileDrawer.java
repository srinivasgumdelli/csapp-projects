import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class TileDrawer extends JFrame{

	private final int cellSpace = 20;
 	private final int StoneSize = 20;
 	private int dimension = 19;

 	private StoneList[] stones = new StoneList[100];
 	private int stoneCount = 0;

 	private int turns = 0;
 	private JTextField xtext, ytext;
 	private DrawCanvas canvas;

 	Color brown = new Color(156, 93, 82);

 	public TileDrawer(){
 		super("Heisen Go");

 		JPanel btnPanel = new JPanel();
 		btnPanel.setLayout(new FlowLayout());

 		JLabel xdesc = new JLabel("X:");
        btnPanel.add(xdesc);
        xtext = new JTextField();
        xtext.setPreferredSize(new Dimension(30,20));
        btnPanel.add(xtext);

        JLabel ydesc = new JLabel("Y:");
        btnPanel.add(ydesc);
        ytext = new JTextField();
        ytext.setPreferredSize(new Dimension(30,20));
        btnPanel.add(ytext);

        JButton endTurn = new JButton("End Turn");
        btnPanel.add(endTurn);
        endTurn.addActionListener(new ActionListener(){
        	public void actionPerformed(ActionEvent e){
        		if (!xtext.getText().isEmpty() && !ytext.getText().isEmpty()){
		 			int x = (int)Double.parseDouble(xtext.getText());
		 			int y = (int)Double.parseDouble(ytext.getText());
		 			Affiliation tmp = (turns%2==0)? Affiliation.BLACK : Affiliation.WHITE;
		 			if (x > 0 && y > 0 && x <= dimension && y <= dimension){
		 				addStone(x,y,tmp);
		 				turns++;
		 			}
		 			canvas.repaint();
		 			requestFocus();
 				}
        	}
        });

        canvas = new DrawCanvas();
        canvas.setPreferredSize(new Dimension(500,500));

        Container cp = getContentPane();
        cp.setLayout(new BorderLayout());
        cp.add(canvas, BorderLayout.CENTER);
        cp.add(btnPanel, BorderLayout.SOUTH);

        addKeyListener(new KeyAdapter(){
        	public void keyPressed(KeyEvent evt){

        	}
        });

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("Heisen Go");
        pack();
        setLocationRelativeTo(null);
        setVisible(true);
        requestFocus();
 	}

 	public void addStone(int x, int y, Affiliation aff){
 		if (stoneCount > stones.length - 2){
 			StoneList[] tmp = new StoneList[stones.length*2];
 			for (int i = 0; i < stones.length - 1; i++)
 				tmp[i] = stones[i];
 			stones = tmp;
 		}
 		stones[++stoneCount] = new StoneList(x,y,aff);
 	}

    public static void main(String args[]){
    	SwingUtilities.invokeLater(new Runnable(){
    		public void run(){
    			new TileDrawer();
    		}
    	});
    }

    class DrawCanvas extends JPanel{
    	public void paintComponent(Graphics g){
 			super.paintComponent(g);
 			setBackground(Color.WHITE);
 			Graphics2D g2d = (Graphics2D)g;

 			g2d.setColor(brown);
 		   	g2d.fillRect(50, 50, cellSpace*dimension, cellSpace*dimension);

    		// drawing the lines
	    	g2d.setColor(Color.DARK_GRAY);
	    	for (int i = 0; i < dimension+1; i++){
	    		g2d.drawLine(i*cellSpace+50, 50, 50+i*cellSpace, 50+dimension*cellSpace);
	    		g2d.drawLine(50, i*cellSpace+50, 50+dimension*cellSpace, 50+i*cellSpace);
	    	}

	    	for (int i = 0; i < stones.length - 1; i++){
	    		if (stones[i] != null){
	    			switch(stones[i].getAffiliation()){
	    				case BLACK: g2d.setColor(Color.BLACK); break;
	    				case WHITE: g2d.setColor(Color.WHITE); break;
	    				default: g2d.setColor(brown);
	    			}
	    			g2d.fillOval((stones[i].getX()-1)*cellSpace+50, (stones[i].getY()-1)*cellSpace+50, StoneSize, StoneSize);
	    		}
	    	}
    	}
    }
}