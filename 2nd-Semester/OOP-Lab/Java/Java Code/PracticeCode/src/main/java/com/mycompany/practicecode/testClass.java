
package com.mycompany.practicecode;

class parent{
        int a;
        public parent(int a){
            this.a= a;
        }
    }
    class subClass extends parent{
        int b;
        subClass(int a,int b){
            super(a);
            this.b= b;
        }
        public void printInfo(){
            System.out.println("SUM: "+(a+b));
        }
        
    }

public class testClass {
    public static void main(String[] args) {
        subClass s = new subClass(5,10);
        s.printInfo();
        
    }
    
}
    
