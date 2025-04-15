
package hackerRank;

import java.util.Scanner;

public class LexicographicalComparison {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        
        String str1 = scanner.nextLine();
        String str2 = scanner.nextLine();

        
        for (int i = 0; i < str1.length(); i++) {
            char char1 = Character.toLowerCase(str1.charAt(i));
            char char2 = Character.toLowerCase(str2.charAt(i));
        

            if (char1 < char2) {
                System.out.println(-1); 
                return;
            } else if (char1 > char2) {
                System.out.println(1); 
                return;
            }
        }

        
        System.out.println(0);

        scanner.close();
    }
}
