class Person{
	String first_name,last_name;
	boolean alive,sex;
	Person mate;
	Person childs[]=new Person[10];
	int age;
	
	Person(String Fname,String Lname,char Sex){
		this.first_name=Fname;
		this.last_name=Lname;

		if (Sex=='m'){this.sex=true;}
		else {
			if(Sex=='f'){this.sex=false;}
			else System.exit(0);
		}
		this.mate=null;
		this.alive=true;
		this.age=0;
	}
	
	void die(){
		this.alive=false;
		this.divorce();
	}
	
	boolean grows(){
		if (!this.alive) return false;
		this.age++;
		if (this.age>120) {
			this.die();
			return false;
		}
		return true;
	}
	
	boolean marry(Person p){
		if (this.age>=18 & p.age>=18 & this.alive & p.alive & this.mate==null & p.mate==null /* & p.sex != this.sex */){ // Gay couples !
			p.mate=this;
			this.mate=p;
			if (this.sex) this.mate.last_name=this.last_name;
			else this.last_name=this.mate.last_name;
			
			return true;
		} else {
			return false;
		}
	}
	
	boolean divorce(){
		if (this.mate==null){
			return false;
		}
		this.mate.mate=null;
		this.mate=null;
		return true;
	}
	
	Person father(String name, char gender){
		Person chld;
		int i=0;
		if (this.mate==null) return null;
		chld=new Person(name,this.last_name,gender);
		while (this.childs[i]!=null) {
			i++;
			if (i>=10) {
				System.out.format("%s got too many childs !",this.first_name);
				System.exit(0);
			}
		}
		this.childs[i]=chld;
		i=0;
		while (this.mate.childs[i]!=null){
			i++;
			if (i>=10){
				System.out.format("%s got too many childs",this.first_name);
				System.exit(0);				
			}
		}
		this.mate.childs[i]=chld;
		return chld;
	}
	
	void show(){
		System.out.format("I'm %s, %s",this.last_name,this.first_name);
		if (this.mate!=null) System.out.format(". Married to %s",this.mate.first_name);
		System.out.format(". I'm %d years old and %s.",this.age,this.sex?"male":"female");
		if (!this.alive) System.out.format(" I'm also dead by the way.");
		System.out.println("");
	}
	
	void show_all_childs(){
		int i;
		this.show();
		if (this.childs[0]!=null) System.out.println("My childs are:");
		for (i=0;i<10;i++){
			if (this.childs[i]!=null) this.childs[i].show_all_childs();
			else break;
		}
	}
	
	void show_childs(){
		int i;
		for (i=0;i<10;i++){
			if (this.childs[i]!=null) this.childs[i].show();
			else break;
		}
	}
	
	public static void main(String[] args) {
		int i;
		Person pierre,marie,jacques;
		pierre=new Person("Pierre","Martin",'m');
		marie=new Person("Marie","Duval",'f');
		jacques=new Person("Jacques","Dupon",'m');
		
		for (i=0;i<20;i++) {
			pierre.grows();
			marie.grows();
			jacques.grows();
		}
		
		pierre.marry(marie);
		pierre.father("Sophie",'f');
		pierre.father("Jean",'m');
		
		pierre.die();
		
		marie.marry(jacques);
		marie.father("Alain",'m');
		
//		jacques.show();
//		marie.show();
		
		pierre.show();
		System.out.println("My childs are:");
		pierre.show_childs();
		
		System.out.println("------------");
		jacques.show_all_childs();
	}
}
