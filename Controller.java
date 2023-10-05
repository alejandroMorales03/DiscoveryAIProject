
import java.util.Random;

public class Controller {
    public static void main(String[] args) {

        int[] distance1;
        distance1 = new int[6];

        for(int i = 0; i < 6; i++) {
            Random rndGen = new Random();
            distance1[i] = rndGen.nextInt(0,16);

        }//end distance1 array initializer

        System.out.println("Testing arrays:");
        System.out.println();
        System.out.println("Testing distance1 array: " + distance1[4] + " and " + distance1[2]);

        //-----------------------------------------------------------------------------------------------------------

        int[] distance2;
        distance2 = new int[6];

        for(int i = 0; i < 6; i++) {
            Random rndGen = new Random();
            distance2[i] = rndGen.nextInt(0,11);

        }//end distance2 array initializer

        System.out.println("Testing distance2 array: " + distance2[4] + " and " + distance2[2]);

        //----------------------------------------------------------------------------------------------------------

        double[] occupancy;
        occupancy = new double[6];

        for(int i = 0; i < 6; i++) {
            Random rndGen = new Random();
            occupancy[i] = rndGen.nextDouble(0.0,1.0);

            //Extremely inefficient decimal truncation:
            occupancy[i] *= 100.0; //multiplies the value by 100 to isolate the first two numbers to the 10s place

            occupancy[i] = (int) occupancy[i]; //casts the value to int to truncate the decimal

            occupancy[i] /= 100.0; //divides by 100 put the numbers back in the decimals place

        }//end occupancy array initializer

        System.out.println("Testing occupancy array: " + occupancy[4] + " and " + occupancy[2]);
        System.out.println("----------------------------------------------------------------");

        //-----------------------------------------------------------------------------------------------------------

        double[] result;
        result = new double[6];

        final double mean = 0.5;
        final double standardDeviation = 0.1; //for a reminder

        System.out.println("Occupancy calculations, adjusted:"); //they are printed when the calc method is called below

        for(int i = 0; i < 6; i++) {
            result[i] = calculateDesirability(distance1[i], distance2[i], occupancy[i]);

        }//end result array initializer

        //-----------------------------------------------------------------------------------------------------------
        //Printing---------------------------------------------------------------------------------------------------

        System.out.println("----------------------------------------------------------------");
        System.out.println();
        System.out.println("Results:");
        System.out.println();

        System.out.println("Distance 1 array:");

        for(int i = 0; i < 6; i++) {
            System.out.printf("Index %1d: \t %-3d\n", i, distance1[i]);

        }//end distance1 printing

        System.out.println();
        System.out.println("---------------------------------------------------------------");
        System.out.println("Distance 2 array:");

        for(int i = 0; i < 6; i++) {
            System.out.printf("Index %1d: \t %-3d\n", i, distance2[i]);

        }//end distance2 printing

        System.out.println();
        System.out.println("--------------------------------------------------------------");
        System.out.println("Occupancy array:");

        for(int i = 0; i < 6; i++) {
            System.out.printf("Index %1d: \t %.7f\n", i, occupancy[i]);
        }
        //Note that the adjustments are only done to a temporary variable and not saved to the array

        System.out.println();
        System.out.println("---------------------------------------------------------------");
        System.out.println("Results array:");

        for(int i = 0; i < 6; i++) {
            System.out.printf("Index %1d: \t %-10.3f\n", i, result[i]);

        }//end result printing

    }//end main method

    //==============================================================================================================
    public static double calculateDesirability(int distance1, int distance2, double occupancy) {

        double result;

        //Less than 1 standard deviation-----------------------------------------------------------------------------
        if (occupancy == 0.5 || 0.4 <= occupancy && occupancy < 0.5 || 0.5 < occupancy && occupancy <= 0.6) {
            result = equation(distance1, distance2, occupancy);
            return result;

        //Diminish---------------------------------------------------------------------------------------------------

        } else if(0.3 <= occupancy && occupancy < 0.4) {
            occupancy /= 10.0;
            result = equation(distance1, distance2, occupancy);
            return result;

        } else if(0.2 <= occupancy && occupancy < 0.3) {
            occupancy /= 100.0;
            result = equation(distance1, distance2, occupancy);
            return result;

        } else if(0.1 <= occupancy && occupancy < 0.2) {
            occupancy /= 1000.0;
            result = equation(distance1, distance2, occupancy);
            return result;

        } else if(0.0 <= occupancy && occupancy < 0.1) {
            occupancy /= 10000.0;
            result = equation(distance1, distance2, occupancy);
            return result;



        //Amplification-----------------------------------------------------------------------------------------------

        } else if(0.6 < occupancy && occupancy <= 0.7) {
            occupancy *= 10.0;
            result = equation(distance1, distance2, occupancy);
            return result;

        } else if(0.7 < occupancy && occupancy <= 0.8) {
            occupancy *= 100.0;
            result = equation(distance1, distance2, occupancy);
            return result;

        } else if(0.8 < occupancy && occupancy <= 0.9) {
            occupancy *= 1000.0;
            result = equation(distance1, distance2, occupancy);
            return result;

        } else if(0.9 < occupancy && occupancy <= 1.0) {
            occupancy *= 10000.0;
            result = equation(distance1, distance2, occupancy);
            return result;

        } else {
            System.out.println("Outside of range.");
            return 0.0;

        }//end diminishing returns

    }//end desirability method

    //Utility ----------------------------------------------------------------------------------------------------

    public static double equation(int distance1, int distance2, double occupancy) {
        occupancy += 1;
        System.out.println(occupancy);
        return ((distance1 + distance2) * occupancy);

    }// end base equation

}//end class Controller
