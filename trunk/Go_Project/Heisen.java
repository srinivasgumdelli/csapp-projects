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
	
	public getY1(){
		return y1;
	}
	
	public getY2(){
		return y2;
	}
}