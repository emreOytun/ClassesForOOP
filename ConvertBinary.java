public class ConvertBinary {
    public static String convertBinary(int num) throws RuntimeException {
        if (num < 0) {
            throw new RuntimeException("Number cannot be negative");
        }
        
        if (num / 2 == 0) return Integer.toString(num%2);
        
        String restRes = convertBinary(num / 2);
        return restRes + Integer.toString(num % 2);
    }

    public static void main(String[] args) {
        System.out.println(convertBinary(21));
    }
}