import java.util.*;
import java.io.*;
class Palindrome
{
    public static boolean isPalindrome(String str) {
        return str.equals(new StringBuilder(str).reverse().toString());
    }
    public static void main(String[] args) throws FileNotFoundException, IOException{
        String everything;
        ArrayList<String> words = new ArrayList<String>();
        BufferedReader br = new BufferedReader(new FileReader("words.txt"));
        try { 
            String line = br.readLine();
            while (line != null) { 
                if(isPalindrome(line))
                    words.add(line);
                line = br.readLine();
            } 
        } 
        catch (FileNotFoundException ex)  
        {
            // insert code to run when exception occurs
        }
        finally {
            br.close();
        }  
        Iterator itr= words.iterator();  
        while(itr.hasNext()){  
         System.out.println(itr.next());  
        }  
    }
}

