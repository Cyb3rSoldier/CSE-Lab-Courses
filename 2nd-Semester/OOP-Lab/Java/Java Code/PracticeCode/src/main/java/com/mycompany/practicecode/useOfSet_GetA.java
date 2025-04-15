
package com.mycompany.practicecode;

public class useOfSet_GetA {
    private int a;
    public useOfSet_GetA(){
        this.a=10;
    }
    public void setA(int a){
        this.a=a;
    }
    public int getA(){
        return a;
    }
    public static void main(String[ ] args){
        useOfSet_GetA obj = new useOfSet_GetA();
        obj.setA(10);
        System.out.println("A= "+obj.getA());
    }
}
