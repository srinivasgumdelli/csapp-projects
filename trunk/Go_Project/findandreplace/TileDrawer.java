import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class TileDrawer extends JFrame{

    private final int cellSpace = 20;
    private final int StoneSize = 20;
    private int dimension = 19;

    private StoneList[] stones = new StoneList[361];
    private int stoneCount = 0;

    private int turns = 0;
    private final JTextField xtext, ytext;
    private DrawCanvas canvas;

    private GoGame theGame;

    Color brown = new Color(156, 93, 82);

    public TileDrawer(){
	super("Heisen Go");

	theGame = new GoGame(this);

	final JPanel btnPanel = new JPanel();
	btnPanel.setLayout(new FlowLayout());


	    
	final JLabel xdesc = new JLabel("X:");
	xtext = new JTextField();
	xtext.setPreferredSize(new Dimension(30,20));
	

	final JLabel ydesc = new JLabel("Y:");
	ytext = new JTextField();
	ytext.setPreferredSize(new Dimension(30,20));
	
	final JButton endTurn = new JButton("Make Move");	
	endTurn.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
		    if (!xtext.getText().isEmpty() && !ytext.getText().isEmpty()){
			int x = (int)Double.parseDouble(xtext.getText());
			int y = (int)Double.parseDouble(ytext.getText());
			Affiliation tmp = (turns%2==0)? Affiliation.BLACK : Affiliation.WHITE;
			/*
			  if (x > 0 && y > 0 && x <= dimension && y <= dimension){
			  addStone(x,y,tmp);
			  turns++;
		
			
			  }
			*/
			
			stones = new StoneList[361];
			stoneCount = 0;

			theGame.makeMove(x, y);
			canvas.repaint();
			requestFocus();
		    }
		}
	    });

	final JButton pass = new JButton("Pass Turn");
	pass.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
		    if(!theGame.makeMove(-1, -1))
			{
			    btnPanel.remove(xdesc);
			    btnPanel.remove(xtext);
			    btnPanel.remove(ydesc);
			    btnPanel.remove(ytext);
			    btnPanel.remove(endTurn);
			    btnPanel.remove(pass);
			    String end = theGame.endGame();
			    theGame.updateGui();
			    JLabel endMessage = new JLabel(end);
			    btnPanel.add(endMessage);

		    btnPanel.repaint();
		    btnPanel.revalidate();

			}

		}
	    });


	final JLabel askHeisen = new JLabel("Turn on HeisenGo uncertainty?");
	final JButton noHeisen = new JButton("No");
	final JButton yesHeisen = new JButton("Yes");
	btnPanel.add(askHeisen);
	btnPanel.add(yesHeisen);
	yesHeisen.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
		    btnPanel.remove(yesHeisen);
		    btnPanel.remove(noHeisen);
		    btnPanel.remove(askHeisen);
		    theGame.setHeisen(true);

		    btnPanel.add(xdesc);
		    btnPanel.add(xtext);
		    btnPanel.add(ydesc);
		    btnPanel.add(ytext);
		    btnPanel.add(endTurn);  
		    btnPanel.add(pass);

		    btnPanel.repaint();
		    btnPanel.revalidate();
		}
	    });
	btnPanel.add(noHeisen);
	noHeisen.addActionListener(new ActionListener(){
		public void actionPerformed(ActionEvent e){
		    btnPanel.remove(noHeisen);
		    btnPanel.remove(yesHeisen);
		    btnPanel.remove(askHeisen);
		    theGame.setHeisen(false);

		    btnPanel.add(xdesc);
		    btnPanel.add(xtext);
		    btnPanel.add(ydesc);
		    btnPanel.add(ytext);
		    btnPanel.add(endTurn);  
		    btnPanel.add(pass);

		    btnPanel.repaint();
		    btnPanel.revalidate();
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
	    g2d.fillRect(50, 50, cellSpace*(dimension-1)+StoneSize, cellSpace*(dimension-1)+StoneSize);

	    // drawing the lines
	    g2d.setColor(Color.DARK_GRAY);
	    for (int i = 0; i < dimension; i++){
		g2d.drawLine(i*cellSpace+50 +(cellSpace/2), 50 +(cellSpace/2), 50+i*cellSpace +(cellSpace/2), 50+(dimension-1)*cellSpace +(cellSpace/2));
		g2d.drawLine(50 +(cellSpace/2), i*cellSpace+50 +(cellSpace/2), 50+(dimension-1)*cellSpace +(cellSpace/2), 50+i*cellSpace +(cellSpace/2));
	    }

	    for (int i = 0; i < stones.length; i++){
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