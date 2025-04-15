
package BeeCrowd;

import java.util.Scanner;

public class ExamProcedure {
    public static void main(String[] args){
        float n1,n2,n3,n4;
        Scanner input= new Scanner(System.in);
        n1= input.nextFloat();
        n2= input.nextFloat();
        n3= input.nextFloat();
        n4= input.nextFloat();
        float a= n1*2;
        float b= n2*3;
        float c= n3*4;
        float d= n4*1;
        float e;
        float re_avg;
        float avg= (a+b+c+d)/10;
        System.out.printf("Media: %.1f\n",avg);
        if (avg>=7.0){
            System.out.println("Aluno reprovado.");
        }
        
        else if(avg<7.0 && avg>=5.0){
            System.out.println("Aluno em exame.");
            System.out.println("Nota do exame:");
            e= input.nextFloat();
            re_avg= (e+avg)/2;
            if(re_avg>=5.0){
                System.out.println("Aluno aprovado.");
            }
            else{
                System.out.println("Aluno reprovado.");
            }
            System.out.printf("Media final: %.1f\n",re_avg);
           
        }
         else{
            System.out.println("Aluno reprovado.");
          }
    }
    
}
