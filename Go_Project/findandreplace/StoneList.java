public class StoneList {
   	private int xloc, yloc;
   	private Affiliation aff = Affiliation.NONE;
    	
   	public StoneList(int x, int y, Affiliation _aff){
   		xloc = x;
   		yloc = y;
   		aff = _aff;
   	}
   	
   	public void setAffiliation(Affiliation _aff){
   		aff = _aff;
   	}
   	
   	public Affiliation getAffiliation(){
   		return aff;
   	}
   	
   	public int getX(){
   		return xloc;
   	}
   	
   	public int getY(){
   		return yloc;
   	}
}