public class Rational implements Comparable<Rational> {

    // Numerator sign can be negative or positive, but denominator sign is always positive.
    private int num;
    private int denom;  // Cannot be 0
    private static int aliveObjects = 0;


    public Rational(int num, int denom) throws RuntimeException {
        set(num, denom);
        ++Rational.aliveObjects;
    }

    public Rational(int num) {
        this.num = num;
        this.denom = 1;
        ++Rational.aliveObjects;
    }

    /* Overriding finalize method to see alive objects, though there is no guarentee for immediate garbage collection. */
    @Override
    protected void finalize() throws Throwable {
        try {
            System.out.println("Finalize for rational: " + num + "/" + denom);
            --Rational.aliveObjects;
        } catch (Throwable e) {
            throw e;
        } finally {
            super.finalize();
        }
    }

    public static int numberOfAliveObjects() {
        return aliveObjects;
    }

    public void set(int num, int denom) throws RuntimeException {    
        this.num = num;
        setDenom(denom);
    }

    public void setNum(int num) {
        this.num = num;
    }

    public void setDenom(int denom) throws RuntimeException {
        if (denom == 0) {
            throw new RuntimeException("Denominator cannot be 0");
        }
    
        this.denom = denom;
        setSigns();
    }

    // If denom is negative somehow, then change the sign of numerator; and make denominator positive.
    private void setSigns() {
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(num);
        stringBuilder.append("/");
        stringBuilder.append(denom);
        return stringBuilder.toString();
    }

    public double toDouble() {
        return (double) num / (double) denom;
    }
 
    public Rational multiply(Rational oth) {
        return new Rational(num*oth.num, denom*oth.denom);
    }
    
    @Override
    public int compareTo(Rational rhs) {
        if (this == rhs) return 0;
        if (toDouble() == rhs.toDouble()) return 0;
        if (toDouble() < rhs.toDouble()) return -1;
        return 1;
    }

    public static void main(String[] args) {
        Rational r1 = new Rational(2, 10);
        System.out.println(r1); // 2/10
        System.out.println(r1.toDouble()); // 0.2
    
        Rational r2 = new Rational(20, 30); 
        System.out.println(r1.multiply(r2)); // 40/300
    
        System.gc();
        System.out.println(Rational.numberOfAliveObjects());
        
    }

}