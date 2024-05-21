package hw3;

import java.io.PrintWriter; // Import the PrintWriter to write data to file
import java.io.IOException; // Import the IOException class to handle errors
import java.util.Scanner; // Import Scanner to take user input

/**
 * Demo class with main method for testing set and vector
 */
public class HwDemo {
	/**
	 * main function, makes use of JavaSet and JavaVector to test out capabilities
	 * @param args No input required
	 */
	public static void main(String[] args) {

		PrintWriter writer = null; // assgined to null for uninitialized error  
		
		//Testing JavaVector
		int size;
		Scanner input = new Scanner(System.in);
		System.out.print("Please enter size for vector: ");
		size = input.nextInt();
		input.nextLine(); // done to do input flush

		System.out.print("Please enter the elements: ");
		JavaVector<String> vect1 = new JavaVector<String>(size);
		String userElement;
		
		for (int i = 0; i<size; i++) {
			
			userElement = input.next(); // taking one string each iteration
			vect1.add(userElement);
			
		}

		System.out.println("\nJavaVector contents: " + vect1);
		System.out.println();
		try {
			
			writer = new PrintWriter("vector.txt");
			writer.println(vect1);

		} catch (IOException e) {
			
			System.out.println("An error occurred.");
			e.printStackTrace();
			
		} finally {
			
			writer.close();
			
		}
		
		//vector equals
		JavaVector<Double> vecteq1 = new JavaVector<Double>();
		JavaVector<Double> vecteq2 = new JavaVector<Double>();
		
		vecteq1.add(4.);
		vecteq1.add(3.);
		vecteq1.add(3.3);
		
		
		vecteq2.add(4.);
		vecteq2.add(3.);
		vecteq2.add(3.3);
		
		equalTest(vecteq1, vecteq2);
		vecteq1.add(3.);
		
		//iterator test
		System.out.print("vector after new element is added: ");
		var it = vecteq1.getIterator();
		while(it.hasNext()) {
			System.out.print(it.next() + "  ");
		}
		System.out.println();
		equalTest(vecteq1, vecteq2);
		
		
		//set

		System.out.print("\nPlease enter size for set: ");
		size = input.nextInt();
		input.nextLine();

		JavaSet<String> set1 = new JavaSet<String>(size);
		System.out.println("Enter elements line by line. ");
		for (int i = 0; i < size; i++) {
			System.out.print("Enter element: ");
			userElement = input.next();
			try {
				set1.add(userElement);
			} catch (IllegalArgumentException e) {
				System.out.println(e.getMessage());
				i--;
			}
		}

		System.out.println("\nJavaSet contents: " + set1);
		
		try {
			
			writer = new PrintWriter("set.txt");
			writer.println(set1);

		} catch (IOException e) {
			
			System.out.println("An error occurred.");
			e.printStackTrace();
			
		} finally {
			
			writer.close();
			
		}

		// Testing JavaSet equals
		
		JavaSet<Integer> seteq1 = new JavaSet<Integer>();
		JavaSet<Integer> seteq2 = new JavaSet<Integer>();
		
		seteq1.add(1);
		seteq1.add(2);
		seteq2.add(2);
		seteq2.add(1);
		
		System.out.print("\n\nset1: "); System.out.println(seteq1);
		System.out.print("set2: "); System.out.println(seteq2);
		
		equalTest(seteq1, seteq2);
		
		
		System.out.println("Adding another element to set1.");
		seteq1.add(3);
		System.out.print("set1: "); System.out.println(seteq1);
		System.out.println();
		equalTest(seteq1, seteq2);
		
		input.close();
	}
	
	public static void equalTest(JavaContainer<?> a, JavaContainer<?> b) {
		if(a.getClass() != b.getClass()) throw new IllegalArgumentException("Incomparable types");
		
		
		System.out.print(a + " and " + b);
		if(a.equals(b)) {	
			System.out.println(" is equal!");
		}
		else {
			System.out.println(" is not equal!");
		}
		
	}
}

