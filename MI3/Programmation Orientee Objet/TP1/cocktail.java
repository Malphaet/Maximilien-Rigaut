class Verre {
	int contenance,quantitee;
	Verre(int c){
		this.contenance=c;
		this.quantitee=0;
	}
	void emplir(int q){
		this.quantitee+=q;
	}
	void boire(int q){
		this.quantitee-=q;
	}
}

class Bouteille{
	int quantitee;
	boolean ouverte;
	Bouteille(int q){
		this.quantitee=q;
	}
	void ouvrir(){
		this.ouverte=true;
	}
	void fermer() {
		this.ouverte=false;
	}
	void verser_dans(Verre v,int q){
		if (this.ouverte) v.emplir(q);
		else System.out.println("Votre bouteille est fermée");
	}
}

class Vodka_orange{
	public static void main(String[] args) {
		Bouteille Vodka=new Bouteille(100);
		Bouteille Orange=new Bouteille(100);
		Verre v = new Verre(20);
		
		Orange.ouvrir(); 			System.out.println("Jus d'Orange ouvert");
		Vodka.ouvrir(); 			System.out.println("Vodka Ouverte");

		Vodka.verser_dans(v,8);		System.out.println("Vodka versée");
		Orange.verser_dans(v,12); 	System.out.println("Jus d'orange versée");
		v.boire(20);				System.out.println("Verre bu avec modération");
	}
}
