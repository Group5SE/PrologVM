package iProlog;
import java.util.*;
public class CustomGenerator 
{ 
    static int a[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    static int random(int numb)
    { // Assuming digit is 6.
        int sqn = numb * numb, next_num=0;
        int trim =  4;
        sqn = sqn / a[trim];
        for(int i=0; i<6; i++)
        {
            next_num += (sqn%(a[trim]))*(a[i]);
            sqn = sqn/10;
        }
        return next_num;
    }
 
public static void main(String args[])
    {
        // Example USE:
        int number= 23456;
        System.out.print("The random numbers are:\n "); 
        for(int i=0; i<9; i++)
        {
            number = random(number);
            System.out.print(number+", ");
        } 
    }
}