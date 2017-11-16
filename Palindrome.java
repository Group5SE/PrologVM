/*


E:\Software Engineering\Exam_Karthik>git remote add origin https://github.com/Group5SE/PrologVM.git
E:\Software Engineering\Exam_Karthik>git add words.txt
E:\Software Engineering\Exam_Karthik>git add Palindrome.java

E:\Software Engineering\Exam_Karthik>git commit -a -m "Uploaded probelm 2"
[exam (root-commit) f914b35] Uploaded probelm 2
 2 files changed, 1033 insertions(+)
 create mode 100644 Palindrome.java
 create mode 100644 words.txt

E:\Software Engineering\Exam_Karthik>git push origin exam -f
Counting objects: 4, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 3.63 KiB | 0 bytes/s, done.
Total 4 (delta 0), reused 0 (delta 0)
To https://github.com/Group5SE/PrologVM.git
 * [new branch]      exam -> exam


 */

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

