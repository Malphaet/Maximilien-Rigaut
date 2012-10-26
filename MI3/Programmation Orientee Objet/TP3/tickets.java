/*
 * tickets.java
 * This file is part of TP3
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * TP3 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * TP3 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TP3. If not, see <http://www.gnu.org/licenses/>.
 */

class Duration{
	public static int HOUR 	= 100;
	public static int DAY 	= 10000;
	public static int MONTH 	= 1000000;
}

class Date{
	private static int currentTime;
	private int value;
	
	public Date(int date){
		this.value=date;
	}
	
	public static Date getNow(){
		return new Date(Date.currentTime);
	}
	public static void setNow(Date date){
		Date.currentTime=date.getVal();
	}
	public int getVal(){
		return this.value;
	}
	
	public Date plus(int time){
		return new Date(this.getVal()+time); 
	}
	
	public boolean before(Date d){
		return d.getVal()<this.getVal();
	}
}

class SimpleTicket{
	protected float price;
	protected int validityTime;
	protected Date validityDate=null;
	public SimpleTicket(float price,int validity){
		this.price=price;
		this.validityTime=validity;
	}
	public float price(){
		return this.price;
	}
	public boolean check(){
		if (this.validityDate!=null) return this.validityDate.before(Date.getNow());
		this.validityDate=Date.getNow().plus(this.validityTime);
		return true;
	}
}


class MultipleTicket extends SimpleTicket{
	protected int usages;
	MultipleTicket(float price,int usages){
		super(price,Duration.HOUR);
		this.usages=usages;
	}
	public boolean check(){
		if (this.validityDate!=null) if (this.validityDate.before(Date.getNow())) return true;
		if (this.usages>0){
			this.usages--;
			this.validityDate=Date.getNow().plus(this.validityTime);
			return true;
		}
		return false;
	}
	public int left(){
		return usages;
	}
	
}

class ReloadableTicket extends MultipleTicket{
	ReloadableTicket(float price,int usages){
		super(price,usages);
	}
	public void reload(int number){
		this.usages+=number;
	}
}


class OneDayTicket extends SimpleTicket{
	public OneDayTicket(){
		super(5f,Duration.DAY);
	}
}

class SoloTicket extends SimpleTicket{
	public SoloTicket(){
		super(1.5f,Duration.HOUR);
	}
}

class PersonnalTicket extends ReloadableTicket{
	PersonnalTicket(){
		super(0,0);
	}
	
	public boolean subscribe(float price,int time){
		if (this.validityDate!=null) if (this.validityDate.before(Date.getNow())) return false;
		this.validityDate=Date.getNow().plus(time);
		this.price+=price;
		return true;
	}
	
	public boolean check(){
		if (super.check()) return true;
		if (this.validityDate!=null) return (this.validityDate.before(Date.getNow())); 
		return false; 
	}
}

class Ticket50 extends SimpleTicket{
	protected SimpleTicket ticket;
	Ticket50(SimpleTicket ticket){
		super(ticket.price/2,ticket.validityTime);
		ticket.price/=2;
		this.ticket=ticket;
	}
	
	public boolean check(){
		return ticket.check();
	}
	
	public SimpleTicket get(){
		return ticket;
	}
}
class Test{
	public static void main(String[] args) {
		System.out.println("Processing tests");
		Date.setNow(new Date(1210011200));
		
		SimpleTicket tickets[]=new SimpleTicket[10];
		int i,max=0;
		tickets[max++]=new SimpleTicket(3,Duration.HOUR);
		tickets[max++]=new SimpleTicket(3,2*Duration.HOUR);
		tickets[max++]=new SoloTicket();
		tickets[max++]=new OneDayTicket();
		PersonnalTicket p = new PersonnalTicket();
		p.subscribe(10f,4);
		p.reload(1);
		tickets[max++]=p;

		System.out.println("+--------\n| Checking ticket");
		for (i=0;i<max;i++)	System.out.printf("| Ticket %d: %b\n",i,tickets[i].check());
		
		
		Date.setNow(Date.getNow().plus(Duration.HOUR));
		System.out.println("+---\n| An hour later");
		for (i=0;i<max;i++)	System.out.printf("| Ticket %d: %b\n",i,tickets[i].check());
		
		Date.setNow(Date.getNow().plus(Duration.DAY));
		System.out.println("+---\n| A month later");
		for (i=0;i<max;i++)	System.out.printf("| Ticket %d: %b\n",i,tickets[i].check());

	}
}
