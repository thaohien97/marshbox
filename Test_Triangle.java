import java.io.*;
import java.util.Scanner;
import java.math.*;

class Triangle {
    //Stores the lengths .
    private double side1,side2,side3;
    public boolean validTri; 
    
    //Constructor to intialize the sides of the triangle .
    public Triangle ( double s1 , double s2 , double s3){
        this.side1 = s1;
        this.side2 = s2;
        this.side3 = s3;
        this.validTri=valid(s1,s2,s3);
    }

    //Test for a right-angled triangle.
    public boolean right_angled (){
            if (
                ( (side1*side1) == ((side2*side2) + (side3*side3)) ) ||
                ( (side2*side2) == ((side1*side1) + (side3*side3)) ) ||
                ( (side3*side3) == ((side1*side1) + (side2*side2)) )
            )
               return true;
            else
               return false;
    }
    

    //Test for scalene triangle.
    public boolean scalene(){
        if ((side1 != side2) && (side1 != side3) && (side2 != side3))
        return true;
     else
        return false;
    }

    //Test for an isosceles triangle.
    public boolean isosceles(){
        if (
            ((side1 == side2) && (side1 != side3)) ||
            ((side1 == side3) && (side1 != side2)) ||
            ((side2 == side3) && (side2 != side1))
        )
       return true;
    else
       return false;
    }

    //Test for an equilateral triangle .
    public boolean equilateral(){
        if ((side1 == side2) && (side1 == side3))
            return true;
        else
            return false;
    }

    public boolean valid(double side1, double side2, double side3){
        if(side1<=0||side2<=0||side3<=0){
            return false;
        }
        else if(side1+side2<=side3||side2+side3<=side1||side1+side3<=side2){
            return false;
        }
        else{
            return true;
        }
    }

    public void output(){
        if(validTri==false){
            System.out.println("Invalid");
        }
        else{
            System.out.println ("\nIs triangle right-angle? "+ right_angled());
            System.out.println ("Is triangle scalene?     "+ scalene());
            System.out.println ("Is triangle isosceles?   "+
                                                       isosceles());
            System.out.println ("Is triangle equilateral? "+
                                                     equilateral());
        }
    }
    
    double area; double s;

    public void getArea(){
        if (validTri==true){
            s = 0.5 * (side1+side2+side3);
            area = Math.sqrt(s*(s-side1)*(s-side2)*(s-side3));
            System.out.println("The area of the triangle is " + area);
        }
    }
}


class Point{
    private double x;
    private double y;

    Point(double x, double y){
        this.x = x;
        this.y = y;
    }

    public double returnX(){
        return x;
    }

    public double returnY(){
        return y;
    }
  
}

class Test_Triangle {
    public static void main(String[] args) throws IOException {
        
        //Declare stdin to read data from input.
        DataInputStream stdin = new DataInputStream (System.in);
        Scanner scan = new Scanner(System.in);
        // loop exits when the user response is "n"
      String user_response = "y";
      while (!user_response.equals("n")) {

         // Ask user for 3 dimensions of triangle.
         try{
            System.out.println ("\nEnter side1 length: ");
            double side1 = scan.nextDouble();
   
            System.out.println ("Enter side2 length: ");
            double side2 = scan.nextDouble();
   
            System.out.println ("Enter side3 length: ");
            double side3 = scan.nextDouble();
   
            // Now use these values to create a Triangle object.
            Triangle tri = new Triangle (side1,side2,side3);
   
            tri.output();
            tri.getArea();
         }
         catch(Exception e){
             System.out.println("Invalid!");
         }
         
        try{
         System.out.println("Enter (x,y) of Point A:");
         double Ax = scan.nextDouble();
         double Ay = scan.nextDouble();
         Point pA = new Point(Ax,Ay);
    
         System.out.println("Enter (x,y) of Point B:");
         double Bx = scan.nextDouble();
         double By = scan.nextDouble();
         Point pB = new Point(Bx,By);

         System.out.println("Enter (x,y) of Point C:");
         double Cx = scan.nextDouble();
         double Cy = scan.nextDouble();
         Point pC = new Point(Cx,Cy);

         double side1 = Math.sqrt( Math.pow(pA.returnX()-pB.returnY(),2) + Math.pow(pA.returnY()-pB.returnY(),2));
         double side2 = Math.sqrt( Math.pow(pB.returnX()-pC.returnY(),2) + Math.pow(pB.returnY()-pC.returnY(),2));
         double side3 = Math.sqrt( Math.pow(pA.returnX()-pC.returnY(),2) + Math.pow(pA.returnY()-pC.returnY(),2));
        
        Triangle newtri = new Triangle (side1,side2,side3);
        newtri.output();
        }
        catch(Exception e){
            System.out.println("Invalid!");
        }
 

         // Determine what kind of triangle it is.
         
         // Ask user if they want to continue.
         System.out.println ("\nDo you want to examine more triangles?");
         System.out.println ("(type 'y' for yes or 'n' for no)");
         user_response = stdin.readLine();
      }
    }
}