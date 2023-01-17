import java.util.Arrays;

public class DigitalTime implements Comparable<DigitalTime> {
    
    private int hour;
    private int minute;

    public DigitalTime() {
        hour = 0;
        minute = 0;
    }

    public DigitalTime(int hour) {
        setHour(hour);
    }

    public DigitalTime(int hour, int minute) {
        setTime(hour, minute);
    }

    public void setHour(int hour) {
        if (hour < 0 || hour > 24) {
            throw new IllegalArgumentException("Hour cannot be negative or greater than 24");
        }

        if (hour == 24) hour = 0;
        this.hour = hour;
    }

    public void setTime(int hour, int minute) {
        if (hour < 0 || hour > 24 || minute < 0 || minute > 59) {
            throw new IllegalArgumentException("Invalid arguments");
        }
        
        if (hour == 24) hour = 0;
        this.hour = hour;
        this.minute = minute; 
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(hour);
        stringBuilder.append(":");
        stringBuilder.append(minute);
        return stringBuilder.toString();
    }

    public double toDouble() {
        return (double) hour + (double) minute / 100;
    }

    @Override
    public int compareTo(DigitalTime oth) {
        if (this == oth) return 0;
        if (this.hour == oth.hour && this.minute == oth.minute) return 0;
        if (this.hour < oth.hour) return -1;
        if (this.hour == oth.hour && this.minute < oth.minute) return -1;
        return 1;
    }

    public static void main(String[] args) {
        /* Java Array olusturacagin zaman new'lenir !!!! */
        DigitalTime[] arr = new DigitalTime[] {new DigitalTime(1, 22), new DigitalTime(3, 23), new DigitalTime(5, 35)};
    
        DigitalTimeHelper.sortTimes(arr);
        System.out.println(Arrays.toString(arr));  /* Javada Arrays.toString(arr) methodunu hatirlarsan daha guzel olur !! */
    }

}

/* This helper function is to practice very basic sorting since it's asked in exams usually. */
/* A class that implements Comparator interface could be implemented to sort DigitalTime instances in more efficent way. */
class DigitalTimeHelper {

    /* 1D ve 2D arraylerin length'ine -> arr.length veya arr[0].length seklinde bakilir !!!! */
    public static void sortTimes(DigitalTime[] arr) {
        
        for (int i = 0; i < arr.length; ++i) {
            int min_i = i;
            for (int j = i+1; j < arr.length; ++j) {
                if (arr[j].compareTo(arr[min_i]) == -1) min_i = j; 
            }
            DigitalTime temp = arr[i];
            arr[i] = arr[min_i];
            arr[min_i] = temp;
        }
    } 

}

