
package com.mycompany.practicecode;

public class exceptionHandlingExercise{
    public static void main(String[] args) {
        
        try{
            int[] array = new int[5];
       
        System.out.println("Accessing sixth element: "+array[10]);
        
        String text = "UITS_CSE";
        System.out.println("Character at 10th position: "+text.charAt(10));
        
        int result =100/0;
        System.out.println("Result: "+result);
        }
        catch(Exception e){
            System.out.println("Exception is: "+e);
        }
        
        finally{
            System.out.println("last line!");
        }
       
    }
}
