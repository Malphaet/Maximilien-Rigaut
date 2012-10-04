class Emetteur{
	int coordonees[], portee, frequence;
	
	Emetteur(int c[], int p, int f){
		this.coordonees=c;
		this.portee=p;
		this.frequence=f;
		System.out.println("Object Emetteur created:");
		this.afficher();
	}
	
	double abscisse() { return this.coordonees[0];}
	double ordonee() { return this.coordonees[1];}
	double portee(){ return this.portee;} 
	double frequence(){ return this.frequence;}
	
	void augmenteFrequence(){
		this.frequence++;
	}
	
	void afficher(){
		System.out.format("x=%d,y=%d. Range %d, Frequency %d\n",this.coordonees[0],this.coordonees[1],portee,frequence);
	}
	
	public static void main(String[] args) {
		int pos[]={2,0};
		Emetteur em=new Emetteur(pos,12,2);
	}
}

class Recepteur{
	int coordonees[];
	
	Recepteur(int c[]){
		this.coordonees=c;
	}
	
	double abscisse() { return this.coordonees[0];}
	double ordonee() { return this.coordonees[1];}
	
	double distance(Emetteur e){
		return Math.sqrt(Math.pow(this.ordonee()-e.ordonee(),2)+Math.pow(this.abscisse()-this.ordonee(),2));
	}
	
	boolean recoit(Emetteur e){
		return this.distance(e)<e.portee;
	}
	
	void controleEmetteurs(Emetteur e1,Emetteur e2){
		if (recoit(e1)&&recoit(e2)){
			e1.augmenteFrequence();
		}
	}
	
	public static void main(String[] args) {
		int p1[]={0,0},p2[]={1,1},p3[]={3,3};
		Emetteur e1=new Emetteur(p1,5,100),e2=new Emetteur(p2,5,100);
		Recepteur auditeur=new Recepteur(p3);
		auditeur.controleEmetteurs(e1,e2);
		System.out.println("Emetteur e1"); e1.afficher();
		System.out.println("Emetteur e2"); e2.afficher();
		
	}
}
