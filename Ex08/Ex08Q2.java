// Author:      Hiroshi Tasaki
// Student ID:  s1270244
// Code Description
// This program is for solving the combination problem to pay the N cents with-
// the four sort of cents, '25 cent', '10 cent', '5 cent', and '1 cent'.
// The algorithm used here is based on the idea of a greedy algorithm. 

import java.util.Arrays;
import java.util.Scanner;

public class Ex08Q2 {
    private static int cents[] = {25, 10, 5, 1};
    private static int count[] = {0, 0, 0, 0};
    private static int myWallet[] = {0, 0, 0, 0};
    private static final int NUM = 4;            // The NUM types of cents can be taken into acount.
    private static int sum = 0;
    private static int payment;

    private static boolean pickUpCent() {
        int i;

        for( i = 0; i < NUM; i++ ) {
            if( myWallet[i] != 0 && sum + cents[i] <= payment ) {
                count[i]++;
                sum += cents[i];
                myWallet[i]--;
                break;
            } 
        }

        // When you cannot pay for the payment with your wallet
        if( i == NUM )
            return false;

        return true;
    }

    private static void print() {
        int total = 0;

        for( int i = 0; i < NUM; i++ ) {
            System.out.format("[ %d cent ] %d used. \n", cents[i], count[i]);
            total += count[i];
        }
        
        System.out.format("Totally, you used %d coins for %d cents.\n", total, payment);
    }


    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        System.out.println("Input numbers of each cent[coin].");
        for( int i = 0; i < NUM; i++ )
            myWallet[i] = scan.nextInt();

        System.out.println("Input how many cents should you pay?");
        payment = scan.nextInt();

        while( true ) {

            if( pickUpCent() == false ) {
                System.out.println("Error: You cannot pay for the value.");
                break;
            }
            
            if( sum == payment ) {
                print();
                break;
            }
        }
    }    
}