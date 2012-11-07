import java.util.Random;

public class Heisen{
	double x1, x2, w, y1, y2;
	public Heisen(){
		// generates the matrix using Box-Muller Transformation
		
		do{
			x1 = 2 * Math.random() - 1;
			x2 = 2 * Math.random() - 1;
			w = Math.pow(x1, 2) + Math.pow(x2, 2);
		} while(w >= 1 );
		
		w = Math.sqrt( -2 * Math.log(w) / w);
		y1 = x1 * w;
		y2 = x2 * w;
	}
	
	public double getY1(){
		return y1;
	}
	
	public double getY2(){
		return y2;
	}
	
	public double getX1(){
		return x1;
	}
	
	public double getX2(){
		return x2;
	}
	
	public static void main(String[] args){
		Heisen g = new Heisen();
		System.out.println(g.getX1() + "\t" + g.getX2());
		System.out.println(g.getY1() + "\t" + g.getY2());
		System.out.println(g.getY1() + g.getY2());
		
		System.out.println("\n");
		
		Heisen g2 = new Heisen();
		System.out.println(g2.getX1() + "\t" + g2.getX2());
		System.out.println(g2.getY1() + "\t" + g2.getY2());
		System.out.println(g2.getY1() + g2.getY2());
		
		System.out.println("\n");
		
		Heisen g3 = new Heisen();
		System.out.println(g3.getX1() + "\t" + g3.getX2());
		System.out.println(g3.getY1() + "\t" + g3.getY2());
		System.out.println(g3.getY1() + g3.getY2());
	}
}