/*
OUTPUT:
a
eye
I
level

*/

/*

GIT LINK: https://github.com/Group5SE/PrologVM/tree/exam 
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

E:\Software Engineering\Exam_Karthik>git commit -a -m "Added git commands"
[exam 28befa0] Added git commands
 1 file changed, 25 insertions(+)

E:\Software Engineering\Exam_Karthik>git push origin exam -f
Counting objects: 3, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 738 bytes | 0 bytes/s, done.
Total 3 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/Group5SE/PrologVM.git
   f914b35..28befa0  exam -> exam

E:\Software Engineering\Exam_Karthik>git commit -a -m "Added output"
[exam 09d1cb4] Added output
 1 file changed, 9 insertions(+)

E:\Software Engineering\Exam_Karthik>git push origin exam -f
Counting objects: 3, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 365 bytes | 0 bytes/s, done.
Total 3 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/Group5SE/PrologVM.git
   28befa0..09d1cb4  exam -> exam
 */

import java.util.*;
import java.io.*;
class Palindrome
{
    public static boolean isPalindrome(String str) {
        return str.equals(new StringBuilder(str).reverse().toString()); // Check if reverse is the original string.
    }
    public static void main(String[] args) throws FileNotFoundException, IOException{
        String everything;
        ArrayList<String> words = new ArrayList<String>();
        BufferedReader br = new BufferedReader(new FileReader("words.txt")); // Read the list of words from file.
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
            ; // Assuming file is found. Ha- ha !
        }
        finally {
            br.close();
        }  
        Iterator itr= words.iterator();  
        while(itr.hasNext()){  
         System.out.println(itr.next());   // Print only  words which are palindromes.
        }  
    }
}
