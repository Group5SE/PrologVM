import java.io.*;
public class palindrome {

	public static boolean checkPalindrome(String s)
	  {
	    // reverse the given String
	    String reverse = new StringBuffer(s).reverse().toString();
	 
	    // check whether the string is palindrome or not
	    if (s.equals(reverse))
	      return true;
	 
	    else
	      return false;
	  }
	  public static void main (String[] args)
	               throws java.lang.Exception
	  {
		  
		// specify the path of file 
	        String fileName = "D:/exam1/words.txt";

	        // This will reference one line at a time
	        String line = null;

	        try {
	            // FileReader reads text files in the default encoding.
	            FileReader fileReader = 
	                new FileReader(fileName);

	            // Always wrap FileReader in BufferedReader.
	            BufferedReader bufferedReader = 
	                new BufferedReader(fileReader);

	            while((line = bufferedReader.readLine()) != null) {
	            	
	            	if(palindrome.checkPalindrome(line))
	            		System.out.println(line);
	            }   
	            // Always close files.
	            bufferedReader.close();         
	        }
	        catch(FileNotFoundException ex) {
	            System.out.println(
	                "Unable to open file '" + 
	                fileName + "'");                
	        }
	        catch(IOException ex) {
	            System.out.println(
	                "Error reading file '" 
	                + fileName + "'");                  
	            // Or we could just do this: 
	            // ex.printStackTrace();
	        }
		 
	    
	  }
}
