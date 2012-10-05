class Monome{
	float coeff;
	int degre;
	Monome(float f,int Degree){
		this.coeff=f;
		this.degre=Degree;
	}
	
	void additionne(float coef){
		this.coeff+=coef;
	}
	
	void additionne(Monome m){
		if (this.degre==m.degre) this.coeff+=m.coeff;
	}
	
	void multiplie(float f,int deg){
		this.degre+=deg;
		this.coeff*=f;
	}
	void multiplie(Monome m){
		multiplie(m.coeff,m.degre);
	}
	
	void affiche(){
		System.out.format("%.1fx^%d ",this.coeff,this.degre);
	}
	void Affiche(){
		this.affiche();
		System.out.println("");
	}
}

class Polynome{
	Monome monomes[];
	int degre;
	
	Polynome(float coeff,int degre){
		this.degre=degre;
		this.monomes=new Monome[degre+1]; 				// Not exactly clever,
		this.monomes[degre]=new Monome(coeff,degre);	// but best one I could figure out
	}
	
	void additionne(float o_coeff,int o_degre){
		int i;
		
		if (o_degre>degre) {
			Monome new_monomes[]=new Monome[o_degre+1];
			for (i=0;i<degre;i++) new_monomes[i]=monomes[i];
			this.monomes=new_monomes;
		}
		
		if (this.monomes[o_degre]!=null) this.monomes[o_degre].additionne(o_coeff);
		else this.monomes[o_degre]=new Monome(o_coeff,o_degre);
	}
	void additionne(Monome m){
		this.additionne(m.coeff,m.degre);
	}
	
	void multiplie(float o_coeff,int o_degre){
		int i;
		if (o_degre>0){
			Monome new_monomes[]=new Monome[o_degre+this.degre+1];
			for (i=0;i<=this.degre;i++) if (monomes[i]!=null) new_monomes[i+o_degre]=monomes[i];
			this.monomes=new_monomes;
		}
		this.degre+=o_degre;
		for (i=0;i<=this.degre;i++) if (monomes[i]!=null) monomes[i].multiplie(o_coeff,o_degre);
	}
	
	void multiplie(Monome m){
		multiplie(m.coeff,m.degre);
	}
	
	void affiche(){
		int i;
		Monome mon;
		for (i=0;i<=this.degre;i++){
			mon=this.monomes[i];
			if (mon!=null) if (mon.coeff!=0) mon.affiche();
		}
		System.out.println("");
	}
}

class TestPolynome{
	public static void main(String[] args) {
		Polynome p1;
		Monome m1,m2,m3;
		m1=new Monome(3.6f,0);
		m2=new Monome(5.9f,1);
		m3=new Monome(2.0f,3);
		m1.Affiche();
		m2.Affiche();
		p1=new Polynome(6.1f,2);
		
		p1.additionne(m1);
		p1.additionne(m2);
		p1.multiplie(m3);
		p1.affiche();
		
		
	}	
}
