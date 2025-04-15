
package com.mycompany.practicecode;

public class Rectangle {
    int lenght=5,width=4;
    
    public void Calculate(){
        int Area= lenght*width;
        System.out.println("Area: "+Area);
    }
    public void printInfo(){
        System.out.println("Value of lenght: "+lenght);
        System.out.println("Value of width: "+width);
    }
        public static void main(String[] args){
            Rectangle rectangle= new Rectangle();
            
            rectangle.printInfo();
            rectangle.Calculate();
        }
}
